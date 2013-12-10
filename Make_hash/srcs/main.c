/*******************************************************************************
*
*  File Name : main.c
*
*  Purpose :
*
*  Creation Date : 23-11-13 15:55:04
*
*  Last Modified : 10-12-13 11:23:51
*
*  Created By : adur
*
*******************************************************************************/

#include <SDL2/SDL.h>
#include "fftw3.h"

#include "constantes.h"
#include "ft_init.h"
#include "ft_getHash.h"
#include "ft_utils.h"

int main(int argc, char *argv[])
{
    t_wav *wav;
    t_fft *fft;

    /*=== chek param ===*/
    if (argc != 2)
    {
        printf("Need a file as param to compute hash.\n");
        return 0;
    }

    /*=== init ===*/
    (void)argc, (void)argv; // disable warning
    wav = ft_init_wav(argv[1]);
    fft = ft_init_fft(wav->len);
    ft_perform_fft(fft, wav);

    /*=== get hash ===*/
    t_max *ptr = ft_get_hash_tab(fft);
    ft_print_t_max(ptr, fft->lenB);

    /*=== free ===*/
    free(ptr);
    ft_free_wav(wav);
    ft_free_fft(fft);

    return 0;
}

