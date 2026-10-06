package com.example.a4camera

import android.content.Context
import androidx.camera.core.ImageAnalysis
import androidx.camera.core.ImageProxy
import com.google.mediapipe.framework.image.BitmapImageBuilder
import com.google.mediapipe.tasks.core.BaseOptions
import com.google.mediapipe.tasks.vision.core.RunningMode
import com.google.mediapipe.tasks.vision.objectdetector.ObjectDetector
import java.io.Closeable

class EfficientDetAnalyzer(
    private val appContext: Context,
    private val onResult: (AnalysisResult) -> Unit
) : ImageAnalysis.Analyzer, Closeable {

    private var detector: ObjectDetector? = null

    private fun createDetector(): ObjectDetector {
        val options = ObjectDetector.ObjectDetectorOptions.builder()
            .setBaseOptions(
                BaseOptions.builder().setModelAssetPath("efficientdet_lite4.tflite").build()
            )
            .setRunningMode(RunningMode.IMAGE)
            .setScoreThreshold(0.4f)
            .setMaxResults(5)
            .build()
        return ObjectDetector.createFromOptions(appContext, options)
    }

    override fun analyze(image: ImageProxy) {
        image.use {
            val d = detector ?: createDetector().also { detector = it }
            val bitmap = image.toBitmap().rotate(image.imageInfo.rotationDegrees)
            val result = d.detect(BitmapImageBuilder(bitmap).build())

            val boxes = result.detections().map { det ->
                val top = det.categories().firstOrNull()
                DetectionBox(det.boundingBox(), top?.categoryName() ?: "?", top?.score() ?: 0f)
            }
            onResult(AnalysisResult.Detections(boxes, bitmap.width, bitmap.height))
        }
    }

    override fun close() {
        detector?.close()
        detector = null
    }
}