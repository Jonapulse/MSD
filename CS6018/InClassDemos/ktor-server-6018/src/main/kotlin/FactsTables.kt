package com.example


import kotlinx.serialization.Serializable
import org.jetbrains.exposed.v1.core.Table

object FactsTable : Table("facts") {
    val id = uinteger("id").autoIncrement()
    val text = varchar("text", length = 255)
    val sourceName = varchar("source", length = 255)

    override val primaryKey = PrimaryKey(id)
}

@Serializable
data class ExposedFact(
    val id: UInt? = null,
    val text: String,
    val sourceName: String
)