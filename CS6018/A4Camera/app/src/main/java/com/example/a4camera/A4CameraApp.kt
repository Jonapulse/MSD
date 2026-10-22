package com.example.a4camera

import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.saveable.rememberSaveable
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel
import com.example.a4camera.auth.AuthViewModel
import com.example.a4camera.auth.LoginScreen
import com.example.a4camera.gallery.GalleryScreen

@Composable
fun A4CameraApp(authViewModel: AuthViewModel = viewModel()) {
    val user by authViewModel.user.collectAsStateWithLifecycle()
    val message by authViewModel.message.collectAsStateWithLifecycle()

    Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
        val currentUser = user
        if (currentUser == null) {
            LoginScreen(
                message = message,
                onSignIn = authViewModel::signIn,
                onSignUp = authViewModel::signUp,
                modifier = Modifier.padding(innerPadding)
            )
        } else {
            // Lives inside the logged-in branch, so it resets to the camera on each login
            var showGallery by rememberSaveable { mutableStateOf(false) }
            if (showGallery) {
                GalleryScreen(
                    username = currentUser,
                    onBack = { showGallery = false },
                    onSignOut = authViewModel::signOut,
                    modifier = Modifier.padding(innerPadding)
                )
            } else {
                CameraScreen(
                    modifier = Modifier.padding(innerPadding),
                    onOpenGallery = { showGallery = true }
                )
            }
        }
    }
}