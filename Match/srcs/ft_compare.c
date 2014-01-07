/*******************************************************************************
*
*  File Name : ft_compare.c
*
*  Purpose :
*
*  Creation Date : 07-01-14 10:57:08
*
*  Last Modified : 07-01-14 15:27:52
*
*  Created By : Nodraak
*
*******************************************************************************/

#include <string.h>

#include "constantes.h"
#include "ft_loadHash.h"
#include "ft_compare.h"

uint64_t *ft_compare(t_data *head, char *s)
{
    uint64_t *tab = NULL;
    FILE *file = NULL;
    int i;
    char buf[BUF_SIZE];
    uint64_t hash;

    tab = ft_malloc(sizeof(uint64_t)*NB_HASH, __FILE__, __LINE__);
    for (i = 0; i < NB_HASH; ++i)
        tab[i] = 0;
    file = ft_fopen(s);

    while (!feof(file))
    {
        fgets(buf, BUF_SIZE-1, file);
        sscanf(buf, "%"SCNu64, &hash);

        t_hash *ptr = head->hash;
        while (ptr != NULL)
        {
            if (ptr->hash == hash)
            {
                printf("got matching hash=%llu id=%llu\n", ptr->hash,
                                                ptr->id_music);
                tab[ptr->id_music]++;
            }
            ptr = ptr->next;
        }
    }

    fclose(file);
    return tab;
}


