package com.example.a4camera

import android.graphics.RectF
import android.util.Log
import androidx.annotation.OptIn
import androidx.camera.core.ExperimentalGetImage
import androidx.camera.core.ImageAnalysis
import androidx.camera.core.ImageProxy
import com.google.mlkit.vision.common.InputImage
import com.google.mlkit.vision.objects.ObjectDetection
import com.google.mlkit.vision.objects.defaults.ObjectDetectorOptions
import java.io.Closeable

class MlKitAnalyzer(
    private val onResult: (AnalysisResult) -> Unit
) : ImageAnalysis.Analyzer, Closeable {
    private val detector = ObjectDetection.getClient(
        ObjectDetectorOptions.Builder()
            .setDetectorMode(ObjectDetectorOptions.STREAM_MODE)
            .enableMultipleObjects()
            .enableClassification()
            .build()
    )

    @OptIn(ExperimentalGetImage::class)
    override fun analyze(image: ImageProxy){
        val mediaImage = image.image ?: run { image.close(); return}
        val rotation = image.imageInfo.rotationDegrees
        val input = InputImage.fromMediaImage(mediaImage, rotation)

        val (uprightW, uprightH) =
            if (rotation % 180 == 0) image.width to image.height
            else image.height to image.width

        detector.process(input)
            .addOnSuccessListener { objects ->
                val boxes = objects.map { obj ->
                    val best = obj.labels.maxByOrNull { it.confidence }
                    DetectionBox(
                        RectF(obj.boundingBox),
                        best?.text ?: "Object",
                        best?.confidence ?: 0f
                    )
                }
                onResult(AnalysisResult.Detections(boxes, uprightW, uprightH))
            }
            .addOnFailureListener { e -> Log.e("MlKitAnalyzer", "Detection failed", e)}
            .addOnCompleteListener { image.close() }
    }

    override fun close() = detector.close()
}