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
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.a1coursechecklist.ui.theme.A1CourseChecklistTheme
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow

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

                    DegreeRequirementList(vm,getDefaultRecList())
                    Spacer(Modifier.height(20.dp))
                    //TODO: text edit and swap
                    //ClassModButton(vm)
                    ClassEntry(vm)
                    Spacer(Modifier.height(20.dp))
                    Text("My Classes")
                    MyClassesList (vm)
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
fun DegreeRequirementList(myVM: MyViewModel, requirements: DegreeRequirements)
{
    Column{
        Row{
            Text("${requirements.degree_name} degree requirements:")
        }
        Row{
            val satisfiedText = if(requirementsSatisfied(myVM, requirements)) "satisfied" else "not satisfied"
            Text("Requirements are $satisfiedText")
        }
        Row{
            LazyColumn() {
                items(requirements.class_reqs){
                    ClassListItem(it)
                }
                items(requirements.class_choice_reqs){
                    OptionalClassListItem(it)
                }
            }
        }
    }
}

@Preview
@Composable
fun DegreeRequirementListPreview()
{
    //DegreeRequirementList(getDefaultRecList())
}

@Composable
fun MyClassesList(myVM: MyViewModel)
{
    val classList by myVM.classesReadOnly.collectAsState()

    Row{
        LazyColumn() {
            items(classList){
                ClassListContainer(myVM, it)
            }
        }
    }
}

@Composable
fun ClassListContainer(myVM: MyViewModel, item: ClassInfo)
{
    Row{
        ClassListItem(item)
        Button(onClick = {
            myVM.dropItem(item)
        }){Text("Remove")}
    }
}

@Composable
fun ClassModButton(myVM: MyViewModel)
{
    val classList by myVM.classesReadOnly.collectAsState()

    Button(onClick = {
        //myVM.addItem(dep_abbrv_text, class_num_text)
        myVM.addItem("Test", "101")
    }){Text("Add Class")}
}

@Composable
fun ClassEntry(myVM: MyViewModel)
{
    var dep_abbrv_text by remember {mutableStateOf("")}
    var class_num_text by remember {mutableStateOf("")}

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
                myVM.addItem(dep_abbrv_text, class_num_text)
                dep_abbrv_text = ""
                class_num_text = ""
            }) { Text("Add Class") }
        }
        Column {
            Button(onClick = {
                //TODO: Toggle back
            }) { Text("Cancel") }
        }
    }
}


fun getDefaultRecList() : DegreeRequirements
{
    return DegreeRequirements(
        degree_name = "Software Development",
        class_reqs = listOf(
            ClassInfo("CS", 6010),
            ClassInfo("CS", 6011),
            ClassInfo("CS", 6012),
            ClassInfo("CS", 6013),
            ClassInfo("CS", 6014),
            ClassInfo("CS", 6015),
            ClassInfo("CS", 6016),
            ClassInfo("CS", 6017),
            ClassInfo("CS", 6018)
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

fun requirementsSatisfied(myVM: MyViewModel, requirements: DegreeRequirements) : Boolean
{
    val myClasses = myVM.classesReadOnly.value
    val satisfiedRequired = myClasses.containsAll(requirements.class_reqs)
    val satisfiedElectives = requirements.class_choice_reqs.isEmpty() ||
            requirements.class_choice_reqs.all{choice -> choice.class_choices.any{
                class_choice -> myClasses.contains((class_choice))
            }}
    return satisfiedRequired && satisfiedElectives
}