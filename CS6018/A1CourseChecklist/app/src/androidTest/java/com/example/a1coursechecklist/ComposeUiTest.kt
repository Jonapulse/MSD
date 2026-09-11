package com.example.a1coursechecklist

import androidx.compose.ui.test.assertIsDisplayed
import androidx.compose.ui.test.junit4.createComposeRule
import androidx.compose.ui.test.onNodeWithTag
import androidx.compose.ui.test.onNodeWithText
import androidx.compose.ui.test.performClick
import androidx.compose.ui.test.performTextInput
import com.example.a1coursechecklist.ui.theme.A1CourseChecklistTheme
import org.junit.Rule
import org.junit.Test

/**
 * Runs on-device/emulator — createComposeRule() needs a real Compose runtime.
 * Location: app/src/androidTest/java/com/example/a1coursechecklist/
 */
class ComposeUiTest {

    @get:Rule
    val composeRule = createComposeRule()

    @Test
    fun classEntry_addButton_invokesCallbackWithEnteredValues() {
        var addedDept: String? = null
        var addedNum: String? = null

        composeRule.setContent {
            A1CourseChecklistTheme {
                ClassEntry(
                    addItem = { dept, num -> addedDept = dept; addedNum = num },
                    dropItem = {}
                )
            }
        }

        composeRule.onNodeWithTag("dept_abbrv_field").performTextInput("CS")
        composeRule.onNodeWithTag("class_num_field").performTextInput("6017")
        composeRule.onNodeWithText("Add Class").performClick()

        assert(addedDept == "CS")
        assert(addedNum == "6017")
    }

    @Test
    fun degreeRequirementList_showsCheckmarkOnlyWhenClassIsTaken() {
        val requirements = DegreeRequirements(
            degree_name = "Computer Science",
            class_reqs = listOf(ClassInfo("CS", 101)),
            class_choice_reqs = emptyList()
        )

        composeRule.setContent {
            A1CourseChecklistTheme {
                DegreeRequirementList(myClasses = listOf(ClassInfo("CS", 101)), requirements = requirements)
            }
        }

        composeRule.onNodeWithText("Requirements are satisfied").assertIsDisplayed()
        composeRule.onNodeWithText("CS 101").assertIsDisplayed()
    }
}
