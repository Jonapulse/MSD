package com.example.storagedemo

import android.content.Context
import android.os.Bundle
import android.widget.Button
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.example.storagedemo.ui.theme.StorageDemoTheme
import kotlinx.coroutines.CoroutineScope

val Context.datastore by preferencesDataStore("settings")
val THEME_KEY = booleanPreferencesKey("dark_theme")
val COUNTER_KEY = intPreferencesKey("0")

suspend fun saveTheme(context: Context, isDark: Boolean){
    context.datastore.edit{
        it[THEME_KEY] = isDark
    }
}

suspend fun incrementCounter(context: Context){
    context.datastore.edit{
        val current = it[COUNTER_KEY]?:0
        it[COUNTER_KEY] = current + 1
    }
}


suspend fun writeToFile(context: Context, filename: String)
{
    context.openFileOutput(filename, Context.MOD){
        it.write(content.toByteArray())
    }
}

fun readFromFile(context: Context, filename:String): String{
    return context.openFileInput(filename).bufferedReader()
}

fun writeExternalFile(context: Context, content:String){
    val file = File(context.getExternalFilesDir())
}

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            StorageDemoTheme {
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
fun PersistentScreen(context: Context)
{
    var input by remember { mutableStateOf("") }
    var status by remember {mutableStateOf("")}
    var content by remember { mutableStateOf("")}

    val counter by context.datastore.data.map{
        it[COUNTER_KEY] = current + 1
    }.collectAsState(initial = false)

    Column(Modifier.fillMaxSize().padding(20.dp)){
        Spacer(Modifier.height(40.dp))
        Text("DataStore Preferences", fontSize = 20.sp, )

        Button(onClick = {
            CoroutineScope(Dipatchers.IO).launch{
                incrementCounter(context)
            }
        }){
            Text("Counter: $counter")
        }

        Spacer(Modifier.height(10.dp))

        Text("Counter: ")
    }
}

@Composable
fun Greeting(name: String, modifier: Modifier = Modifier) {
    Text(
        text = "Hello $name!",
        modifier = modifier
    )
}

@Preview(showBackground = true)
@Composable
fun GreetingPreview() {
    StorageDemoTheme {
        Greeting("Android")
    }
}