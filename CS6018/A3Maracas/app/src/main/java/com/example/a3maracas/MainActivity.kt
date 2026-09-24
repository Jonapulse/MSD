package com.example.a3maracas

import android.app.Application
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.animation.core.Animatable
import androidx.compose.animation.core.animateFloatAsState
import androidx.compose.animation.core.tween
import androidx.compose.foundation.Canvas
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.ImageBitmap
import androidx.compose.ui.graphics.drawscope.rotate
import androidx.compose.ui.graphics.drawscope.scale
import androidx.compose.ui.res.imageResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.compose.ui.util.lerp
import androidx.lifecycle.ViewModel
import androidx.lifecycle.compose.LifecycleStartEffect
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.compose.viewModel
import androidx.lifecycle.viewmodel.initializer
import androidx.lifecycle.viewmodel.viewModelFactory
import androidx.room.Dao
import androidx.room.Database
import androidx.room.Entity
import androidx.room.Insert
import androidx.room.PrimaryKey
import androidx.room.Query
import com.example.a3maracas.ui.theme.A3MaracasTheme
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.flow
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.launch
import androidx.room.Room
import androidx.room.RoomDatabase
import kotlinx.coroutines.Job
import kotlinx.coroutines.channels.awaitClose
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.callbackFlow
import kotlin.math.sqrt

private const val MIN_EXPECTED_INTENSITY = 5f
private const val MAX_EXPECTED_INTENSITY = 15f
private const val MIN_SCALE = 1f
private const val MAX_SCALE = 3f
//Remove shakes before this time from database on button press
private const val FORGET_SHAKES_MS = 10000L

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            A3MaracasTheme {
                val app = application as MaracasApp
                val myVm: MaracasViewModel = viewModel(
                    factory = viewModelFactory{initializer { MaracasViewModel(app.db.shakeDao(), app.shakeDetector)}}
                )

                LifecycleStartEffect(myVm){
                    myVm.startListening()
                    onStopOrDispose{myVm.stopListening()}
                }

                val intensity by myVm.intensity.collectAsStateWithLifecycle()
                val shakes by myVm.storedShakes.collectAsStateWithLifecycle()

                Scaffold(modifier = Modifier.fillMaxSize(),
                    bottomBar = {
                        MaracasButtons(
                            shakes = shakes,
                            onClickForget = {myVm.forgetPastShakes()}
                        )
                    }
                ) { innerPadding ->
                    MaracasDisplay(
                        shakes = shakes,
                        intensity,
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
        }
    }
}

//------------------------------------------------
// View model
//------------------------------------------------

class MaracasViewModel(private val dao: ShakeDao, private val detector: ShakeDetector) : ViewModel() {
    private var listenJob: Job? = null
    fun startListening(){
        if(listenJob != null) return
        listenJob = viewModelScope.launch {
            detector.shakes().collect { magnitude -> shake(magnitude)}
        }
    }

    fun stopListening(){
        listenJob?.cancel()
        listenJob = null
    }

    val storedShakes: StateFlow<Int> = dao.countAll()
        .stateIn(viewModelScope, SharingStarted.WhileSubscribed(5_000), 0)

    fun shake(velocity: Float = 1f){
        viewModelScope.launch{
            dao.insert(ShakeEvent(timestamp = System.currentTimeMillis(), magnitude = velocity))
        }
    }

    fun forgetPastShakes(){
        viewModelScope.launch {
            dao.deleteBefore(System.currentTimeMillis() - FORGET_SHAKES_MS)
        }
    }

    val intensity: StateFlow<Float> = flow{
        while(true){
            emit(dao.averageSince(System.currentTimeMillis() - 1_000) ?: 0f)
            delay(250)
        }
    }.stateIn(viewModelScope, SharingStarted.WhileSubscribed(1_000), 0f)
}

//------------------------------------------------
// View - composables
//------------------------------------------------
@Composable
fun MaracasDisplay(shakes: Int, intensity: Float, modifier: Modifier = Modifier){
    val maracas = ImageBitmap.imageResource(R.drawable.maracas)
    val rotation = remember {Animatable(0f)}

    val targetScale = lerp(MIN_SCALE, MAX_SCALE, ((intensity - MIN_EXPECTED_INTENSITY) / (MAX_EXPECTED_INTENSITY - MIN_EXPECTED_INTENSITY)).coerceIn(0f, 1f))
    val scale by animateFloatAsState(targetScale, label = "maracasScale")

    LaunchedEffect(shakes) {
        if(shakes == 0) return@LaunchedEffect
        rotation.animateTo(30f, tween(80))
        rotation.animateTo(-30f, tween(160))
        rotation.animateTo(0f, tween(80))
    }

    Canvas(modifier.fillMaxSize()){
        val center = Offset(size.width / 2, size.height / 2)
        scale(scale, pivot = center) {
            rotate(
                degrees = rotation.value,
                pivot = center
            ){
                drawImage(
                    image = maracas,
                    topLeft = Offset(
                        (size.width - maracas.width) / 2,
                        (size.height - maracas.height) / 2
                    )
                )
            }
        }
    }
}

@Preview(showBackground = true)
@Composable
fun MaracasPreview() {
    A3MaracasTheme {
        MaracasDisplay(1, 2f, Modifier.fillMaxSize() )
    }
}

@Composable
fun MaracasButtons(shakes: Int, onClickForget: () -> Unit) {
    Column(modifier = Modifier
            .fillMaxWidth()
            .padding(bottom = 60.dp),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text("How shook are we?")
        Spacer(Modifier.height(5.dp))
        Text(
            text = "$shakes",
            fontSize = 32.sp
        )
        Spacer(Modifier.height(5.dp))
        Button( onClick = onClickForget )
        {
            Text("Forget old shakes (10 seconds)")
        }
    }
}

@Preview
@Composable
fun MaracasButtonPreview()
{
    A3MaracasTheme {
        MaracasButtons(shakes = 3, onClickForget = {})
    }
}

//------------------------------------------------
// Model - room database, shake detection, and Application stub to init them
//------------------------------------------------

class MaracasApp : Application() {
    val db: ShakeDatabase by lazy {
        Room.databaseBuilder(this, ShakeDatabase::class.java, "shakes.db").build()
    }
    val shakeDetector: ShakeDetector by lazy{
        ShakeDetector(getSystemService(SensorManager::class.java))
    }
}

@Database(entities = [ShakeEvent::class], version = 1)
abstract class ShakeDatabase : RoomDatabase() {
    abstract fun shakeDao(): ShakeDao
}

@Entity(tableName = "shakes")
data class ShakeEvent(
    @PrimaryKey(autoGenerate = true) val id: Long = 0,
    val timestamp: Long,
    val magnitude: Float
)

@Dao
interface ShakeDao {
    @Insert
    suspend fun insert(event: ShakeEvent)

    @Query("SELECT AVG(magnitude) FROM shakes WHERE timestamp >= :since")
    suspend fun averageSince(since: Long): Float?

    @Query("DELETE FROM shakes WHERE timestamp < :before")
    suspend fun deleteBefore(before: Long)

    @Query("SELECT COUNT(*) FROM shakes")
    fun countAll(): Flow<Int>
}

private const val GRAVITY_ALPHA = 0.8f            // low-pass smoothing, from the Android sensor docs
private const val MIN_ACCEL = 3f                  // m/s^2, below this is treated as noise
private const val MIN_SHAKE_GAP_NS = 150_000_000L // 150 ms debounce

class ShakeDetector(private val sensorManager: SensorManager) {

    fun shakes(): Flow<Float> = callbackFlow {
        val accel = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)
        if (accel == null) {   // no accelerometer (some emulator configs)
            close()
            return@callbackFlow
        }

        val gravity = FloatArray(3)
        var gravityInitialized = false
        val ref = FloatArray(3)
        var hasRef = false
        var lastShakeNs = 0L

        val listener = object : SensorEventListener {
            override fun onSensorChanged(event: SensorEvent) {
                val v = event.values

                if (!gravityInitialized) {
                    v.copyInto(gravity, endIndex = 3)
                    gravityInitialized = true
                    return
                }

                // We subtract gravity ourselves (rather than use virtual LINEAR_ACCELERATION sensor)
                for (i in 0..2) gravity[i] = GRAVITY_ALPHA * gravity[i] + (1 - GRAVITY_ALPHA) * v[i]
                val x = v[0] - gravity[0]
                val y = v[1] - gravity[1]
                val z = v[2] - gravity[2]

                val mag = sqrt(x * x + y * y + z * z)
                if (mag < MIN_ACCEL) return

                if (hasRef) {
                    val dot = x * ref[0] + y * ref[1] + z * ref[2]
                    if (dot < 0 && event.timestamp - lastShakeNs > MIN_SHAKE_GAP_NS) {
                        val dx = x - ref[0]
                        val dy = y - ref[1]
                        val dz = z - ref[2]
                        trySend(sqrt(dx * dx + dy * dy + dz * dz))
                        lastShakeNs = event.timestamp
                    }
                }
                ref[0] = x; ref[1] = y; ref[2] = z
                hasRef = true
            }

            override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {}
        }

        sensorManager.registerListener(listener, accel, SensorManager.SENSOR_DELAY_GAME)
        awaitClose { sensorManager.unregisterListener(listener) }
    }
}