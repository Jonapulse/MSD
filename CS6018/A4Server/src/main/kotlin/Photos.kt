package com.example

import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.singleOrNull
import kotlinx.coroutines.flow.toList
import kotlinx.coroutines.withContext
import kotlinx.serialization.Serializable
import org.jetbrains.exposed.v1.core.ResultRow
import org.jetbrains.exposed.v1.core.SortOrder
import org.jetbrains.exposed.v1.core.Table
import org.jetbrains.exposed.v1.core.and
import org.jetbrains.exposed.v1.core.eq
import org.jetbrains.exposed.v1.r2dbc.R2dbcDatabase
import org.jetbrains.exposed.v1.r2dbc.SchemaUtils
import org.jetbrains.exposed.v1.r2dbc.deleteWhere
import org.jetbrains.exposed.v1.r2dbc.insert
import org.jetbrains.exposed.v1.r2dbc.selectAll
import org.jetbrains.exposed.v1.r2dbc.transactions.suspendTransaction
import java.io.File
import java.util.UUID

object PhotosTable : Table("photos") {
    val id = uinteger("id").autoIncrement()
    val owner = varchar("owner", 50).index()
    val fileName = varchar("file_name", 100)
    val createdAt = long("created_at")
    override val primaryKey = PrimaryKey(id)
}

@Serializable
data class PhotoInfo(val id: UInt, val createdAt: Long)

data class StoredPhoto(val id: UInt, val owner: String, val fileName: String, val createdAt: Long)

class PhotosDAO(private val database: R2dbcDatabase) {
    suspend fun createSchema() = suspendTransaction(database) {
        SchemaUtils.create(PhotosTable)
    }

    suspend fun create(owner: String, fileName: String): UInt = suspendTransaction(database) {
        PhotosTable.insert {
            it[PhotosTable.owner] = owner
            it[PhotosTable.fileName] = fileName
            it[createdAt] = System.currentTimeMillis()
        }[PhotosTable.id]
    }

    suspend fun listFor(owner: String): List<StoredPhoto> = suspendTransaction(database) {
        PhotosTable.selectAll()
            .where { PhotosTable.owner eq owner }
            .orderBy(PhotosTable.createdAt, SortOrder.DESC)
            .map(::toPhoto)
            .toList()
    }

    suspend fun find(id: UInt, owner: String): StoredPhoto? = suspendTransaction(database) {
        PhotosTable.selectAll()
            .where { (PhotosTable.id eq id) and (PhotosTable.owner eq owner) }
            .map(::toPhoto)
            .singleOrNull()
    }

    suspend fun delete(id: UInt, owner: String): Int = suspendTransaction(database) {
        PhotosTable.deleteWhere { (PhotosTable.id eq id) and (PhotosTable.owner eq owner) }
    }

    private fun toPhoto(row: ResultRow) = StoredPhoto(
        row[PhotosTable.id], row[PhotosTable.owner], row[PhotosTable.fileName], row[PhotosTable.createdAt]
    )
}

class PhotoStorage(val dir: File) {
    init { dir.mkdirs() }

    suspend fun save(bytes: ByteArray): String = withContext(Dispatchers.IO) {
        val name = "${UUID.randomUUID()}.jpg"
        File(dir, name).writeBytes(bytes)
        name
    }

    fun fileFor(name: String) = File(dir, name)

    suspend fun delete(name: String) = withContext(Dispatchers.IO) {
        File(dir, name).delete()
    }
}