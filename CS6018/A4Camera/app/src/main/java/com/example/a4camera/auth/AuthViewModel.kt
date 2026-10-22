package com.example.a4camera.auth

import android.util.Log
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.a4camera.network.ApiException
import com.example.a4camera.network.ServerApi
import io.ktor.http.HttpStatusCode
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.launch
import java.io.IOException

class AuthViewModel : ViewModel() {
    private val _user = MutableStateFlow<String?>(null)
    val user: StateFlow<String?> = _user.asStateFlow()

    private val _message = MutableStateFlow("")
    val message: StateFlow<String> = _message.asStateFlow()

    fun signIn(username: String, password: String) =
        attempt(username, password) { ServerApi.login(username, password) }

    fun signUp(username: String, password: String) =
        attempt(username, password) { ServerApi.register(username, password) }

    private fun attempt(username: String, password: String, call: suspend () -> Unit) {
        if (username.isBlank() || password.isBlank()) {
            _message.value = "Username and password required"
            return
        }
        viewModelScope.launch {
            try {
                call()
                _message.value = ""
                _user.value = username
            } catch (e: ApiException) {
                _message.value = when (e.status) {
                    HttpStatusCode.Unauthorized -> "Invalid username or password"
                    HttpStatusCode.Conflict -> "Username already taken"
                    else -> e.message ?: "Request failed (${e.status.value})"
                }
            } catch (e: IOException) {
                Log.e("AuthViewModel", "Network error", e)   // keep this: tells you timeout vs refused vs cleartext blocked
                _message.value = "Can't reach server"
            } catch (e: Exception) {
                Log.e("AuthViewModel", "Unexpected error", e)
                _message.value = "Something went wrong"
            }
        }
    }

    fun signOut() {
        viewModelScope.launch {
            try { ServerApi.logout() } catch (_: Exception) { }
            _user.value = null
        }
    }
}