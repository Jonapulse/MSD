package com.example

import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.singleOrNull
import kotlinx.coroutines.flow.toList
import org.jetbrains.exposed.v1.core.ResultRow

import org.jetbrains.exposed.v1.core.eq

import org.jetbrains.exposed.v1.r2dbc.R2dbcDatabase
import org.jetbrains.exposed.v1.r2dbc.SchemaUtils
import org.jetbrains.exposed.v1.r2dbc.deleteWhere
import org.jetbrains.exposed.v1.r2dbc.insert
import org.jetbrains.exposed.v1.r2dbc.selectAll
import org.jetbrains.exposed.v1.r2dbc.transactions.suspendTransaction
import org.jetbrains.exposed.v1.r2dbc.update

class FactsDAOs(private val database: R2dbcDatabase) {

    suspend fun createSchema() {
        suspendTransaction(database) {
            SchemaUtils.create(FactsTable)
        }
    }

    suspend fun create(fact: ExposedFact): UInt =
        suspendTransaction(database) {
            val newRecord = FactsTable.insert {
                it[text] = fact.text
                it[sourceName] = fact.sourceName
            }

            newRecord[FactsTable.id]
        }

    suspend fun read(id: UInt): ExposedFact? =
        suspendTransaction(database) {
            FactsTable
                .selectAll()
                .where { FactsTable.id eq id }
                .map(::toFact)
                .singleOrNull()
        }

    suspend fun readAll(): List<ExposedFact> =
        suspendTransaction(database) {
            FactsTable
                .selectAll()
                .map(::toFact)
                .toList()
        }

    suspend fun update(id: UInt, fact: ExposedFact) {
        suspendTransaction(database) {
            FactsTable.update({ FactsTable.id eq id }) {
                it[text] = fact.text
                it[sourceName] = fact.sourceName
            }
        }
    }

    suspend fun delete(id: UInt) {
        suspendTransaction(database) {
            FactsTable.deleteWhere { FactsTable.id eq id }
        }
    }

    private fun toFact(row: ResultRow): ExposedFact =
        ExposedFact(
            id = row[FactsTable.id],
            text = row[FactsTable.text],
            sourceName = row[FactsTable.sourceName]
        )
}