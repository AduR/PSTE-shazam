/*******************************************************************************
*
*  File Name : ft_getHash.c
*
*  Purpose :
*
*  Creation Date : 09-12-13 10:55:04
*
*  Last Modified : 07-01-14 11:15:02
*
*  Created By : Nodraak
*
*******************************************************************************/

#include <SDL2/SDL.h>
#include "fftw3.h"

#include "constantes.h"
#include "ft_utils.h"

/* private functions prototypes , no need to be seeable from another file */
void ft_clean_tab(t_max maxTab[]);
void ft_get_max(fftw_complex *out, t_max maxTab[]);
void ft_save_max_intensities(t_max *ptr, t_max maxTab[]);

void ft_sortTab(t_max *tab)
{
    int i, done = 0;
    uint64_t i_tmp;
    double d_tmp;

    while (!done)
    {
        done = 1;

        for (i = 0; i < NB_MAX_INTENSITY-1; i++)
        {
            if (tab[i].intensity > tab[i+1].intensity)
            {
                i_tmp = tab[i].hash;
                tab[i].hash = tab[i+1].hash;
                tab[i+1].hash = i_tmp;

                d_tmp = tab[i].intensity;
                tab[i].intensity = tab[i+1].intensity;
                tab[i+1].intensity = d_tmp;

                done = 0;
            }
        }
    }
}

t_max *ft_get_hash_tab(t_fft *fft)
{
    uint64_t times;
    t_max maxTab[NB_MAX_INTENSITY]; /* tmp max intensities */
    t_max *ptr; /* save the NB_MAX_INT. intensities foreach times */

    ptr = my_malloc(sizeof(t_max) * fft->lenB, __FILE__, __LINE__);

    for (times = 0; times < fft->lenB; times++)
    {
        ft_clean_tab(maxTab);
        ft_get_max(fft->out[times], maxTab);
        ft_save_max_intensities(&ptr[times], maxTab);
        /* save time, would have need many parameters */
        ptr[times].time = times * fft->lenT / fft->lenB;
    }

    return ptr;
}

////////////////////////////////////////////////////////////////////////////////

void ft_clean_tab(t_max maxTab[])
{
    uint64_t i;

    for (i = 0; i < NB_MAX_INTENSITY; i++)
    {
        maxTab[i].hash = 0;
        maxTab[i].intensity = 0;
    }
}

void ft_get_max(fftw_complex *out, t_max maxTab[])
{
    uint64_t i;
    double currentMax;

    /* skip firsts freq, causing false true info TODO define */
    for (i = 50; i < CHUNK_SIZE/2+1; i++)
    {
        currentMax = out[i][0] + out[i][1];

        if (currentMax > maxTab[0].intensity)
        {
            maxTab[0].intensity = currentMax;
            maxTab[0].hash = i;
            // TODO : set to real hz freq, not arbitrairy unit - 7/01/14 osef
            ft_sortTab(maxTab);
        }
    }
}


void ft_save_max_intensities(t_max *ptr, t_max maxTab[])
{
    uint64_t i;

    /* init */
    ptr->hash = 0;
    ptr->intensity = 0;

    /* fill */
    for (i = 0; i < NB_MAX_INTENSITY; i++)
    {
       ptr->hash += (maxTab[i].hash/ROUND) * ft_my_pow(ENCODE_NB, i);
       ptr->intensity += maxTab[i].intensity;
    }
}

