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
import io.ktor.client.call.body
import io.ktor.client.request.delete
import io.ktor.client.request.get
import io.ktor.client.statement.HttpResponse
import io.ktor.client.statement.readRawBytes

@Serializable
data class Credentials(val username: String, val password: String)

@Serializable
data class UploadResponse(val id: UInt)

@Serializable
data class PhotoInfo(val id: UInt, val createdAt: Long)
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

    suspend fun uploadPhoto(bytes: ByteArray): UInt {
        val res = client.post("/photos") {
            contentType(ContentType.Image.JPEG)
            setBody(bytes)
        }
        if (!res.status.isSuccess()) throw ApiException(res.status, res.bodyAsText())
        return res.body<UploadResponse>().id
    }

    private suspend fun HttpResponse.requireSuccess(): HttpResponse {
        if (!status.isSuccess()) throw ApiException(status, bodyAsText())
        return this
    }

    suspend fun listPhotos(): List<PhotoInfo> =
        client.get("/photos").requireSuccess().body()

    suspend fun downloadPhoto(id: UInt): ByteArray =
        client.get("/photos/$id").requireSuccess().readRawBytes()

    suspend fun deletePhoto(id: UInt) {
        client.delete("/photos/$id").requireSuccess()
    }
}