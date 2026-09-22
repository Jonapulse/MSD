package com.example.a3maraca

import android.app.Application
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.viewModelScope
import com.example.a3maraca.data.ShakeDatabase
import com.example.a3maraca.data.ShakeEvent
import com.example.a3maraca.shake.ShakeDetector
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch

class ShakeViewModel(application: Application) : AndroidViewModel(application) {

    private val dao = ShakeDatabase.getInstance(application).shakeDao()

    // Minimum time between accepted shakes.
    private val cooldownMillis = 25L
    private var lastShakeTime = 0L

    // Bumped every time a shake is *accepted* (i.e. passes the cooldown).
    // The Canvas observes this and fires its animation on change.
    private val _shakeTrigger = MutableStateFlow(0)
    val shakeTrigger: StateFlow<Int> = _shakeTrigger.asStateFlow()

    val shakeDetector = ShakeDetector(application) { onShakeDetected() }

    private fun onShakeDetected() {
        val now = System.currentTimeMillis()
        if (now - lastShakeTime < cooldownMillis) return
        lastShakeTime = now

        viewModelScope.launch {
            dao.insert(ShakeEvent(timestamp = now))
            _shakeTrigger.value += 1
        }
    }
}
