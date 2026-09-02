package com.example.coroutinesdemo

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import com.example.coroutinesdemo.ui.theme.ComposeDEMOTheme
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.material3.OutlinedTextField
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.rememberCoroutineScope
import androidx.compose.ui.Alignment
import androidx.compose.ui.text.font.FontFamily
import androidx.compose.ui.text.font.FontWeight
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.compose.viewModel
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.launch
import kotlin.time.Duration.Companion.milliseconds

class MyViewModel : ViewModel()
{

    private val dataMutable = MutableStateFlow("Blank")
    val data: StateFlow<String> = dataMutable

    // Simulate talking to an external server

    fun fetchData()
    {
        viewModelScope.launch {
            dataMutable.value = "Loading . . . . "
            delay (10000.milliseconds)
            dataMutable.value = "Weather updated"
        }
    }

    // To-do List Model
    private val taskMutable = MutableStateFlow(listOf<String>())
    val tasksReadOnly : StateFlow<List<String>> = taskMutable

    // VM Methods
     suspend fun addItem (item: String){

        delay(500.milliseconds)
        taskMutable.value += item
    }
}

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            ComposeDEMOTheme {
               val vm:MyViewModel = viewModel()
               TodoList (vm)
            }
        }
    }
}

@Composable
fun TodoList(myVM: MyViewModel) {
    Column(Modifier.fillMaxWidth().padding(50.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.Center) {
        val scope = rememberCoroutineScope ()
        val observableList by myVM.tasksReadOnly.collectAsState()
        val dataObservable by myVM.data.collectAsState()

        var itemText by remember { mutableStateOf("") }


        Row {
            OutlinedTextField(
                value = itemText,
                onValueChange = { newText -> itemText = newText},
                label = { Text("Item") }
            )
        }
        Row {
            Button(onClick = {
                scope.launch {
                    myVM.addItem(itemText)
                    itemText = ""
                }

            }) {
                Text("Add Item")
            }
        }
        Spacer(Modifier.height(20.dp))
        Text("ToDo List", fontSize = 25.sp, fontWeight = FontWeight.ExtraBold, color = Color.Blue)
        Row{
            LazyColumn {
                items(observableList) { Text(it,
                    fontSize = 20.sp,
                    fontFamily = FontFamily.SansSerif,
                    fontWeight = FontWeight.Bold) }
            }
        }
        Spacer(Modifier.height(40.dp))
        Button(onClick = { myVM.fetchData() }) {
            Text("Load Data")
        }
        Text("Result: $dataObservable")
    }
}

