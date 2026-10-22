package com.example

import io.ktor.http.HttpStatusCode
import io.ktor.server.application.*
import io.ktor.server.auth.*
import io.ktor.server.response.respond
import io.ktor.server.sessions.*
import kotlinx.serialization.Serializable

@Serializable
data class UserSession(val username: String)

fun Application.configureSecurity() {
    install(Sessions) {
        header<UserSession>("X-Session", SessionStorageMemory())
    }
    install(Authentication) {
        session<UserSession>("auth-session") {
            validate { session -> session }
            challenge { call.respond(HttpStatusCode.Unauthorized) }
        }
    }
}