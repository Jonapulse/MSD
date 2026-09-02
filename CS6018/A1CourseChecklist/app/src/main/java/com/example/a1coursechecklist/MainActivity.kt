package com.example.a1coursechecklist

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.a1coursechecklist.ui.theme.A1CourseChecklistTheme

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            A1CourseChecklistTheme {
                DegreeRequirementList(getDefaultList())
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
fun DegreeRequirementList(requirements: DegreeRequirements)
{
    Column{
        Row{
            Text("${requirements.degree_name} degree requirements:")
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
    DegreeRequirementList(getDefaultList())
}

fun getDefaultList() : DegreeRequirements
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