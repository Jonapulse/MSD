package com.example.classfollowallong

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.classfollowallong.ui.theme.ClassFollowAllongTheme
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch
import kotlin.time.Duration.Companion.milliseconds


class MyViewModel : ViewModel()
{
    private val dataMutable = MutableStateFlow("Blank")
    val data: StateFlow<String> = dataMutable;

    fun fetchData()
    {
        viewModelScope.launch{
            dataMutable.value = "Loading . . . ."
            delay(10000.milliseconds)
            dataMutable.value = "Weather updated"
        }
    }

//    private val taskMutable = MutableStateFlow(listOf<String>)
//    val tasksReadOnly : StateFlow<List<String>>
}
class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            ClassFollowAllongTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Greeting(
                        name = "Android",
                        modifier = Modifier.padding(innerPadding)
                    )
                }
            }
        }
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
    Button(onClick = { myVM.fetchData() }
        Text("Load Data")
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    ClassFollowAllongTheme {
        Greeting("Android")
    }
}