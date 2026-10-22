package com.example.a4camera.network

import io.ktor.client.HttpClient
import io.ktor.client.engine.okhttp.OkHttp
import io.ktor.client.plugins.api.createClientPlugin
import io.ktor.client.plugins.contentnegotiation.ContentNegotiation
import io.ktor.client.plugins.defaultRequest
import io.ktor.client.request.post
import io.ktor.client.request.setBody
import io.ktor.client.statement.bodyAsText
import io.ktor.http.ContentType
import io.ktor.http.HttpStatusCode
import io.ktor.http.contentType
import io.ktor.http.isSuccess
import io.ktor.serialization.kotlinx.json.json
import kotlinx.serialization.Serializable

@Serializable
data class Credentials(val username: String, val password: String)

class ApiException(val status: HttpStatusCode, message: String) : Exception(message)

object ServerApi {
    private const val BASE_URL = "http://localhost:8080"
    private const val SESSION_HEADER = "X-Session"

    @Volatile
    private var sessionToken: String? = null

    // Attaches the session header to every request once logged in
    private val SessionHeader = createClientPlugin("SessionHeader") {
        onRequest { request, _ ->
            sessionToken?.let { request.headers.append(SESSION_HEADER, it) }
        }
    }

    val client = HttpClient(OkHttp) {
        install(ContentNegotiation) { json() }
        install(SessionHeader)
        defaultRequest { url(BASE_URL) }
    }

    suspend fun register(username: String, password: String) =
        startSession("/register", username, password)

    suspend fun login(username: String, password: String) =
        startSession("/login", username, password)

    private suspend fun startSession(path: String, username: String, password: String) {
        val res = client.post(path) {
            contentType(ContentType.Application.Json)
            setBody(Credentials(username, password))
        }
        if (!res.status.isSuccess()) throw ApiException(res.status, res.bodyAsText())
        sessionToken = res.headers[SESSION_HEADER]
            ?: throw ApiException(res.status, "Server did not return a session")
    }

    suspend fun logout() {
        try {
            client.post("/logout")
        } finally {
            sessionToken = null  // clear locally even if the server call fails
        }
    }
}