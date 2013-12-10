/*******************************************************************************
*
*  File Name : ft_init.c
*
*  Purpose :
*
*  Creation Date : 9-12-13 10:50:04
*
*  Last Modified : 09-12-13 15:38:09
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

    wav->spec.freq = 44100;
    wav->spec.format = AUDIO_U8;
    wav->spec.channels = 1;
    wav->spec.samples = 4096;

    if (SDL_LoadWAV(path, &wav->spec, &wav->buf, &wav->len) == NULL)
    {
        fprintf(stderr, "Error SDL_LoadWAV() for file %s : %s\n",
                path, SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return wav;
}

t_fft *ft_init_fft(Uint32 wav_len)
{
    t_fft *fft;
    uint64_t times;

    fft = my_malloc(sizeof(t_fft), __FILE__, __LINE__);

    // init fft.len*
    fft->lenB = wav_len / CHUNK_SIZE;
    fft->lenT = (double)wav_len / ECHANT;

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
    uint64_t times, i;

    in = my_malloc(CHUNK_SIZE * sizeof(fftw_complex), __FILE__, __LINE__);

    for (times = 0; times < fft->lenB; times++)
    {
        // load chunk
        for (i = 0; i < CHUNK_SIZE; i++)
        {
            in[i][0] = wav->buf[times*CHUNK_SIZE+i];
            in[i][1] = 0;
        }

        // perform FFT analysis on the chunk
        fft->plan = fftw_plan_dft_1d(CHUNK_SIZE, in, fft->out[times],
                                        FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_execute(fft->plan);
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

    fftw_destroy_plan(fft->plan);
    for (i = 0; i < fft->lenB; i++)
        free(fft->out[i]);
    free(fft->out);
}


