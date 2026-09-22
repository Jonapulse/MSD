package com.example.a3maraca

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.activity.viewModels
import androidx.compose.animation.core.Animatable
import androidx.compose.animation.core.tween
import androidx.compose.foundation.Canvas
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.runtime.Composable
import androidx.compose.runtime.DisposableEffect
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalLifecycleOwner
import androidx.lifecycle.Lifecycle
import androidx.lifecycle.LifecycleEventObserver
import com.example.a3maraca.ui.theme.A3MaracaTheme

class MainActivity : ComponentActivity() {

    private val viewModel: ShakeViewModel by viewModels()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            A3MaracaTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    ShakeScreen(
                        viewModel = viewModel,
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
        }
    }
}

@Composable
fun ShakeScreen(viewModel: ShakeViewModel, modifier: Modifier = Modifier) {
    // Only listen while the activity is actually visible.
    val lifecycleOwner = LocalLifecycleOwner.current
    DisposableEffect(lifecycleOwner) {
        val observer = LifecycleEventObserver { _, event ->
            when (event) {
                Lifecycle.Event.ON_RESUME -> viewModel.shakeDetector.start()
                Lifecycle.Event.ON_PAUSE -> viewModel.shakeDetector.stop()
                else -> {}
            }
        }
        lifecycleOwner.lifecycle.addObserver(observer)
        onDispose { lifecycleOwner.lifecycle.removeObserver(observer) }
    }

    val shakeTrigger by viewModel.shakeTrigger.collectAsState()
    val scale = remember { Animatable(1f) }

    // Every time shakeTrigger changes (a shake was recorded), pulse the circle.
    LaunchedEffect(shakeTrigger) {
        if (shakeTrigger == 0) return@LaunchedEffect
        scale.snapTo(1f)
        scale.animateTo(targetValue = 1.6f, animationSpec = tween(durationMillis = 150))
        scale.animateTo(targetValue = 1f, animationSpec = tween(durationMillis = 250))
    }

    Canvas(modifier = modifier.fillMaxSize()) {
        val radius = (size.minDimension / 4f) * scale.value
        drawCircle(
            color = Color(0xFFE07A29),
            radius = radius,
            center = Offset(size.width / 2f, size.height / 2f)
        )
    }
}