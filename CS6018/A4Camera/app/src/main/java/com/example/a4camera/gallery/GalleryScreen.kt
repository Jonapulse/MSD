package com.example.a4camera.gallery

import androidx.activity.compose.BackHandler
import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.aspectRatio
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.grid.GridCells
import androidx.compose.foundation.lazy.grid.LazyVerticalGrid
import androidx.compose.foundation.lazy.grid.items
import androidx.compose.material3.Button
import androidx.compose.material3.ButtonDefaults
import androidx.compose.material3.CircularProgressIndicator
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.unit.dp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel

@Composable
fun GalleryScreen(
    username: String,
    onBack: () -> Unit,
    onSignOut: () -> Unit,
    modifier: Modifier = Modifier,
    viewModel: GalleryViewModel = viewModel(key = "gallery-$username")
) {
    val photos by viewModel.photos.collectAsStateWithLifecycle()
    val thumbnails by viewModel.thumbnails.collectAsStateWithLifecycle()
    val selected by viewModel.selected.collectAsStateWithLifecycle()
    val status by viewModel.status.collectAsStateWithLifecycle()

    LaunchedEffect(Unit) { viewModel.refresh() }

    // System back: close the full view first, then return to the camera
    BackHandler {
        if (selected != null) viewModel.closePhoto() else onBack()
    }

    selected?.let { photo ->
        FullPhotoView(
            photo = photo,
            onClose = viewModel::closePhoto,
            onDelete = { viewModel.delete(photo.id) },
            modifier = modifier
        )
        return
    }

    Column(modifier.fillMaxSize()) {
        Row(
            modifier = Modifier.fillMaxWidth().padding(8.dp),
            verticalAlignment = Alignment.CenterVertically,
            horizontalArrangement = Arrangement.spacedBy(8.dp)
        ) {
            Button(onClick = onBack) { Text("Camera") }
            Text(
                text = "$username's photos",
                style = MaterialTheme.typography.titleMedium,
                modifier = Modifier.weight(1f)
            )
            Button(onClick = onSignOut) { Text("Sign Out") }
        }

        status?.let { Text(it, modifier = Modifier.padding(16.dp)) }

        LazyVerticalGrid(
            columns = GridCells.Adaptive(110.dp),
            contentPadding = PaddingValues(4.dp),
            modifier = Modifier.fillMaxSize()
        ) {
            // Lazy keys must be Bundle-saveable, and UInt isn't, so use Long
            items(photos, key = { it.id.toLong() }) { photo ->
                LaunchedEffect(photo.id) { viewModel.loadThumbnail(photo.id) }
                Box(
                    modifier = Modifier
                        .padding(4.dp)
                        .aspectRatio(1f)
                        .background(Color.LightGray)
                        .clickable { viewModel.openPhoto(photo.id) }
                ) {
                    thumbnails[photo.id]?.let { thumb ->
                        Image(
                            bitmap = thumb,
                            contentDescription = "Photo ${photo.id}",
                            contentScale = ContentScale.Crop,
                            modifier = Modifier.fillMaxSize()
                        )
                    }
                }
            }
        }
    }
}

@Composable
private fun FullPhotoView(
    photo: FullPhoto,
    onClose: () -> Unit,
    onDelete: () -> Unit,
    modifier: Modifier = Modifier
) {
    Column(modifier.fillMaxSize()) {
        Row(
            modifier = Modifier.fillMaxWidth().padding(8.dp),
            verticalAlignment = Alignment.CenterVertically
        ) {
            Button(onClick = onClose) { Text("Back") }
            Spacer(Modifier.weight(1f))
            Button(
                onClick = onDelete,
                colors = ButtonDefaults.buttonColors(containerColor = MaterialTheme.colorScheme.error)
            ) { Text("Delete") }
        }
        Box(Modifier.fillMaxSize(), contentAlignment = Alignment.Center) {
            val bitmap = photo.bitmap
            if (bitmap == null) {
                CircularProgressIndicator()
            } else {
                Image(
                    bitmap = bitmap,
                    contentDescription = "Photo ${photo.id}",
                    contentScale = ContentScale.Fit,
                    modifier = Modifier.fillMaxSize()
                )
            }
        }
    }
}