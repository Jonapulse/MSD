package com.example.a1coursechecklist

import org.junit.Test

import org.junit.Assert.*


class BusinessLogic {
    @Test
    fun validateRequirementCheck()
    {
        val defaultRecs = getDefaultRecList()

        val myClassList = defaultRecs.class_reqs + defaultRecs.class_choice_reqs.map { it.class_choices.first() }
        val incompleteList = defaultRecs.class_reqs

        assertTrue(requirementsSatisfied(myClassList, defaultRecs))
        assertFalse(requirementsSatisfied(incompleteList, defaultRecs))
    }

    @Test
    fun validatePerClassReqCheck()
    {
        val classInfo = ClassInfo("CS", 101)
        val missingClass = ClassInfo("ART", 304)
        val myClasses = listOf(classInfo, classInfo,classInfo)

        assertTrue(requirementSatisfied(myClasses, classInfo))
        assertFalse(requirementSatisfied(myClasses, missingClass))
    }
}