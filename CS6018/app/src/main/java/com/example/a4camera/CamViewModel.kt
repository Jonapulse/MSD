package com.example.a4camera

import android.content.Context
import androidx.camera.core.Camera
import androidx.camera.core.CameraSelector
import androidx.camera.core.Preview
import androidx.camera.core.SurfaceRequest
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.camera.lifecycle.awaitInstance
import androidx.compose.runtime.currentComposer
import androidx.lifecycle.LifecycleOwner
import androidx.lifecycle.ViewModel
import kotlinx.coroutines.awaitCancellation
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update

class CamViewModel : ViewModel(){
    private val _surfaceRequest = MutableStateFlow<SurfaceRequest?>(null)
    val surfaceRequest: StateFlow<SurfaceRequest?> = _surfaceRequest.asStateFlow()

    private val _cameraSelector = MutableStateFlow(CameraSelector.DEFAULT_BACK_CAMERA)

    private val previewUseCase = Preview.Builder().build().apply {
        setSurfaceProvider{ request ->
            _surfaceRequest.value = request
        }
    }

    suspend fun bindToCamera(appContext: Context, lifecycleOwner: LifecycleOwner){
        val cameraProvider = ProcessCameraProvider.awaitInstance(appContext)
        try{
            _cameraSelector.collect{ selector ->
                cameraProvider.unbindAll()
                cameraProvider.bindToLifecycle(lifecycleOwner, selector, previewUseCase)
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
}