package com.example

import io.ktor.http.HttpStatusCode
import io.ktor.server.application.*
import io.ktor.server.auth.*
import io.ktor.server.request.receive
import io.ktor.server.response.respond
import io.ktor.server.response.respondFile
import io.ktor.server.routing.*
import java.io.File
import io.ktor.server.application.ApplicationStopped
import io.ktor.server.application.log
import kotlinx.coroutines.CancellationException
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext

suspend fun Application.configurePhotoRoutes() {
    val photos = PhotosDAO(DatabaseConnection.database).also { it.createSchema() }
    val storage = PhotoStorage(File(System.getenv("PHOTO_DIR") ?: "uploads"))
    val ml = MlClient(System.getenv("ML_URL") ?: "http://localhost:8000")
    monitor.subscribe(ApplicationStopped) { ml.close() }

    routing {
        authenticate("auth-session") {
            route("/photos") {
                post {
                    val user = call.principal<UserSession>()!!.username
                    val bytes = call.receive<ByteArray>()
                    if (bytes.isEmpty()) {
                        return@post call.respond(HttpStatusCode.BadRequest, "Empty body")
                    }
                    val fileName = storage.save(bytes)
                    val id = photos.create(user, fileName)
                    call.respond(HttpStatusCode.Created, mapOf("id" to id))
                }

                get {
                    val user = call.principal<UserSession>()!!.username
                    call.respond(photos.listFor(user).map { PhotoInfo(it.id, it.createdAt) })
                }

                get("/{id}") {
                    val user = call.principal<UserSession>()!!.username
                    val id = call.parameters["id"]?.toUIntOrNull()
                        ?: return@get call.respond(HttpStatusCode.BadRequest, "Invalid ID")
                    val photo = photos.find(id, user)
                        ?: return@get call.respond(HttpStatusCode.NotFound)
                    val file = storage.fileFor(photo.fileName)
                    if (!file.exists()) return@get call.respond(HttpStatusCode.NotFound)
                    call.respondFile(file)
                }

                delete("/{id}") {
                    val user = call.principal<UserSession>()!!.username
                    val id = call.parameters["id"]?.toUIntOrNull()
                        ?: return@delete call.respond(HttpStatusCode.BadRequest, "Invalid ID")
                    val photo = photos.find(id, user)
                        ?: return@delete call.respond(HttpStatusCode.NotFound)
                    photos.delete(id, user)
                    storage.delete(photo.fileName)
                    call.respond(HttpStatusCode.NoContent)
                }

                post("/{id}/analysis") {
                    val user = call.principal<UserSession>()!!.username
                    val id = call.parameters["id"]?.toUIntOrNull()
                        ?: return@post call.respond(HttpStatusCode.BadRequest, "Invalid ID")
                    val photo = photos.find(id, user)
                        ?: return@post call.respond(HttpStatusCode.NotFound)
                    val file = storage.fileFor(photo.fileName)
                    if (!file.exists()) return@post call.respond(HttpStatusCode.NotFound)

                    val bytes = withContext(Dispatchers.IO) { file.readBytes() }
                    val caption = try {
                        ml.caption(bytes)
                    } catch (e: CancellationException) {
                        throw e
                    } catch (e: Exception) {
                        call.application.log.error("Analysis failed for photo $id", e)
                        return@post call.respond(HttpStatusCode.BadGateway, "Analysis service failed")
                    }
                    call.respond(CaptionResponse(caption))
                }
            }
        }
    }
}