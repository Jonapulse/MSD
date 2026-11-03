package com.example

import io.ktor.client.HttpClient
import io.ktor.client.call.body
import io.ktor.client.engine.cio.CIO
import io.ktor.client.plugins.HttpTimeout
import io.ktor.client.plugins.contentnegotiation.ContentNegotiation
import io.ktor.client.request.post
import io.ktor.client.request.setBody
import io.ktor.http.ContentType
import io.ktor.http.contentType
import io.ktor.http.isSuccess
import io.ktor.serialization.kotlinx.json.json
import kotlinx.serialization.Serializable
import kotlinx.serialization.json.Json

@Serializable
data class CaptionResponse(val caption: String)

class MlClient(private val baseUrl: String) {
    private val client = HttpClient(CIO) {
        install(ContentNegotiation) { json(Json { ignoreUnknownKeys = true }) }
        // Captioning can take several seconds on CPU, well past the default timeout
        install(HttpTimeout) { requestTimeoutMillis = 60_000 }
    }

    suspend fun caption(jpeg: ByteArray): String {
        val res = client.post("$baseUrl/caption") {
            contentType(ContentType.Image.JPEG)
            setBody(jpeg)
        }
        if (!res.status.isSuccess()) error("ML server returned ${res.status}")
        return res.body<CaptionResponse>().caption
    }

    fun close() = client.close()
}