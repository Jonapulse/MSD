package com.example.a3maracas

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.animation.core.Animatable
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
import androidx.compose.ui.res.imageResource
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.a3maracas.ui.theme.A3MaracasTheme

class MaracasViewModel : ViewModel() {
    var shakes by mutableStateOf(0)
        private set
    var shakeVelocity by mutableStateOf(0f)
        private set

    fun shake(velocity: Float = 1f){
        shakes++
        shakeVelocity = velocity
    }
}

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            A3MaracasTheme {
                val myVm: MaracasViewModel = viewModel()

                Scaffold(modifier = Modifier.fillMaxSize(),
                    bottomBar = {
                        MaracasButtons(
                            shakes = myVm.shakes,
                            onShake = {myVm.shake()}
                        )
                    }
                ) { innerPadding ->
                    MaracasDisplay(
                        shakes = myVm.shakes,
                        modifier = Modifier.padding(innerPadding))
                }
            }
        }
    }
}

@Composable
fun MaracasDisplay(shakes: Int, modifier: Modifier = Modifier){
    val maracas = ImageBitmap.imageResource(R.drawable.maracas)
    val rotation = remember {Animatable(0f)}

    LaunchedEffect(shakes) {
        if(shakes == 0) return@LaunchedEffect
        rotation.animateTo(30f, tween(80))
        rotation.animateTo(-60f, tween(160))
        rotation.animateTo(0f, tween(80))
    }

    Canvas(modifier.fillMaxSize()){
        val center = Offset(size.width / 2, size.height / 2)
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

@Preview(showBackground = true)
@Composable
fun MaracasPreview() {
    A3MaracasTheme {
        MaracasDisplay(1)
    }
}

@Composable
fun MaracasButtons(shakes: Int, onShake: () -> Unit) {
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
        Button( onClick = onShake )
        {
            Text("Forget old shakes (1 min)")
        }
    }
}

@Preview
@Composable
fun MaracasButtonPreview()
{
    A3MaracasTheme {
        MaracasButtons(shakes = 3, onShake = {})
    }
}

