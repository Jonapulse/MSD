package com.example.a4camera

import android.content.ContentValues
import android.content.Context
import android.provider.MediaStore
import android.util.Log
import androidx.camera.core.Camera
import androidx.camera.core.CameraSelector
import androidx.camera.core.ImageAnalysis
import androidx.camera.core.ImageCapture
import androidx.camera.core.ImageCaptureException
import androidx.camera.core.Preview
import androidx.camera.core.SurfaceRequest
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.camera.lifecycle.awaitInstance
import androidx.compose.runtime.currentComposer
import androidx.core.content.ContextCompat
import androidx.lifecycle.LifecycleOwner
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.awaitCancellation
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.map
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch
import java.util.concurrent.Executors

class CamViewModel : ViewModel(){
    private val _surfaceRequest = MutableStateFlow<SurfaceRequest?>(null)
    val surfaceRequest: StateFlow<SurfaceRequest?> = _surfaceRequest.asStateFlow()

    private val _cameraSelector = MutableStateFlow(CameraSelector.DEFAULT_BACK_CAMERA)
    val isFrontCamera: StateFlow<Boolean> = _cameraSelector
        .map{it == CameraSelector.DEFAULT_FRONT_CAMERA }
        .stateIn(viewModelScope, SharingStarted.Eagerly, false)

    private val _analysisMode = MutableStateFlow(AnalysisMode.BRIGHTNESS)
    val analysisMode: StateFlow<AnalysisMode> = _analysisMode.asStateFlow()

    private val _analysisResult = MutableStateFlow<AnalysisResult?>(null)
    val analysisResult: StateFlow<AnalysisResult?> = _analysisResult.asStateFlow()

    private val analysisExecutor = Executors.newSingleThreadExecutor()

    private val previewUseCase = Preview.Builder().build().apply {
        setSurfaceProvider{ request ->
            _surfaceRequest.value = request
        }
    }

    private val imageAnalysisUseCase = ImageAnalysis.Builder()
        .setBackpressureStrategy(ImageAnalysis.STRATEGY_KEEP_ONLY_LATEST)
        .build()

    private val imageCaptureUseCase = ImageCapture.Builder()
        .setCaptureMode(ImageCapture.CAPTURE_MODE_MINIMIZE_LATENCY)
        .build()

    init{
        viewModelScope.launch{
            _analysisMode.collect { mode ->
                _analysisResult.value = null
                imageAnalysisUseCase.setAnalyzer(analysisExecutor, analyzerFor(mode))
            }
        }
    }

    private fun analyzerFor(mode: AnalysisMode): ImageAnalysis.Analyzer = when(mode) {
        AnalysisMode.BRIGHTNESS -> BrightnessAnalyzer(threshold = 120) { result ->
            _analysisResult.value = result
        }
        AnalysisMode.ML_KIT -> ImageAnalysis.Analyzer{ image -> image.close()} //TODO: STUB
        AnalysisMode.EFF_DET -> ImageAnalysis.Analyzer{ image -> image.close()} //TODO: STUB
    }

    fun setAnalysisMode(mode: AnalysisMode){
        _analysisMode.value = mode
    }

    suspend fun bindToCamera(appContext: Context, lifecycleOwner: LifecycleOwner){
        val cameraProvider = ProcessCameraProvider.awaitInstance(appContext)
        try{
            _cameraSelector.collect{ selector ->
                cameraProvider.unbindAll()
                cameraProvider.bindToLifecycle(lifecycleOwner, selector, previewUseCase, imageAnalysisUseCase, imageCaptureUseCase)
            }
        } finally {
            cameraProvider.unbindAll()
        }
    }

    fun toggleCamera()
    {
        _cameraSelector.update { current ->
            if(current == CameraSelector.DEFAULT_BACK_CAMERA) CameraSelector.DEFAULT_FRONT_CAMERA
            else CameraSelector.DEFAULT_BACK_CAMERA
        }
    }

    fun takePicture(appContext: Context)
    {
        val name = "DemoPic" + System.currentTimeMillis()

        val contentValues = ContentValues().apply {
            put(MediaStore.MediaColumns.DISPLAY_NAME, name)
            put(MediaStore.MediaColumns.MIME_TYPE, "image/jpeg")
            put(MediaStore.Images.Media.RELATIVE_PATH, "Pictures/A4Camera")
        }

        val metadata = ImageCapture.Metadata().apply {
            isReversedHorizontal = _cameraSelector.value == CameraSelector.DEFAULT_FRONT_CAMERA
        }

        val outputOptions = ImageCapture.OutputFileOptions.Builder(
            appContext.contentResolver,
            MediaStore.Images.Media.EXTERNAL_CONTENT_URI,
            contentValues
        ).setMetadata(metadata).build()

        imageCaptureUseCase.takePicture(
            outputOptions,
            ContextCompat.getMainExecutor(appContext),
            object : ImageCapture.OnImageSavedCallback {
                override fun onImageSaved(output: ImageCapture.OutputFileResults) {
                    Log.d("CamViewModel", "Capture saved! To: ${output.savedUri}")
                }

                override fun onError(exception: ImageCaptureException){
                    Log.e("CamViewModel", "Capture failed...", exception)
                }
            }
        )
    }
}