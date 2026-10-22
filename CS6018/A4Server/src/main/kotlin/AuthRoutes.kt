package com.example

import io.ktor.http.HttpStatusCode
import io.ktor.server.application.*
import io.ktor.server.auth.*
import io.ktor.server.request.receive
import io.ktor.server.response.respond
import io.ktor.server.routing.*
import io.ktor.server.sessions.*
import kotlinx.serialization.Serializable
import org.mindrot.jbcrypt.BCrypt

@Serializable
data class Credentials(val username: String, val password: String)

suspend fun Application.configureAuthRoutes() {
    val users = UsersDAO(DatabaseConnection.database).also { it.createSchema() }

    routing {
        post("/register") {
            val creds = call.receive<Credentials>()
            if (creds.username.isBlank() || creds.password.length < 4) {
                return@post call.respond(HttpStatusCode.BadRequest, "Invalid username or password")
            }
            if (users.findByUsername(creds.username) != null) {
                return@post call.respond(HttpStatusCode.Conflict, "Username taken")
            }
            users.create(creds.username, BCrypt.hashpw(creds.password, BCrypt.gensalt()))
            call.sessions.set(UserSession(creds.username))
            call.respond(HttpStatusCode.Created)
        }

        post("/login") {
            val creds = call.receive<Credentials>()
            val user = users.findByUsername(creds.username)
            if (user == null || !BCrypt.checkpw(creds.password, user.passwordHash)) {
                return@post call.respond(HttpStatusCode.Unauthorized, "Invalid credentials")
            }
            call.sessions.set(UserSession(user.username))
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