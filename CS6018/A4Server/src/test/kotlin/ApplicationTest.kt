package com.example

import io.ktor.client.HttpClient
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import io.ktor.server.testing.*
import kotlinx.serialization.json.Json
import kotlinx.serialization.json.jsonObject
import kotlinx.serialization.json.jsonPrimitive
import java.util.UUID
import kotlin.test.*
import io.ktor.server.config.ApplicationConfig

private const val SESSION = "X-Session"

private fun uniqueName() = "user-${UUID.randomUUID()}"

private fun credsJson(user: String, pw: String) = """{"username":"$user","password":"$pw"}"""

private fun serverTest(block: suspend ApplicationTestBuilder.() -> Unit) = testApplication {
    environment {
        config = ApplicationConfig("application.yaml")
    }
    block()
}

private suspend fun HttpClient.register(user: String = uniqueName(), pw: String = "secret1"): String {
    val res = post("/register") {
        contentType(ContentType.Application.Json)
        setBody(credsJson(user, pw))
    }
    assertEquals(HttpStatusCode.Created, res.status)
    return assertNotNull(res.headers[SESSION])
}

private suspend fun HttpClient.upload(session: String, bytes: ByteArray): String {
    val res = post("/photos") {
        header(SESSION, session)
        contentType(ContentType.Image.JPEG)
        setBody(bytes)
    }
    assertEquals(HttpStatusCode.Created, res.status)
    return Json.parseToJsonElement(res.bodyAsText()).jsonObject["id"]!!.jsonPrimitive.content
}

class RootRouteTest {
    @Test
    fun rootRespondsHello() = serverTest {
        val res = client.get("/")
        assertEquals(HttpStatusCode.OK, res.status)
        assertEquals("Hello, World!", res.bodyAsText())
    }
}

class AuthRoutesTest {
    @Test
    fun registerReturnsCreatedAndSession() = serverTest {
        client.register()
    }

    @Test
    fun registerDuplicateIsConflict() = serverTest {
        val name = uniqueName()
        client.register(name)
        val res = client.post("/register") {
            contentType(ContentType.Application.Json)
            setBody(credsJson(name, "secret1"))
        }
        assertEquals(HttpStatusCode.Conflict, res.status)
    }

    @Test
    fun registerInvalidIsBadRequest() = serverTest {
        val res = client.post("/register") {
            contentType(ContentType.Application.Json)
            setBody(credsJson("", "x"))
        }
        assertEquals(HttpStatusCode.BadRequest, res.status)
    }

    @Test
    fun loginWithCorrectPasswordReturnsSession() = serverTest {
        val name = uniqueName()
        client.register(name, "secret1")
        val res = client.post("/login") {
            contentType(ContentType.Application.Json)
            setBody(credsJson(name, "secret1"))
        }
        assertEquals(HttpStatusCode.OK, res.status)
        assertNotNull(res.headers[SESSION])
    }

    @Test
    fun loginWithWrongPasswordIsUnauthorized() = serverTest {
        val name = uniqueName()
        client.register(name, "secret1")
        val res = client.post("/login") {
            contentType(ContentType.Application.Json)
            setBody(credsJson(name, "wrong"))
        }
        assertEquals(HttpStatusCode.Unauthorized, res.status)
    }

    @Test
    fun loginUnknownUserIsUnauthorized() = serverTest {
        val res = client.post("/login") {
            contentType(ContentType.Application.Json)
            setBody(credsJson(uniqueName(), "secret1"))
        }
        assertEquals(HttpStatusCode.Unauthorized, res.status)
    }

    @Test
    fun meReturnsUsername() = serverTest {
        val name = uniqueName()
        val session = client.register(name)
        val res = client.get("/me") { header(SESSION, session) }
        assertEquals(HttpStatusCode.OK, res.status)
        assertTrue(res.bodyAsText().contains(name))
    }

    @Test
    fun meWithoutSessionIsUnauthorized() = serverTest {
        assertEquals(HttpStatusCode.Unauthorized, client.get("/me").status)
    }

    @Test
    fun logoutInvalidatesSession() = serverTest {
        val session = client.register()
        val res = client.post("/logout") { header(SESSION, session) }
        assertEquals(HttpStatusCode.NoContent, res.status)
        assertEquals(HttpStatusCode.Unauthorized, client.get("/me") { header(SESSION, session) }.status)
    }
}

class PhotoRoutesTest {
    private val fakeJpeg = ByteArray(1024) { it.toByte() }

    @Test
    fun photosRequireAuth() = serverTest {
        assertEquals(HttpStatusCode.Unauthorized, client.get("/photos").status)
        assertEquals(HttpStatusCode.Unauthorized, client.post("/photos").status)
        assertEquals(HttpStatusCode.Unauthorized, client.get("/photos/1").status)
        assertEquals(HttpStatusCode.Unauthorized, client.delete("/photos/1").status)
    }

    @Test
    fun uploadListAndDownload() = serverTest {
        val session = client.register()
        val id = client.upload(session, fakeJpeg)

        val list = client.get("/photos") { header(SESSION, session) }
        assertEquals(HttpStatusCode.OK, list.status)
        assertTrue(list.bodyAsText().contains("\"id\":$id"))

        val download = client.get("/photos/$id") { header(SESSION, session) }
        assertEquals(HttpStatusCode.OK, download.status)
        assertContentEquals(fakeJpeg, download.readRawBytes())
    }

    @Test
    fun emptyUploadIsBadRequest() = serverTest {
        val session = client.register()
        val res = client.post("/photos") {
            header(SESSION, session)
            contentType(ContentType.Image.JPEG)
            setBody(ByteArray(0))
        }
        assertEquals(HttpStatusCode.BadRequest, res.status)
    }

    @Test
    fun invalidIdIsBadRequest() = serverTest {
        val session = client.register()
        assertEquals(HttpStatusCode.BadRequest, client.get("/photos/abc") { header(SESSION, session) }.status)
        assertEquals(HttpStatusCode.BadRequest, client.delete("/photos/abc") { header(SESSION, session) }.status)
    }

    @Test
    fun otherUsersCannotSeeOrDeletePhotos() = serverTest {
        val owner = client.register()
        val other = client.register()
        val id = client.upload(owner, fakeJpeg)

        assertEquals("[]", client.get("/photos") { header(SESSION, other) }.bodyAsText())
        assertEquals(HttpStatusCode.NotFound, client.get("/photos/$id") { header(SESSION, other) }.status)
        assertEquals(HttpStatusCode.NotFound, client.delete("/photos/$id") { header(SESSION, other) }.status)

        // Owner's photo survived the other user's delete attempt
        assertEquals(HttpStatusCode.OK, client.get("/photos/$id") { header(SESSION, owner) }.status)
    }

    @Test
    fun deleteRemovesPhoto() = serverTest {
        val session = client.register()
        val id = client.upload(session, fakeJpeg)

        assertEquals(HttpStatusCode.NoContent, client.delete("/photos/$id") { header(SESSION, session) }.status)
        assertEquals(HttpStatusCode.NotFound, client.get("/photos/$id") { header(SESSION, session) }.status)
    }
}