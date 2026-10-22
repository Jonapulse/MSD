package com.example

import org.jetbrains.exposed.v1.r2dbc.R2dbcDatabase

object DatabaseConnection {
    val database: R2dbcDatabase by lazy {
        R2dbcDatabase.connect(
            url = "r2dbc:h2:file:///./h2",
            user = "root",
            password = ""
        )
    }
}