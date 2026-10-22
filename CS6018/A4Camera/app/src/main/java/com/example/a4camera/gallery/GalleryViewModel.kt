package com.example.a4camera.gallery

import android.graphics.ImageDecoder
import android.util.Log
import androidx.compose.ui.graphics.ImageBitmap
import androidx.compose.ui.graphics.asImageBitmap
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.example.a4camera.network.PhotoInfo
import com.example.a4camera.network.ServerApi
import kotlinx.coroutines.CancellationException
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.asStateFlow
import kotlinx.coroutines.flow.update
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.nio.ByteBuffer

data class FullPhoto(val id: UInt, val bitmap: ImageBitmap?)

class GalleryViewModel : ViewModel() {
    private val _photos = MutableStateFlow<List<PhotoInfo>>(emptyList())
    val photos: StateFlow<List<PhotoInfo>> = _photos.asStateFlow()

    private val _thumbnails = MutableStateFlow<Map<UInt, ImageBitmap>>(emptyMap())
    val thumbnails: StateFlow<Map<UInt, ImageBitmap>> = _thumbnails.asStateFlow()

    private val _selected = MutableStateFlow<FullPhoto?>(null)
    val selected: StateFlow<FullPhoto?> = _selected.asStateFlow()

    private val _status = MutableStateFlow<String?>(null)
    val status: StateFlow<String?> = _status.asStateFlow()

    // Touched only from the main thread (viewModelScope), so no locking needed
    private val inFlight = mutableSetOf<UInt>()

    fun refresh() {
        viewModelScope.launch {
            try {
                val list = ServerApi.listPhotos()
                _photos.value = list
                _status.value = if (list.isEmpty()) "No photos yet" else null
            } catch (e: CancellationException) {
                throw e
            } catch (e: Exception) {
                Log.e("GalleryViewModel", "List failed", e)
                _status.value = "Couldn't load photos"
            }
        }
    }

    fun loadThumbnail(id: UInt) {
        if (id in _thumbnails.value || !inFlight.add(id)) return
        viewModelScope.launch {
            try {
                val bytes = ServerApi.downloadPhoto(id)
                val bitmap = withContext(Dispatchers.Default) { decode(bytes, maxSide = 300) }
                _thumbnails.update { it + (id to bitmap) }
            } catch (e: CancellationException) {
                throw e
            } catch (e: Exception) {
                Log.e("GalleryViewModel", "Thumbnail $id failed", e)
            } finally {
                inFlight.remove(id)
            }
        }
    }

    fun openPhoto(id: UInt) {
        _selected.value = FullPhoto(id, null)
        viewModelScope.launch {
            try {
                val bytes = ServerApi.downloadPhoto(id)
                val bitmap = withContext(Dispatchers.Default) { decode(bytes, maxSide = 2048) }
                // Ignore the result if the user already closed or switched photos
                if (_selected.value?.id == id) _selected.value = FullPhoto(id, bitmap)
            } catch (e: CancellationException) {
                throw e
            } catch (e: Exception) {
                Log.e("GalleryViewModel", "Open $id failed", e)
                _status.value = "Couldn't open photo"
                _selected.value = null
            }
        }
    }

    fun closePhoto() {
        _selected.value = null
    }

    fun delete(id: UInt) {
        viewModelScope.launch {
            try {
                ServerApi.deletePhoto(id)
                _photos.update { list -> list.filterNot { it.id == id } }
                _thumbnails.update { it - id }
                _selected.value = null
                if (_photos.value.isEmpty()) _status.value = "No photos yet"
            } catch (e: CancellationException) {
                throw e
            } catch (e: Exception) {
                Log.e("GalleryViewModel", "Delete $id failed", e)
                _status.value = "Delete failed"
            }
        }
    }

    private fun decode(bytes: ByteArray, maxSide: Int): ImageBitmap {
        val source = ImageDecoder.createSource(ByteBuffer.wrap(bytes))
        return ImageDecoder.decodeBitmap(source) { decoder, info, _ ->
            val longest = maxOf(info.size.width, info.size.height)
            decoder.setTargetSampleSize(maxOf(1, longest / maxSide))
        }.asImageBitmap()
    }
}