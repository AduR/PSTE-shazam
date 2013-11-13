#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

/* include */
#include <fmod/fmod.h>
#include <SDL2/SDL.h>

 /* define */
#define SCREEN_WIDTH        1000
#define SCREEN_HEIGHT       600

#define FPS                 40 /* 40 ideally == fmod refresh delay */
#define FPS_DELAY           (1000/FPS)
#define NB_FREQ             128

/* for the spectrogramme with sdl */
#define SPECTRUM_COR        500 /* should be 255 - fmod return between 0 and 1 and sdl expect 0-255 for colors */
#define MUL_Y               5
#define MUL_X               4

#define MY_PI               3.1415926539
#define MUSIC_PATH          "son15k.mp3"

 /* struct */
typedef struct      s_fmodSound
{
    FMOD_SYSTEM     *system;
    FMOD_SOUND      *sound;
    FMOD_CHANNEL    *channel;
}                   t_fmodSound;

typedef struct      s_soundSpect
{
    unsigned int    music_len; /* in ms */
    unsigned int    tab_len; /* 1 for each spectrum from fmod */
    unsigned int    nb_freq;
    float           **tab;
}                   t_soundSpect;

#endif /* CONSTANTES_H_INCLUDED */
