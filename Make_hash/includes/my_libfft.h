#ifndef MY_LIB_FFT_H
#define MY_LIB_FFT_H

//=== INCLUDE ===

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL.h>
#include "fftw3.h"

//=== DEFINE ===

#define CHUNK_SIZE      (4*1024)
#define INTENSITY_DIV   10              // for clarify printf debuging
#define ECHANT          44100           // frequence echantillonage en Hz
#define TIME_DIV        (1.0/100000)    // force double type
#define ENCODE_NB       10000           // should be > chunk_size

#define SCREEN_W        (4000)
#define SCREEN_H        (1000)

//=== STRUCT ===

typedef struct      s_wave
{
    SDL_AudioSpec   spec;
    Uint32          len;
    Uint8           *buf;
}                   t_wave;

typedef struct      s_fft
{
    fftw_complex    *in;
    fftw_complex    **out;
    Uint32          lenB;
    double          lenT;
    fftw_plan       plan;
}                   t_fft;

typedef struct      s_max
{
    Uint64          hash;
    double          time;
    double          intensity;
}                   t_max;

//=== PROTOTYPE ===

void ft_init(t_wave *wave, t_fft *fft, char *path);
void ft_free(t_wave *wave, t_fft *fft);
void ft_print_spect(t_fft *fft, char *path);

t_max *ft_getTab(t_fft *fft);

#endif /* MY_LIB_FFT_H */
