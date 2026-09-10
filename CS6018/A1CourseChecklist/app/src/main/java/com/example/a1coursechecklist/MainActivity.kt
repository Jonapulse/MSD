package com.example.a1coursechecklist

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Button
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.lifecycle.ViewModel
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.a1coursechecklist.ui.theme.A1CourseChecklistTheme
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Check
import androidx.compose.material3.Icon
import androidx.compose.ui.graphics.Color

class MyViewModel : ViewModel()
{
    private val classesMutable = MutableStateFlow(listOf<ClassInfo>())
    val classesReadOnly : StateFlow<List<ClassInfo>> = classesMutable.asStateFlow()
    fun addItem(dep_abbrv:String, class_num:String)
    {
        classesMutable.value += ClassInfo(dep_abbrv, class_num.toIntOrNull()?:0)
    }
    fun dropItem(info: ClassInfo)
    {
        classesMutable.value -= info
    }
}


class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            A1CourseChecklistTheme {
                Column{
                    val vm: com.example.a1coursechecklist.MyViewModel = viewModel()

                    DegreeRequirementList(vm.classesReadOnly.collectAsStateWithLifecycle().value,getDefaultRecList())
                    Spacer(Modifier.height(20.dp))
                    ClassEntry(vm::addItem, vm::dropItem)
                    Spacer(Modifier.height(20.dp))
                    Text("My Classes")
                    MyClassesList (vm.classesReadOnly.collectAsStateWithLifecycle().value, vm::addItem, vm::dropItem)
                }
            }
        }
    }
}


data class ClassInfo(val dep_code: String, val class_num: Int )
data class OptionalClassGroup(val class_choices: List<ClassInfo>)
data class DegreeRequirements(val degree_name: String, val class_reqs: List<ClassInfo>, val class_choice_reqs: List<OptionalClassGroup>)

@Composable
fun ClassListItem(info: ClassInfo)
{
    Text("${info.dep_code} ${info.class_num}")
}

@Preview
@Composable
fun ClassListItemPreview()
{
    A1CourseChecklistTheme() {
        ClassListItem(ClassInfo("CS", 6018))
    }
}

@Composable
fun OptionalClassListItem(class_options: OptionalClassGroup)
{
    Row{
        Text("Choose one from ")
        class_options.class_choices.forEachIndexed { index, info ->
            ClassListItem(info)
            when{
                index == class_options.class_choices.lastIndex - 1 -> Text(" and ")
                index < class_options.class_choices.lastIndex - 1 -> Text(", ")
            }
        }
    }
}

@Preview
@Composable
fun OptionalClassListItemPreview()
{
    val options = listOf(
        ClassInfo("CS", 6010),
        ClassInfo("CS", 6011),
        ClassInfo("CS", 6012)
    )
    A1CourseChecklistTheme() {
        OptionalClassListItem(OptionalClassGroup(options))
    }
}

@Composable
fun DegreeRequirementList(myClasses: List<ClassInfo>, requirements: DegreeRequirements)
{
    val satisfiedText = remember(myClasses, requirements){
        if(requirementsSatisfied(myClasses, requirements)) "satisfied" else "not satisfied"
    }

    Column{
        Row{
            Text("${requirements.degree_name} degree requirements:")
        }
        Row{
            Text("Requirements are $satisfiedText")
        }
        Row{
            LazyColumn() {
                items(requirements.class_reqs){
                    Row {
                        ClassListItem(it)
                        if (requirementSatisfied(myClasses, it)) BasicCheckmark()
                    }
                }
                items(requirements.class_choice_reqs){
                    Row {
                        OptionalClassListItem(it)
                        if (it.class_choices.any { classReq ->
                                requirementSatisfied(myClasses, classReq)
                            }) BasicCheckmark()
                    }
                }
            }
        }
    }
}

@Composable
fun MyClassesList(classList: List<ClassInfo>, addItem: (String, String) -> Unit, dropItem: (ClassInfo) -> Unit)
{
    Row{
        LazyColumn() {
            items(classList){
                ClassListContainer(it, addItem, dropItem)
            }
        }
    }
}

@Composable
fun ClassListContainer(item: ClassInfo, addItem: (String, String) -> Unit, dropItem: (ClassInfo) -> Unit)
{
    var isEditing by remember {mutableStateOf(false)}
    Row{
        if(isEditing)
        {
            Column {
                ClassEntry(addItem, dropItem, resetListItem = { isEditing = !isEditing }, item)
                Button(onClick = { isEditing = !isEditing }) { Text("Cancel") }
            }
        }
        else
        {
            ClassListItem(item)
            Button(onClick = { isEditing = !isEditing }){Text("Edit")}
            Button(onClick = {
                dropItem(item)
            }){Text("Remove")}
        }
    }
}

@Composable
fun ClassEntry(addItem: (String, String) -> Unit, dropItem: (ClassInfo) -> Unit, resetListItem : (() -> Unit) ? = null, prevValues: ClassInfo? = null)
{
    var dep_abbrv_text by remember {mutableStateOf(prevValues?.dep_code?:"")}
    var class_num_text by remember {mutableStateOf(prevValues?.class_num.toString()?:"")}

    Row {
        Column {
            Text("Dept Abbrv")
            OutlinedTextField(
                value = dep_abbrv_text,
                onValueChange = { newText -> dep_abbrv_text = newText }
            )
        }
        Column {
            Text("Class Num")
            OutlinedTextField(
                value = class_num_text,
                onValueChange = { newText -> class_num_text = newText }
            )
        }
    }
    Row {
        Column {
            Button(onClick = {
                if(prevValues != null) //when editing, we drop previous values
                    dropItem(prevValues)

                addItem(dep_abbrv_text, class_num_text)
                dep_abbrv_text = ""
                class_num_text = ""

                if(prevValues != null)
                    resetListItem?.invoke()

            }) { Text("Add Class") }
        }
    }
}

@Composable
fun BasicCheckmark(modifier: Modifier = Modifier) {
    Icon(
        imageVector = Icons.Default.Check,
        contentDescription = "Checkmark", // Crucial for screen readers
        tint = Color.Green // Optional: Defaults to the local text/content color
    )
}


fun getDefaultRecList() : DegreeRequirements
{
    return DegreeRequirements(
        degree_name = "Software Development",
        class_reqs = listOf(
            ClassInfo("CS", 6010),
            ClassInfo("CS", 6011),
            ClassInfo("CS", 6012)
        ),
        class_choice_reqs = listOf(
            OptionalClassGroup(listOf(
                ClassInfo("CS", 6019),
                ClassInfo("CS", 6020))),
            OptionalClassGroup(listOf(
                ClassInfo("CS", 4050),
                ClassInfo("CS", 4150),
                ClassInfo("CS", 4250)))
        )
    )
}

fun requirementsSatisfied(myClasses: List<ClassInfo>, requirements: DegreeRequirements) : Boolean
{
    val satisfiedRequired = myClasses.containsAll(requirements.class_reqs)
    val satisfiedElectives = requirements.class_choice_reqs.isEmpty() ||
            requirements.class_choice_reqs.all{choice -> choice.class_choices.any{
                class_choice -> myClasses.contains((class_choice))
            }}
    return satisfiedRequired && satisfiedElectives
}

fun requirementSatisfied(myClasses: List<ClassInfo>, requiredClass: ClassInfo) : Boolean
{
    return myClasses.contains(requiredClass)
}