package com.example.a1coursechecklist

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.safeDrawingPadding
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Button
import androidx.compose.material3.OutlinedTextField
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.a1coursechecklist.ui.theme.A1CourseChecklistTheme
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Check
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.DropdownMenuItem
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.ExposedDropdownMenuBox
import androidx.compose.material3.ExposedDropdownMenuDefaults
import androidx.compose.material3.Icon
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.testTag
import io.ktor.client.HttpClient
import io.ktor.client.call.body
import io.ktor.client.engine.android.Android
import io.ktor.client.plugins.contentnegotiation.ContentNegotiation
import io.ktor.client.request.get
import io.ktor.serialization.kotlinx.json.json
import kotlinx.serialization.Serializable

data class ClassInfo(val dep_code: String, val class_num: Int)
data class OptionalClassGroup(val class_choices: List<ClassInfo>)
data class DegreeRequirements(
    val degree_name: String,
    val class_reqs: List<ClassInfo>,
    val class_choice_reqs: List<OptionalClassGroup>
)

/**
 * Data classes and functions for JSON grab/deserialize
 * Note: documenting use of an llm to help me with this approach
 */
@Serializable
data class DegreePlanSummaryDto(val name: String, val path: String)

@Serializable
data class DegreePlanListDto(val plans: List<DegreePlanSummaryDto>)

@Serializable
data class CourseDto(val department: String, val number: String)

@Serializable
data class RequirementDto(
    val type: String,
    val course: CourseDto? = null,
    val courses: List<CourseDto>? = null
)

@Serializable
data class DegreeRequirementsDto(val name: String, val requirements: List<RequirementDto>)


fun CourseDto.toClassInfo(): ClassInfo = ClassInfo(department, number.toIntOrNull() ?: 0)

fun DegreeRequirementsDto.toDegreeRequirements(): DegreeRequirements {
    val required = mutableListOf<ClassInfo>()
    val choiceGroups = mutableListOf<OptionalClassGroup>()

    requirements.forEach { req ->
        when (req.type) {
            "requiredCourse" -> req.course?.let { required.add(it.toClassInfo()) }
            "oneOf" -> req.courses?.let { choiceGroups.add(OptionalClassGroup(it.map { c -> c.toClassInfo() })) }
        }
    }

    return DegreeRequirements(name, required, choiceGroups)
}

class DegreeRepository(private val client: HttpClient) {
    private val baseUrl = "https://msd2026.github.io/degreePlans/"

    suspend fun getAvailablePlans(): List<DegreePlanSummaryDto> {
        return client.get(baseUrl + "degreePlans.json").body<DegreePlanListDto>().plans
    }

    suspend fun getDegreeRequirements(planPath: String): DegreeRequirements {
        return client.get(baseUrl + planPath).body<DegreeRequirementsDto>().toDegreeRequirements()
    }
}

class MyViewModel : ViewModel() {

    private val client = HttpClient(Android) {
        install(ContentNegotiation) {
            json()
        }
    }
    private val repository = DegreeRepository(client)

    private val classesMutable = MutableStateFlow(listOf<ClassInfo>())
    val classesReadOnly: StateFlow<List<ClassInfo>> = classesMutable.asStateFlow()

    private val availablePlansMutable = MutableStateFlow(listOf<DegreePlanSummaryDto>())
    val availablePlansReadOnly: StateFlow<List<DegreePlanSummaryDto>> = availablePlansMutable.asStateFlow()

    private val selectedPlanMutable = MutableStateFlow<DegreePlanSummaryDto?>(null)
    val selectedPlanReadOnly: StateFlow<DegreePlanSummaryDto?> = selectedPlanMutable.asStateFlow()

    private val selectedRequirementsMutable = MutableStateFlow<DegreeRequirements?>(null)
    val selectedRequirementsReadOnly: StateFlow<DegreeRequirements?> = selectedRequirementsMutable.asStateFlow()

    private val errorMutable = MutableStateFlow<String?>(null)
    val errorReadOnly: StateFlow<String?> = errorMutable.asStateFlow()

    init {
        refreshAvailablePlans()
    }

    fun refreshAvailablePlans() {
        viewModelScope.launch {
            runCatching { repository.getAvailablePlans() }
                .onSuccess { availablePlansMutable.value = it }
                .onFailure { errorMutable.value = "Couldn't load degree plan list: ${it.message}" }
        }
    }

    fun selectDegreePlan(plan: DegreePlanSummaryDto) {
        selectedPlanMutable.value = plan
        viewModelScope.launch {
            runCatching { repository.getDegreeRequirements(plan.path) }
                .onSuccess {
                    selectedRequirementsMutable.value = it
                    errorMutable.value = null
                }
                .onFailure { errorMutable.value = "Couldn't load '${plan.name}' requirements: ${it.message}" }
        }
    }

    fun addItem(dep_abbrv: String, class_num: String) {
        classesMutable.value += ClassInfo(dep_abbrv, class_num.toIntOrNull() ?: 0)
    }

    fun dropItem(info: ClassInfo) {
        classesMutable.value -= info
    }

    override fun onCleared() {
        super.onCleared()
        client.close()
    }
}

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContent {
            A1CourseChecklistTheme {
                val vm: MyViewModel = viewModel()

                val myClasses by vm.classesReadOnly.collectAsStateWithLifecycle()
                val availablePlans by vm.availablePlansReadOnly.collectAsStateWithLifecycle()
                val selectedPlan by vm.selectedPlanReadOnly.collectAsStateWithLifecycle()
                val selectedRequirements by vm.selectedRequirementsReadOnly.collectAsStateWithLifecycle()
                val error by vm.errorReadOnly.collectAsStateWithLifecycle()

                Column (
                    modifier = Modifier.safeDrawingPadding().padding(horizontal = 20.dp)
                ){
                    DegreePlanDropdown(
                        plans = availablePlans,
                        selectedPlan = selectedPlan,
                        onPlanSelected = vm::selectDegreePlan
                    )

                    error?.let { Text(it) }

                    selectedRequirements?.let { requirements ->
                        Spacer(Modifier.height(20.dp))
                        DegreeRequirementList(myClasses, requirements)
                    }

                    Spacer(Modifier.height(20.dp))
                    ClassEntry(vm::addItem, vm::dropItem)
                    Spacer(Modifier.height(20.dp))
                    Text("My Classes")
                    MyClassesList(myClasses, vm::addItem, vm::dropItem)
                }
            }
        }
    }
}

@Composable
fun ClassListItem(info: ClassInfo) {
    Text("${info.dep_code} ${info.class_num}")
}

@Preview
@Composable
fun ClassListItemPreview() {
    A1CourseChecklistTheme {
        ClassListItem(ClassInfo("CS", 6018))
    }
}

@Composable
fun OptionalClassListItem(class_options: OptionalClassGroup) {
    Row {
        Text("Choose one from ")
        class_options.class_choices.forEachIndexed { index, info ->
            ClassListItem(info)
            when {
                index == class_options.class_choices.lastIndex - 1 -> Text(" and ")
                index < class_options.class_choices.lastIndex - 1 -> Text(", ")
            }
        }
    }
}

@Preview
@Composable
fun OptionalClassListItemPreview() {
    val options = listOf(
        ClassInfo("CS", 6010),
        ClassInfo("CS", 6011),
        ClassInfo("CS", 6012)
    )
    A1CourseChecklistTheme {
        OptionalClassListItem(OptionalClassGroup(options))
    }
}

@Composable
fun DegreeRequirementList(myClasses: List<ClassInfo>, requirements: DegreeRequirements) {
    val satisfiedText = remember(myClasses, requirements) {
        if (requirementsSatisfied(myClasses, requirements)) "satisfied" else "not satisfied"
    }

    Column {
        Row {
            Text("${requirements.degree_name} degree requirements:")
        }
        Row {
            Text("Requirements are $satisfiedText")
        }
        Row {
            LazyColumn {
                items(requirements.class_reqs) {
                    Row {
                        ClassListItem(it)
                        if (requirementSatisfied(myClasses, it)) BasicCheckmark()
                    }
                }
                items(requirements.class_choice_reqs) {
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
fun MyClassesList(classList: List<ClassInfo>, addItem: (String, String) -> Unit, dropItem: (ClassInfo) -> Unit) {
    Row {
        LazyColumn {
            items(classList) {
                ClassListContainer(it, addItem, dropItem)
            }
        }
    }
}

@Composable
fun ClassListContainer(item: ClassInfo, addItem: (String, String) -> Unit, dropItem: (ClassInfo) -> Unit) {
    var isEditing by remember { mutableStateOf(false) }
    Card(
        modifier = Modifier.fillMaxWidth().padding(vertical = 4.dp),
        elevation = CardDefaults.cardElevation(defaultElevation = 2.dp)
    ){
        Row (
            modifier = Modifier.padding(12.dp),
            horizontalArrangement = Arrangement.spacedBy(8.dp)
        ){
            if (isEditing) {
                Column {
                    ClassEntry(addItem, dropItem, resetListItem = { isEditing = !isEditing }, item)
                    Button(onClick = { isEditing = !isEditing }) { Text("Cancel") }
                }
            } else {
                ClassListItem(item)
                Button(onClick = { isEditing = !isEditing }) { Text("Edit") }
                Button(onClick = { dropItem(item) }) { Text("Remove") }
            }
        }
    }

}

@Composable
fun ClassEntry(
    addItem: (String, String) -> Unit,
    dropItem: (ClassInfo) -> Unit,
    resetListItem: (() -> Unit)? = null,
    prevValues: ClassInfo? = null
) {
    var dep_abbrv_text by remember { mutableStateOf(prevValues?.dep_code ?: "") }
    var class_num_text by remember { mutableStateOf(prevValues?.class_num?.toString() ?: "") }

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
                if (prevValues != null) // when editing, we drop previous values
                    dropItem(prevValues)

                addItem(dep_abbrv_text, class_num_text)
                dep_abbrv_text = ""
                class_num_text = ""

                if (prevValues != null)
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

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun DegreePlanDropdown(
    plans: List<DegreePlanSummaryDto>,
    selectedPlan: DegreePlanSummaryDto?,
    onPlanSelected: (DegreePlanSummaryDto) -> Unit
) {
    var showDropdown by remember { mutableStateOf(false) }

    ExposedDropdownMenuBox(
        expanded = showDropdown,
        onExpandedChange = { showDropdown = !showDropdown }
    ) {
        OutlinedTextField(
            value = selectedPlan?.name ?: "Select degree",
            onValueChange = {},
            readOnly = true,
            label = { Text("Degree") },
            trailingIcon = {
                ExposedDropdownMenuDefaults.TrailingIcon(expanded = showDropdown)
            },
            modifier = Modifier.menuAnchor()
        )

        ExposedDropdownMenu(
            expanded = showDropdown,
            onDismissRequest = { showDropdown = false }
        ) {
            plans.forEach { plan ->
                DropdownMenuItem(
                    text = { Text(plan.name) },
                    onClick = {
                        onPlanSelected(plan)
                        showDropdown = false
                    }
                )
            }
        }
    }
}

fun requirementsSatisfied(myClasses: List<ClassInfo>, requirements: DegreeRequirements): Boolean {
    val satisfiedRequired = myClasses.containsAll(requirements.class_reqs)
    val satisfiedElectives = requirements.class_choice_reqs.isEmpty() ||
            requirements.class_choice_reqs.all { choice ->
                choice.class_choices.any { class_choice -> myClasses.contains(class_choice) }
            }
    return satisfiedRequired && satisfiedElectives
}

fun requirementSatisfied(myClasses: List<ClassInfo>, requiredClass: ClassInfo): Boolean {
    return myClasses.contains(requiredClass)
}
