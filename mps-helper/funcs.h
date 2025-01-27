#ifndef STRUCTS_FUNCS
#include "structs.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

void generate_sine_wave(struct mpa_Format *format, double frequency, double duration);
void write_pcm_to_file(struct mpa_Format *format);

void play_audio(struct mpa_Format *format);

#endif // STRUCTS_FUNCS