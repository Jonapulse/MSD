package com.example.coroutinesdemo

import android.app.Application
import androidx.room.Room
import com.example.coroutinesdemo.room.AppDatabase
class TodoAPP: Application {
    val scope = Coroutinescpe(SupervisorJob())
    val db by lazy {
        Room.databaseBuilder(
            applicationContext,

        ).build()
    }
}