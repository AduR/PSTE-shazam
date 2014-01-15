/*******************************************************************************
*
*  File Name : main.c
*
*  Purpose :
*
*  Creation Date : 23-11-13 15:55:04
*
*  Last Modified : 15-01-14 12:32:37
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
    t_wav *wav = NULL;
    t_fft *fft = NULL;
    t_max *ptr = NULL;

    /*=== chek param ===*/
    if (argc != 2)
    {
        printf("Need one (and only one) file as param to compute its hash.\n");
        return 0;
    }

    /*=== init ===*/
    wav = ft_init_wav(argv[1]);
    fft = ft_init_fft(wav->len);
    ft_perform_fft(fft, wav);

    /*=== get hash ===*/
    ptr = ft_get_hash_tab(fft);
    ft_print_t_max(ptr, fft->lenB);

    /*=== clean ===*/
    free(ptr);
    ft_free_wav(wav);
    ft_free_fft(fft);

    return 0;
}

