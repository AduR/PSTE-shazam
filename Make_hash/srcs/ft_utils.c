/*******************************************************************************
*
*  File Name : ft_utils.c
*
*  Purpose :
*
*  Creation Date : 09-12-13 11:21:32
*
*  Last Modified : 10-12-13 11:24:12
*
*  Created By : Nodraak
*
*******************************************************************************/

#include "constantes.h"
#include "ft_utils.h"

void *my_malloc(uint64_t size, char *file, int line)
{
    void *ptr;

    ptr = malloc(size);

    if (ptr == NULL)
    {
        printf("Erreur malloc in %s l.%d\n", file, line);
        exit(EXIT_FAILURE);
    }

    return ptr;
}

uint64_t ft_my_pow(uint64_t nb, uint64_t pow)
{
    uint64_t ret = 1, i;

    for (i = 1; i < pow; i++)
        ret *= nb;

    return ret;
}

void ft_print_t_max(t_max *ptr, uint32_t len)
{
    uint32_t i;

    for (i = 0; i < len; i++)
        printf("%"PRIu64"\t%.3f\n", ptr[i].hash, ptr[i].time);

        // freq time, intensity
        //printf("%d %.3f %d\n", ptr[i].freq, ptr[i].time,
        //        (int)ptr[i].intensity);
}

