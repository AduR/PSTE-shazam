/*******************************************************************************
*
*  File Name : fmod.c
*
*  Purpose : fmod functions - loading and creating the tab time / freq (spectrogramme)
*
*  Creation Date : 23-10-13 10:32:29
*
*  Last Modified : 13-11-13 15:18:08
*
*  Created By : achardon
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <fmod/fmod.h>
#include <fmod/fmod_errors.h>

#include "constantes.h"
#include "fmod.h"

t_soundSpect *ft_get_spect(void)
{
    t_fmodSound sound;
    t_soundSpect *spect;

    ft_init_system(&sound);
    ft_init_sound(&sound, MUSIC_PATH);
    ft_init_sound_spect(&sound, &spect);
    ft_fill_spect(&sound, spect);

    ft_free_sound(&sound);

    return spect;
}

void ft_fmod_check_error(FMOD_RESULT result, char *s, char *file, int line)
{
    if (result != FMOD_OK)
    {
        while (*file != '\0')
            file++;
        while (*file != '\\')
            file--;
        file++;

        printf("erreur %s in %s:%d : %s\n", s, file, line, FMOD_ErrorString(result));

        printf("pause ...");
        getchar();

        exit(EXIT_FAILURE);
    }
}

void ft_init_system(t_fmodSound *sound)
{
    FMOD_RESULT result;

    result = FMOD_System_Create(&sound->system);
    ft_fmod_check_error(result, "create system", __FILE__, __LINE__);
    result = FMOD_System_Init(sound->system, 2, FMOD_INIT_NORMAL, NULL);
    ft_fmod_check_error(result, "init system", __FILE__, __LINE__);
}

void ft_init_sound(t_fmodSound *sound, char *path)
{
    FMOD_RESULT result;

    result = FMOD_System_CreateSound(sound->system, path, FMOD_SOFTWARE  | FMOD_CREATESAMPLE
                                        /*| FMOD_INIT_STREAM_FROM_UPDATE*/ | FMOD_ACCURATETIME, 0, &sound->sound);
    ft_fmod_check_error(result, "create sound", __FILE__, __LINE__);
    result = FMOD_System_PlaySound(sound->system, FMOD_CHANNEL_FREE, sound->sound, 0, &sound->channel);
    ft_fmod_check_error(result, "play sound", __FILE__, __LINE__);
}

void ft_free_sound(t_fmodSound *sound)
{
    FMOD_Sound_Release(sound->sound);

    FMOD_System_Close(sound->system);
    FMOD_System_Release(sound->system);
}

unsigned int ft_get_sound_length(t_fmodSound *sound)
{
    unsigned int len;
    FMOD_RESULT result;

    result = FMOD_Sound_GetLength(sound->sound, &len, FMOD_TIMEUNIT_MS);
    ft_fmod_check_error(result, "get length", __FILE__, __LINE__);

    return len;
}

void ft_init_tab(t_soundSpect *spect)
{
    unsigned int y;

    spect->tab = malloc(sizeof(float*)*spect->tab_len);
    for (y = 0; y < spect->tab_len; y++)
        spect->tab[y] = malloc(sizeof(float)*spect->nb_freq);
}

void ft_free_tab(t_soundSpect *spect)
{
    unsigned int y;

    for (y = 0; y < spect->tab_len; y++)
        free(spect->tab[y]);
    free(spect->tab);
}


void ft_init_sound_spect(t_fmodSound *sound, t_soundSpect **spect)
{
    *spect = malloc(sizeof(t_soundSpect));

    (*spect)->music_len = ft_get_sound_length(sound);
    (*spect)->tab_len = (*spect)->music_len / FPS;
    (*spect)->nb_freq = NB_FREQ;
    ft_init_tab(*spect);
}

void ft_fill_spect(t_fmodSound *sound, t_soundSpect *spect)
{
    unsigned int pos;
    FMOD_RESULT result;

    for (pos = 0; pos < spect->music_len - 1000; pos += FPS)
    {
        /* if we set the position and not let fmod plays it, it bugs (dont remember how but it does) */
        /*result = FMOD_Channel_SetPosition(sound->channel, pos, FMOD_TIMEUNIT_MS);
        ft_fmod_check_error(result, "set pos", __FILE__, __LINE__);

        result = FMOD_System_Update(sound->system);
        ft_fmod_check_error(result, "system update", __FILE__, __LINE__);*/

        /*
          fft options : FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS
                        FMOD_DSP_FFT_WINDOW_HAMMING
                        FMOD_DSP_FFT_WINDOW_TRIANGLE);
                        FMOD_DSP_FFT_WINDOW_RECT
        */
        result = FMOD_Channel_GetSpectrum(sound->channel, spect->tab[pos/FPS], NB_FREQ, 0,
                                            FMOD_DSP_FFT_WINDOW_RECT);
        ft_fmod_check_error(result, "get spectrum", __FILE__, __LINE__);

        SDL_Delay(FPS_DELAY);
    }
}

