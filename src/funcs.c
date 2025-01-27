#include "mps-helper/funcs.h"

void generate_sine_wave(struct mpa_Format *format, double frequency, double duration) {
    uint32_t sample_count = (uint32_t)(format->sample_rate * duration);
    format->audio_data = malloc(sample_count * sizeof(int16_t));

    for (uint32_t i = 0; i < sample_count; i++) {
        // Generate sine wave (PCM data)
        int16_t sample = (int16_t)(32767 * sin(2 * M_PI * frequency * i / format->sample_rate));
        format->audio_data[i] = sample;
    }

    format->length = sample_count;
}

void write_pcm_to_file(struct mpa_Format *format) {
    FILE *file = fopen(format->name, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }
    size_t nameLength = strlen(format->name) + 1; // +1 for the null terminator
    fwrite(format->name, sizeof(char), nameLength, file);
    // Write the audio data to the file
    fwrite(format->audio_data, sizeof(int16_t), format->length, file);
    fclose(file);
}

#ifdef _WIN32
void play_audio(struct mpa_Format *format) {
    HWAVEOUT hWaveOut;
    WAVEFORMATEX waveFormat;
    WAVEHDR waveHeader;

    // Set up the WAVEFORMATEX structure for 16-bit, stereo audio
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nChannels = format->num_channels;
    waveFormat.nSamplesPerSec = format->sample_rate;
    waveFormat.nAvgBytesPerSec = format->sample_rate * format->num_channels * sizeof(int16_t); // 16-bit samples
    waveFormat.nBlockAlign = format->num_channels * sizeof(int16_t);
    waveFormat.wBitsPerSample = 16; // 16-bit depth
    waveFormat.cbSize = 0;

    // Open the audio output device
    if (waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, CALLBACK_NULL) != MMSYSERR_NOERROR) {
        printf("Failed to open audio device.\n");
        return;
    }

    // Set up the WAVEHDR structure to describe the audio data
    waveHeader.lpData = (LPSTR)format->audio_data;
    waveHeader.dwBufferLength = (DWORD)(format->length * sizeof(int16_t));
    waveHeader.dwBytesRecorded = 0;
    waveHeader.dwUser = 0;
    waveHeader.dwFlags = 0;
    waveHeader.dwLoops = 0;

    // Prepare the audio data for playback
    if (waveOutPrepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
        printf("Failed to prepare header.\n");
        return;
    }

    // Start playing the audio
    if (waveOutWrite(hWaveOut, &waveHeader, sizeof(WAVEHDR)) != MMSYSERR_NOERROR) {
        printf("Failed to play audio.\n");
        return;
    }

    // Wait for the audio to finish playing
    while (!(waveHeader.dwFlags & WHDR_DONE)) {
        Sleep(100);
    }

    // Clean up
    waveOutUnprepareHeader(hWaveOut, &waveHeader, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
#else
void play_audio(struct mpa_Format *format);
#endif