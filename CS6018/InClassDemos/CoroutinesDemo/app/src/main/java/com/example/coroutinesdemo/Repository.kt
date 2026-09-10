package com.example.coroutinesdemo

import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.flow.Flow
import com.example.roomdemo.room.TaskDao
import com.example.roomdemo.room.TaskEntity
import kotlin.time.Duration.Companion.milliseconds


class Repository(val scope: CoroutineScope, private val dao: TaskDao) {
    val allTasks:Flow<List<TaskEntity?>> = dao.getAllTasks()

    // can web requests . . .

    // insert

    fun addTask(task:String){
        scope.launch{
            delay(500.milliseconds)
        }
    }
}