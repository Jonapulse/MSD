package com.example.a4camera

import android.Manifest
import android.content.pm.PackageManager
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.camera.compose.CameraXViewfinder
import androidx.compose.foundation.Canvas
import androidx.compose.foundation.Image
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.statusBarsPadding
import androidx.compose.material3.Button
import androidx.compose.material3.FilterChip
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
import androidx.compose.ui.geometry.Size
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.asImageBitmap
import androidx.compose.ui.graphics.drawscope.Stroke
import androidx.compose.ui.graphics.graphicsLayer
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.drawText
import androidx.compose.ui.text.rememberTextMeasurer
import androidx.compose.ui.unit.dp
import androidx.core.content.ContextCompat
import androidx.lifecycle.compose.LocalLifecycleOwner
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel
import kotlin.math.max

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
            val mode by viewModel.analysisMode.collectAsStateWithLifecycle()

            CameraPreview(modifier = Modifier, viewModel = viewModel)
            AnalysisOverlay(modifier = Modifier.fillMaxSize(), viewModel = viewModel)

            Row(
                modifier = Modifier
                    .align(Alignment.TopCenter)
                    .statusBarsPadding()
                    .padding(top = 16.dp),
                horizontalArrangement = Arrangement.spacedBy(8.dp)
            ) {
                AnalysisMode.entries.forEach { m ->
                    FilterChip(
                        selected = mode == m,
                        onClick = { viewModel.setAnalysisMode(m) },
                        label = { Text(m.name) }
                    )
                }
            }
            Row(modifier = Modifier
                .align(Alignment.BottomCenter)
                .padding(bottom = 32.dp), horizontalArrangement = Arrangement.spacedBy(8.dp)) {
                SwapButton(
                    modifier = Modifier,
                    viewModel::toggleCamera
                )
                Button(onClick = {viewModel.takePicture(context.applicationContext)})
                { Text("Take Picture")}
            }
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
fun AnalysisOverlay(modifier: Modifier = Modifier, viewModel: CamViewModel)
{
    val result by viewModel.analysisResult.collectAsStateWithLifecycle()
    val isFront by viewModel.isFrontCamera.collectAsStateWithLifecycle()
    val textMeasurer = rememberTextMeasurer()

    when (val r = result){
        is AnalysisResult.Overlay -> Image(
            bitmap = r.bitmap.asImageBitmap(),
            contentDescription = null,
            contentScale = ContentScale.Crop,
            modifier = modifier.graphicsLayer{scaleX = if (isFront) -1f else 1f}
        )
        is AnalysisResult.Detections -> Canvas(modifier = modifier) {
            // Same math as ContentScale.Crop: scale to cover, then center
            val scale = max(size.width / r.imageWidth, size.height / r.imageHeight)
            val dx = (size.width - r.imageWidth * scale) / 2f
            val dy = (size.height - r.imageHeight * scale) / 2f

            r.boxes.forEach { det ->
                var left = det.box.left * scale + dx
                var right = det.box.right * scale + dx
                if (isFront) {
                    val mirroredLeft = size.width - right
                    right = size.width - left
                    left = mirroredLeft
                }
                val top = det.box.top * scale + dy
                val bottom = det.box.bottom * scale + dy

                drawRect(
                    color = Color.Red,
                    topLeft = Offset(left, top),
                    size = Size(right - left, bottom - top),
                    style = Stroke(width = 4.dp.toPx())
                )
                drawText(
                    textMeasurer = textMeasurer,
                    text = "${det.label} ${(det.score * 100).toInt()}%",
                    topLeft = Offset(left, top),
                    style = TextStyle(color = Color.White, background = Color.Red)
                )
            }
        }
        null -> Unit
    }
}

@Composable
fun SwapButton(modifier: Modifier = Modifier, toggleCamera: () -> Unit){
    Button(onClick = { toggleCamera(); }, modifier = modifier) {
        Text("Swap")
    }
}