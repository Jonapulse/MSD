package com.example.a3maraca.data

import android.content.Context
import androidx.room.Dao
import androidx.room.Database
import androidx.room.Entity
import androidx.room.Insert
import androidx.room.PrimaryKey
import androidx.room.Query
import androidx.room.Room
import androidx.room.RoomDatabase
import androidx.room3.Entity
import androidx.room3.PrimaryKey
import kotlinx.coroutines.flow.Flow

@Entity(tableName = "shake_events")
data class ShakeEvent(
    @PrimaryKey(autoGenerate = true) val id: Long = 0,
    val timestamp: Long
)

@Dao
interface ShakeDao {
    @Insert
    suspend fun insert(event: ShakeEvent)

    @Query("SELECT * FROM shake_events ORDER BY timestamp DESC")
    fun getAll(): Flow<List<ShakeEvent>>

    @Query("SELECT * FROM shake_events ORDER BY timestamp DESC LIMIT 1")
    suspend fun getLast(): ShakeEvent?

    @Query("SELECT COUNT(*) FROM shake_events")
    fun getCount(): Flow<Int>
}

@Database(entities = [ShakeEvent::class], version = 1, exportSchema = false)
abstract class ShakeDatabase : RoomDatabase() {
    abstract fun shakeDao(): ShakeDao

    companion object {
        @Volatile private var INSTANCE: ShakeDatabase? = null

        fun getInstance(context: Context): ShakeDatabase =
            INSTANCE ?: synchronized(this) {
                INSTANCE ?: Room.databaseBuilder(
                    context.applicationContext,
                    ShakeDatabase::class.java,
                    "shake_database"
                ).build().also { INSTANCE = it }
            }
    }
}
