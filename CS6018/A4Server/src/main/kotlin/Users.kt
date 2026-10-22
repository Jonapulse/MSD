package com.example

import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.singleOrNull
import org.jetbrains.exposed.v1.core.ResultRow
import org.jetbrains.exposed.v1.core.Table
import org.jetbrains.exposed.v1.core.eq
import org.jetbrains.exposed.v1.r2dbc.R2dbcDatabase
import org.jetbrains.exposed.v1.r2dbc.SchemaUtils
import org.jetbrains.exposed.v1.r2dbc.insert
import org.jetbrains.exposed.v1.r2dbc.selectAll
import org.jetbrains.exposed.v1.r2dbc.transactions.suspendTransaction

object UsersTable : Table("users") {
    val id = uinteger("id").autoIncrement()
    val username = varchar("username", 50).uniqueIndex()
    val passwordHash = varchar("password_hash", 72)
    override val primaryKey = PrimaryKey(id)
}

data class StoredUser(val id: UInt, val username: String, val passwordHash: String)

class UsersDAO(private val database: R2dbcDatabase) {
    suspend fun createSchema() = suspendTransaction(database) {
        SchemaUtils.create(UsersTable)
    }

    suspend fun findByUsername(username: String): StoredUser? = suspendTransaction(database) {
        UsersTable.selectAll()
            .where { UsersTable.username eq username }
            .map(::toUser)
            .singleOrNull()
    }

    suspend fun create(username: String, passwordHash: String): UInt = suspendTransaction(database) {
        UsersTable.insert {
            it[UsersTable.username] = username
            it[UsersTable.passwordHash] = passwordHash
        }[UsersTable.id]
    }

    private fun toUser(row: ResultRow) = StoredUser(
        row[UsersTable.id], row[UsersTable.username], row[UsersTable.passwordHash]
    )
}