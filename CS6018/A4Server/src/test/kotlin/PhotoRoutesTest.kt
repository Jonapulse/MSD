package com.example
import io.ktor.client.request.header
import io.ktor.client.request.post
import io.ktor.http.HttpStatusCode
import kotlin.test.*

@Test
fun analysisRequiresAuthAndOwnership() = serverTest {
    assertEquals(HttpStatusCode.Unauthorized, client.post("/photos/1/analysis").status)

    val owner = client.register()
    val other = client.register()
    val id = client.upload(owner, fakeJpeg)
    assertEquals(
        HttpStatusCode.NotFound,
        client.post("/photos/$id/analysis") { header(SESSION, other) }.status
    )
}