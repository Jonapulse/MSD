package com.example

import io.ktor.server.application.Application
import io.ktor.server.application.log
import io.ktor.server.auth.UserPasswordCredential
import io.ktor.server.auth.ldap.ldapAuthenticate
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import org.mindrot.jbcrypt.BCrypt
import java.security.MessageDigest
import java.security.SecureRandom
import java.util.Base64
import java.util.Hashtable
import java.util.concurrent.ConcurrentHashMap
import javax.naming.Context
import javax.naming.NameAlreadyBoundException
import javax.naming.directory.BasicAttribute
import javax.naming.directory.BasicAttributes
import javax.naming.directory.InitialDirContext

interface UserDirectory {
    /** True if the username/password pair is valid. */
    suspend fun authenticate(username: String, password: String): Boolean

    /** True if created, false if the username is already taken. */
    suspend fun register(username: String, password: String): Boolean
}

class LdapUserDirectory(
    private val url: String,
    private val usersDn: String,
    private val adminDn: String,
    private val adminPassword: String
) : UserDirectory {

    override suspend fun authenticate(username: String, password: String): Boolean =
        withContext(Dispatchers.IO) {
            ldapAuthenticate(
                UserPasswordCredential(username, password),
                url,
                "cn=%s,$usersDn"
            ) != null
        }

    override suspend fun register(username: String, password: String): Boolean =
        withContext(Dispatchers.IO) {
            val env = Hashtable<String, String>().apply {
                put(Context.INITIAL_CONTEXT_FACTORY, "com.sun.jndi.ldap.LdapCtxFactory")
                put(Context.PROVIDER_URL, url)
                put(Context.SECURITY_AUTHENTICATION, "simple")
                put(Context.SECURITY_PRINCIPAL, adminDn)
                put(Context.SECURITY_CREDENTIALS, adminPassword)
            }
            val ctx = InitialDirContext(env)
            try {
                val attrs = BasicAttributes(true).apply {
                    put(BasicAttribute("objectClass").apply {
                        add("top"); add("person"); add("organizationalPerson"); add("inetOrgPerson")
                    })
                    put("cn", username)
                    put("sn", username)
                    put("uid", username)
                    put("userPassword", ssha(password))
                }
                ctx.createSubcontext("cn=$username,$usersDn", attrs)
                true
            } catch (e: NameAlreadyBoundException) {
                false
            } finally {
                ctx.close()
            }
        }

    // Salted SHA-1, OpenLDAP's standard {SSHA} format: base64(sha1(password + salt) + salt)
    private fun ssha(password: String): String {
        val salt = ByteArray(8).also { SecureRandom().nextBytes(it) }
        val md = MessageDigest.getInstance("SHA-1")
        md.update(password.toByteArray())
        md.update(salt)
        return "{SSHA}" + Base64.getEncoder().encodeToString(md.digest() + salt)
    }
}

/** For tests and running locally without LDAP. Accounts vanish on restart. */
class InMemoryUserDirectory : UserDirectory {
    private val users = ConcurrentHashMap<String, String>()

    override suspend fun authenticate(username: String, password: String): Boolean =
        users[username]?.let { BCrypt.checkpw(password, it) } ?: false

    override suspend fun register(username: String, password: String): Boolean =
        users.putIfAbsent(username, BCrypt.hashpw(password, BCrypt.gensalt())) == null
}

fun Application.createUserDirectory(): UserDirectory {
    val url = System.getenv("LDAP_URL")
    return if (url != null) {
        log.info("Using LDAP user directory at $url")
        LdapUserDirectory(
            url = url,
            usersDn = System.getenv("LDAP_USERS_DN") ?: "ou=users,dc=example,dc=org",
            adminDn = System.getenv("LDAP_ADMIN_DN") ?: "cn=admin,dc=example,dc=org",
            adminPassword = System.getenv("LDAP_ADMIN_PASSWORD")
                ?: error("LDAP_URL is set but LDAP_ADMIN_PASSWORD is not")
        )
    } else {
        log.warn("LDAP_URL not set: using IN-MEMORY user directory (tests/local dev only)")
        InMemoryUserDirectory()
    }
}