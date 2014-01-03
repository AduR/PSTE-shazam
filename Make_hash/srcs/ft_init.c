/*******************************************************************************
*
*  File Name : ft_init.c
*
*  Purpose :
*
*  Creation Date : 9-12-13 10:50:04
*
*  Last Modified : 03-01-14 21:22:15
*
*  Created By : Nodraak
*
*******************************************************************************/

#include <string.h>

#include <SDL2/SDL.h> // for SDL_loadWAV()
#include "fftw3.h"

#include "constantes.h"
#include "ft_init.h"
#include "ft_utils.h"

t_wav *ft_init_wav(char *path)
{
    t_wav *wav;

    SDL_Init(SDL_INIT_AUDIO);
    wav = my_malloc(sizeof(t_wav), __FILE__, __LINE__);

    /* desired format */
    wav->spec.freq = SAMPLING_FREQ;
    wav->spec.format = AUDIO_U8;
    wav->spec.channels = 1;
    wav->spec.samples = 4096; /* 3/01/14 chunk size ? */

    /* load music */
    SDL_AudioSpec *have = SDL_LoadWAV(path, &wav->spec, &wav->buf, &wav->len);
    if (have == NULL)
    {
        fprintf(stderr, "Error SDL_LoadWAV() for file %s : %s\n",
                path, SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* check real format */
    if (have->freq != wav->spec.freq)
        fprintf(stderr, "Error, dont have wanted freq\n");
    if (have->format != wav->spec.format)
        fprintf(stderr, "Error, dont have wanted format\n");
    if (have->channels != wav->spec.channels)
        fprintf(stderr, "Error, dont have wanted channels\n");
    if (have->samples != wav->spec.samples)
        fprintf(stderr, "Error, dont have wanted samples\n");

    return wav;
}

t_fft *ft_init_fft(Uint32 wav_len)
{
    t_fft *fft;
    uint64_t times;

    fft = my_malloc(sizeof(t_fft), __FILE__, __LINE__);

    // init fft.len*
    fft->lenT = (double)wav_len / SAMPLING_FREQ;
    fft->lenB = fft->lenT / STEP;

    // malloc fft.out
    fft->out = my_malloc(fft->lenB * sizeof(fftw_complex*), __FILE__, __LINE__);
    for (times = 0; times < fft->lenB; times++)
    {
        fft->out[times] = my_malloc(CHUNK_SIZE * sizeof(fftw_complex),
                                    __FILE__, __LINE__);
    }

    return fft;
}

void ft_perform_fft(t_fft *fft, t_wav *wav)
{
    fftw_complex *in;
    fftw_plan plan;
    uint64_t times, freq;

    in = my_malloc(CHUNK_SIZE * sizeof(fftw_complex), __FILE__, __LINE__);

    for (times = 0; times < fft->lenB; times++)
    {
        // load chunk
        for (freq = 0; freq < CHUNK_SIZE; freq++)
        {
            in[freq][0] = wav->buf[(int)(OFFSET_SIZE) * times + freq];
            in[freq][1] = 0;
        }

        // perform FFT analysis on the chunk
        plan = fftw_plan_dft_1d(CHUNK_SIZE, in, fft->out[times],
                                        FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_execute(plan);
        fftw_destroy_plan(plan);
    }

    free(in);
}

//////////////////////////////////////////////////////////////////

void ft_free_wav(t_wav *wav)
{
    SDL_FreeWAV(wav->buf);
    SDL_Quit();
}

void ft_free_fft(t_fft *fft)
{
    uint64_t i;

    for (i = 0; i < fft->lenB; i++)
        free(fft->out[i]);
    free(fft->out);
}


