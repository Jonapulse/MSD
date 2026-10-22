package com.example.a4camera

import android.graphics.Bitmap
import android.graphics.Color
import android.graphics.Matrix
import android.graphics.RectF
import android.util.Log
import androidx.camera.core.ImageAnalysis
import androidx.camera.core.ImageProxy

enum class AnalysisMode{BRIGHTNESS, ML_KIT, EFF_DET}

data class DetectionBox(val box: RectF, val label: String, val score: Float)
sealed interface AnalysisResult{
    data class Overlay(val bitmap: Bitmap) : AnalysisResult
    data class Detections(
        val boxes: List<DetectionBox>,
        val imageWidth: Int,
        val imageHeight: Int
    ) : AnalysisResult
}

class BrightnessAnalyzer(
    private val threshold: Int,
    private val onResult: (AnalysisResult) -> Unit
) : ImageAnalysis.Analyzer {
    override fun analyze(image: ImageProxy){
        image.use{
            try{
                val yPlane = image.planes[0]
                val buffer = yPlane.buffer
                val rowStride = yPlane.rowStride //rowstride corrects for padding added memory optimization
                val width = image.width
                val height = image.height

                val pixels = IntArray(width * height)
                for(row in 0 until height){
                    val rowStart = row * rowStride
                    for(col in 0 until width){
                        val luma = buffer.get(rowStart + col).toInt() and 0xFF
                        pixels[row * width + col] =
                            if(luma > threshold) Color.RED else Color.TRANSPARENT
                    }
                }

                val overlay = Bitmap.createBitmap(pixels, width, height, Bitmap.Config.ARGB_8888)
                    .rotate(image.imageInfo.rotationDegrees)
                onResult(AnalysisResult.Overlay(overlay))
            } catch(e: Exception){
                Log.e("EfficientDetAnalyzer", "Detection failed", e)
            }
        }
    }
}

internal fun Bitmap.rotate(degrees: Int): Bitmap {
    if(degrees == 0) return this
    val matrix = Matrix().apply { postRotate(degrees.toFloat())}
    return Bitmap.createBitmap(this, 0, 0, width, height, matrix, true)
}