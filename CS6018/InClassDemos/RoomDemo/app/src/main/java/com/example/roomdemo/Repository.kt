package com.example.roomdemo

import com.example.roomdemo.room.TaskDao
import com.example.roomdemo.room.TaskEntity
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.launch
import kotlin.time.Duration.Companion.milliseconds

class Repository(val scope: CoroutineScope, private val dao: TaskDao){
    val allTasks: Flow<List<TaskEntity?>> = dao.getAllTasks()

    // can web requests ...

    // insert

    fun addTask (task: String){
        scope.launch {
            delay(500.milliseconds)
            val taskObj = TaskEntity(task)
            dao.insertTask(taskObj)
        }
    }
}