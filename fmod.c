/*******************************************************************************
*
*  File Name : fmod.c
*
*  Purpose : fmod function
*
*  Creation Date : 23-10-13 10:32:29
*
*  Last Modified : 28-10-13 15:18:08
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


#if 0
    /*result = channel->setVolume(volume);*/
    FMOD_DSP *dsp;
    FMOD_DSP_DESCRIPTION dspdes = {
    "fuck it fmod dsp",
    0,
    0,
    0, 0, 0, 0,
    0,
    0, 0,
    /*DSP::getNumParame, FMOD_DSP_PARAMETERDESC *  paramdesc;*/
    0, 0,
    0, 0, 0,
    0};

    result = FMOD_System_CreateDSPByType(sound->system, FMOD_DSP_TYPE_UNKNOWN, &dsp);
    ft_fmod_check_error(result, "sys create dsp", __FILE__, __LINE__);
    result = FMOD_System_AddDSP(sound->system, dsp, 0);
    ft_fmod_check_error(result, "sys add dsp", __FILE__, __LINE__);
#endif
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
        /*result = FMOD_Channel_SetPosition(sound->channel, pos, FMOD_TIMEUNIT_MS);
        ft_fmod_check_error(result, "set pos", __FILE__, __LINE__);

        result = FMOD_System_Update(sound->system);
        ft_fmod_check_error(result, "system update", __FILE__, __LINE__);*/

        result = FMOD_Channel_GetSpectrum(sound->channel, spect->tab[pos/FPS], NB_FREQ, 0,
                                            //FMOD_DSP_FFT_WINDOW_BLACKMANHARRIS);
                                            //FMOD_DSP_FFT_WINDOW_HAMMING);
                                            //FMOD_DSP_FFT_WINDOW_TRIANGLE);
                                            FMOD_DSP_FFT_WINDOW_RECT);
        ft_fmod_check_error(result, "get spectrum", __FILE__, __LINE__);

        SDL_Delay(FPS_DELAY);
    }
}

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




#if 0

/* hash */
//For every line of data:
for (int freq = LOWER_LIMIT; freq < UPPER_LIMIT-1; freq++)
{
    //Get the magnitude:
    double mag = Math.log(results[freq].abs() + 1);
    //Find out which range we are in:
    int index = getIndex(freq);
    //Save the highest magnitude and corresponding frequency:
    if (mag > highscores[index])
    {
        highscores[index] = mag;
        recordPoints[index] = freq;
    }
}

//Write the points to a file:
for (int i = 0; i < AMOUNT_OF_POINTS; i++)
{
    fw.append(recordPoints[i] + "\t");
}
fw.append("\n");
// ... snip ...
int[] RANGE = new int[] {40,80,120,180, UPPER_LIMIT+1};
//Find out in which range
int getIndex(int freq)
{
    int i = 0;
    while(RANGE[i] < freq)
        i++;
    return i;
}


/* search match */
//Using a little bit of error-correction, damping
int FUZ_FACTOR = 2;

long hash(String line)
{
    String[] p = line.split("\t");
    long p1 = Long.parseLong(p[0]);
    long p2 = Long.parseLong(p[1]);
    long p3 = Long.parseLong(p[2]);
    long p4 = Long.parseLong(p[3]);
    return (p4-(p4%FUZ_FACTOR)) * 100000000 + (p3-(p3%FUZ_FACTOR)) * 100000
            + (p2-(p2%FUZ_FACTOR)) * 100 + (p1-(p1%FUZ_FACTOR));
}

/* nb : *.h */
private class DataPoint
{
    private int time;
    private int songId;
    public DataPoint(int songId, int time)
    {
        this.songId = songId;
        this.time = time;
    }
    public int getTime()
    {
        return time;
    }
    public int getSongId()
    {
        return songId;
    }
}
#endif

