package com.example.roomdemo.room

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "tasks")
data class TaskEntity(val text: String,
                      @PrimaryKey(autoGenerate = true) val id: Int = 0
)
