package com.example.a4camera

import android.Manifest
import android.content.pm.PackageManager
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.camera.compose.CameraXViewfinder
import androidx.camera.core.CameraSelector
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.navigationBarsPadding
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.unit.dp
import androidx.core.content.ContextCompat
import androidx.lifecycle.compose.LocalLifecycleOwner
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel

@Composable
fun CameraScreen(modifier : Modifier, viewModel: CamViewModel = viewModel()){
    val context = LocalContext.current
    var hasPermission by remember{
        mutableStateOf(
            ContextCompat.checkSelfPermission(context, Manifest.permission.CAMERA) ==
                    PackageManager.PERMISSION_GRANTED
        )
    }
    val permissionLauncher = rememberLauncherForActivityResult(
        ActivityResultContracts.RequestPermission()
    ) { granted -> hasPermission = granted }

    LaunchedEffect(Unit){
        if(!hasPermission) permissionLauncher.launch(Manifest.permission.CAMERA)
    }

    if(hasPermission){
        Box( modifier = Modifier.fillMaxSize()){
            CameraPreview(modifier = Modifier, viewModel = viewModel)
            SwapButton(modifier = Modifier
                .align(Alignment.BottomCenter)
                .padding(bottom = 32.dp),
            viewModel::toggleCamera)
        }
    } else {
        Text("Camera permission is required.", modifier = modifier)
    }
}

@Composable
fun CameraPreview(modifier: Modifier = Modifier, viewModel: CamViewModel){
    val surfaceRequest by viewModel.surfaceRequest.collectAsStateWithLifecycle()
    val context = LocalContext.current
    val lifecycleOwner = LocalLifecycleOwner.current

    LaunchedEffect(lifecycleOwner) {
        viewModel.bindToCamera(context.applicationContext, lifecycleOwner)
    }

    surfaceRequest?.let{ request ->
        CameraXViewfinder(
            surfaceRequest = request,
            modifier = modifier.fillMaxSize()
        )
    }
}

@Composable
fun SwapButton(modifier: Modifier = Modifier, toggleCamera: () -> Unit){
    var camFaceForward by remember {mutableStateOf(true)}
    Button(onClick = {
        camFaceForward = !camFaceForward;
        toggleCamera();
    }, modifier = modifier) {
        Text("Swap")
    }
}