#include "mps-helper/mps.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    struct mpa_Format *format = malloc(sizeof(struct mpa_Format));
    if (format == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    // Initialize default values
    format->name = "My MP3 Song";
    format->sample_rate = 44100;  // Default, will be set later
    format->num_channels = 2;     // Default, will be set later
    format->bit_depth = 16;       // Default, typically 16-bit for PCM
    format->audio_data = NULL;    // Will hold decoded PCM data
    format->length = 44100 * 5;
    printf("creating song with name %s\n", format->name);
    for (int i = 0; i < 6; i++) {
        printf("creating sine %d\n", i);
        generate_sine_wave(format, i * 10, 1.0);
    }
    play_audio(format);
    printf("done\n");
    write_pcm_to_file(format);
    return 0;
}