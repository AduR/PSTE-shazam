/*******************************************************************************
*
*  File Name : ft_result.c
*
*  Purpose :
*
*  Creation Date : 07-01-14 17:02:44
*
*  Last Modified : 07-01-14 18:41:46
*
*  Created By : Nodraak
*
*******************************************************************************/

#include "constantes.h"
#include "ft_result.h"

void ft_print_result(uint64_t *tab, t_data *head)
{
    uint64_t i, j, max_id, max_value;

    printf("\n");
    for (j = 0; j < NB_HASH; ++j)
    {
        // get max
        max_value = tab[0];
        max_id = 0;
        for (i = 0; i < NB_HASH; ++i)
        {
            if (tab[i] > max_value)
            {
                max_value = tab[i];
                max_id = i;
            }
        }
        if (max_value == 0) // no max found
            break;

        // printf
        printf("%llu match for %s\n", tab[max_id],
                ft_get_name_from_id(head->music, max_id));
        tab[max_id] = 0;
    }
}

char *ft_get_name_from_id(t_music *ptr, uint64_t max_id)
{
    while (ptr != NULL && ptr->id_music != max_id)
        ptr = ptr->next;

    if (ptr == NULL)
        return NULL;
    else
        return ptr->name;
}



