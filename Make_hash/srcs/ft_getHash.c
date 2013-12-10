/*******************************************************************************
*
*  File Name : ft_getHash.c
*
*  Purpose :
*
*  Creation Date : 09-12-13 10:55:04
*
*  Last Modified : 10-12-13 14:50:22
*
*  Created By : Nodraak
*
*******************************************************************************/

#include <SDL2/SDL.h>
#include "fftw3.h"

#include "constantes.h"
#include "ft_utils.h"

void ft_sortTab(t_max *tab)
{
    int i, done = 0;
    uint64_t tmpi;
    double tmpd;

    while (!done)
    {
        done = 1;

        for (i = 0; i < 4-1; i++)
        {
            if (tab[i].intensity < tab[i+1].intensity)
            {
                tmpi = tab[i].hash;
                tab[i].hash = tab[i+1].hash;
                tab[i+1].hash = tmpi;

                tmpd = tab[i].intensity;
                tab[i].intensity = tab[i+1].intensity;
                tab[i+1].intensity = tmpd;

                done = 0;
            }
        }
    }
}

t_max *ft_get_hash_tab(t_fft *fft)
{
    uint64_t times, i;
    t_max *ptr;
    t_max maxTab[4];

    ptr = my_malloc(sizeof(t_max) * fft->lenB, __FILE__, __LINE__);

    for (times = 0; times < fft->lenB; times++)
    {
        // init max tab
        for (i = 0; i < 4; i++)
        {
            maxTab[i].hash = 0;
            maxTab[i].intensity =  0;
        }

        // get the 4 max intensities
        // ===>>> may start at 5 and end before 4k
        for (i = 1; i < CHUNK_SIZE; i++)
        {
            double maxCurrent = fft->out[times][i][0] + fft->out[times][i][1];

            if (maxTab[3].intensity < maxCurrent)
            {
                maxTab[3].intensity = maxCurrent;
                maxTab[3].hash = i; // to do : set to real freq
                                    // edit 9 dec  : what ?
                ft_sortTab(maxTab);
            }
        }

        // copy founded max to final returned tab
        ptr[times].hash = 0;
        ptr[times].time = times * fft->lenT / fft->lenB;
        ptr[times].intensity = 0;

        for (i = 0; i < 4; i++)
        {
            ptr[times].hash += maxTab[i].hash/10*10 * ft_my_pow(ENCODE_NB, i);
            // hash/10*10 ===> arrondi ===> reduction du bruit
            // max(hash) ~ chunksize == 4k ===> false, saw 8k
            // !! 10 is to much, 5 a little too much ===> try 3 or maybe 2
            // !! ok for original file, but real listening may be != ===> 10 ?
            ptr[times].intensity += maxTab[i].intensity;
        }
    }

    return ptr;
}

