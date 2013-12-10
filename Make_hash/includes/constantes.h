#ifndef CONSTANTES_H
#define CONSTANTES_H

//=== INCLUDE ===

#include <stdio.h>
#include <stdio.h>
#include <stdint.h> // for uint64_t

#include <SDL2/SDL.h>
#include "fftw3.h"

//=== DEFINE ===

#define CHUNK_SIZE      (4*1024)
#define ECHANT          44100           // frequence echantillonage en Hz
#define TIME_DIV        (1.0/100000)    // force double type
#define ENCODE_NB       10000           // should be > chunk_size

//=== STRUCT ===

typedef struct      s_wav
{
    SDL_AudioSpec   spec;
    uint32_t        len;
    uint8_t         *buf;
}                   t_wav;

typedef struct      s_fft
{
    fftw_complex    **out;
    uint32_t        lenB;
    double          lenT;
    fftw_plan       plan;
}                   t_fft;

typedef struct      s_max
{
    uint64_t        hash;
    double          time;
    double          intensity;
}                   t_max;

#endif /* CONSTANTES_H */
