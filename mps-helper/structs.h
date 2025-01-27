#ifndef STRUCTS_MPS
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

struct mpa_Format {
    char *name;        // Name of the file format, e.g., "Custom MP3"
    int64_t length;    // Length of the audio data in samples or time (milliseconds/seconds)
    uint32_t sample_rate; // Sampling rate (e.g., 44100 Hz)
    uint16_t bit_depth;  // Bit depth (e.g., 16 bits per sample)
    uint16_t num_channels; // Number of audio channels (1 for mono, 2 for stereo)
    uint8_t *audio_data; // Pointer to the actual audio data (PCM or compressed)
};
#endif // STRUCTS_MPS