package com.example.a3maraca.shake

import android.content.Context
import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import kotlin.math.sqrt

/**
 * Detects a "shake" by watching for a sharp reversal in acceleration direction.
 *
 * On every reading we take the dot product of the current linear-acceleration
 * vector against the previous one. Two vectors pointing in similar directions
 * give a positive dot product; a sudden reversal (the hallmark of a shake)
 * drives it negative. We also require a minimum magnitude so slow drift or
 * gravity noise doesn't trigger false positives.
 */
class ShakeDetector(
    context: Context,
    private val magnitudeThreshold: Float = 12f,
    private val onShake: () -> Unit
) : SensorEventListener {

    private val sensorManager =
        context.getSystemService(Context.SENSOR_SERVICE) as SensorManager

    // TYPE_LINEAR_ACCELERATION strips out gravity for us, which makes the
    // dot-product comparison much cleaner than raw TYPE_ACCELEROMETER data.
    private val accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_LINEAR_ACCELERATION)

    private var lastVector: FloatArray? = null

    fun start() {
        accelerometer?.let {
            sensorManager.registerListener(this, it, SensorManager.SENSOR_DELAY_GAME)
        }
    }

    fun stop() {
        sensorManager.unregisterListener(this)
    }

    override fun onSensorChanged(event: SensorEvent) {
        val current = event.values.copyOf(3)
        val magnitude = sqrt(
            current[0] * current[0] + current[1] * current[1] + current[2] * current[2]
        )

        val previous = lastVector
        if (previous != null) {
            val dot = previous[0] * current[0] +
                previous[1] * current[1] +
                previous[2] * current[2]

            // Direction reversed AND it was forceful enough to be a real shake,
            // not just hand tremor.
            if (dot < 0f && magnitude > magnitudeThreshold) {
                onShake()
            }
        }
        lastVector = current
    }

    override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {}
}
