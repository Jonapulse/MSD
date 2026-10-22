package com.example.a4camera.auth

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import androidx.lifecycle.viewmodel.compose.viewModel
import com.google.firebase.Firebase
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.auth.FirebaseUser
import com.google.firebase.auth.auth
import kotlinx.coroutines.channels.awaitClose
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.callbackFlow
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.launch
import kotlinx.coroutines.tasks.await

class AuthViewModel : ViewModel() {
    private val auth = Firebase.auth

    val user: StateFlow<FirebaseUser?> = callbackFlow{
        val listener = FirebaseAuth.AuthStateListener {trySend(it.currentUser)}
        auth.addAuthStateListener(listener)
        awaitClose{ auth.removeAuthStateListener(listener)}
    }.stateIn(viewModelScope, SharingStarted.Eagerly, auth.currentUser)

    private val _message = MutableStateFlow("")
    val message: StateFlow<String> = _message.asStateFlow()

    fun signIn(email: String, password: String) {
        viewModelScope.launch {
            try{
                auth.signInWithEmailAndPassword(email, password).await()
                _message.value = ""
            } catch (e: Exception){
                _message.value = "Login failed: ${e.localizedMessage}"
            }
        }
    }

    fun signUp(email: String, password: String){
        viewModelScope.launch {
            try{
                auth.createUserWithEmailAndPassword(email, password).await()
                _message.value = ""
            } catch (e: Exception){
                _message.value = "Sign-up failed: ${e.localizedMessage}"
            }
        }
    }

    fun signOut() = auth.signOut()
}