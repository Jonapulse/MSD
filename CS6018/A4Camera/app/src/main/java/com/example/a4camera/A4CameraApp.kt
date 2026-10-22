package com.example.a4camera

import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.ui.Modifier
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.a4camera.auth.AuthViewModel
import com.example.a4camera.auth.LoginScreen

@Composable
fun A4CameraApp(authViewModel: AuthViewModel = viewModel()){
    val user by authViewModel.user.collectAsStateWithLifecycle()
    val message by authViewModel.message.collectAsStateWithLifecycle()

    Scaffold(modifier = Modifier.fillMaxSize()){ innerPadding ->
        if(user == null){
            LoginScreen(
                message = message,
                onSignIn = authViewModel::signIn,
                onSignUp = authViewModel::signUp,
                modifier = Modifier.padding(innerPadding)
            )
        } else {
            CameraScreen(
                modifier = Modifier.padding(innerPadding),
                onSignOut = authViewModel::signOut
            )
        }

    }
}