package com.example


import io.ktor.http.HttpStatusCode
import io.ktor.server.application.Application
import io.ktor.server.request.receive
import io.ktor.server.response.respond
import io.ktor.server.routing.delete
import io.ktor.server.routing.get
import io.ktor.server.routing.post
import io.ktor.server.routing.put
import io.ktor.server.routing.routing

suspend fun Application.configureFacts() {

    val factService = FactsDAOs(DatabaseConnection.database).also {
        it.createSchema()
    }

    routing {

        post("/facts") {
            val fact = call.receive<ExposedFact>()
            val id = factService.create(fact)

            call.respond(HttpStatusCode.Created, mapOf("id" to id))
        }

        get("/facts") {
            call.respond(HttpStatusCode.OK, factService.readAll())
        }

        get("/facts/{id}") {
            val id = call.parameters["id"]?.toUIntOrNull()
                ?: return@get call.respond(
                    HttpStatusCode.BadRequest,
                    "Invalid ID"
                )

            val fact = factService.read(id)

            if (fact != null) {
                call.respond(HttpStatusCode.OK, fact)
            } else {
                call.respond(HttpStatusCode.NotFound)
            }
        }

        put("/facts/{id}") {
            val id = call.parameters["id"]?.toUIntOrNull()
                ?: return@put call.respond(
                    HttpStatusCode.BadRequest,
                    "Invalid ID"
                )

            val fact = call.receive<ExposedFact>()
            factService.update(id, fact)

            call.respond(HttpStatusCode.NoContent)
        }

        delete("/facts/{id}") {
            val id = call.parameters["id"]?.toUIntOrNull()
                ?: return@delete call.respond(
                    HttpStatusCode.BadRequest,
                    "Invalid ID"
                )

            factService.delete(id)

            call.respond(HttpStatusCode.NoContent)
        }
    }
}