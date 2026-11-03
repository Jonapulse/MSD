package com.example

import io.ktor.http.HttpStatusCode
import io.ktor.server.application.*
import io.ktor.server.auth.*
import io.ktor.server.request.receive
import io.ktor.server.response.respond
import io.ktor.server.routing.*
import io.ktor.server.sessions.*
import kotlinx.serialization.Serializable

@Serializable
data class Credentials(val username: String, val password: String)

// Usernames go into an LDAP DN, so only allow characters with no special meaning there
private val USERNAME_REGEX = Regex("^[A-Za-z0-9_.-]{1,50}$")

fun Application.configureAuthRoutes() {
    val directory = createUserDirectory()

    routing {
        post("/register") {
            val creds = call.receive<Credentials>()
            if (!creds.username.matches(USERNAME_REGEX) || creds.password.length < 4) {
                return@post call.respond(HttpStatusCode.BadRequest, "Invalid username or password")
            }
            if (!directory.register(creds.username, creds.password)) {
                return@post call.respond(HttpStatusCode.Conflict, "Username taken")
            }
            call.sessions.set(UserSession(creds.username))
            call.respond(HttpStatusCode.Created)
        }

        post("/login") {
            val creds = call.receive<Credentials>()
            // Empty password must be rejected here: LDAP treats it as an anonymous bind
            val valid = creds.username.matches(USERNAME_REGEX) &&
                    creds.password.isNotEmpty() &&
                    directory.authenticate(creds.username, creds.password)
            if (!valid) {
                return@post call.respond(HttpStatusCode.Unauthorized, "Invalid credentials")
            }
            call.sessions.set(UserSession(creds.username))
            call.respond(HttpStatusCode.OK)
        }

        authenticate("auth-session") {
            post("/logout") {
                call.sessions.clear<UserSession>()
                call.respond(HttpStatusCode.NoContent)
            }
            get("/me") {
                val session = call.principal<UserSession>()!!
                call.respond(mapOf("username" to session.username))
            }
        }
    }
}