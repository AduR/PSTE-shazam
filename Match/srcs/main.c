/*******************************************************************************
*
*  File Name : main.c
*
*  Purpose :
*
*  Creation Date : 03-12-13 18:57:08
*
*  Last Modified : 07-01-14 15:07:56
*
*  Created By : Nodraak
*
*******************************************************************************/

#include <time.h>

#include "constantes.h"
#include "ft_loadHash.h"
#include "ft_compare.h"

void ft_free(t_data *ptr);

int main(int argc, char *argv[])
{
    t_data *head;
    uint64_t *tab;

    if (argc != 2)
    {
        printf("Error, need hash file as param to compare.\n");
        return 0;
    }

    head = ft_load_data();
    tab = ft_compare(head, argv[1]);
    //ft_print_result(tab, head);

    ft_free(head);
    free(tab);
    return 0;
}

void ft_free(t_data *ptr)
{
    t_music *ptrMusic = NULL, *ptrMusicTmp;
    t_hash *ptrHash = NULL, *ptrHashTmp;

    ptrMusic = ptr->music;
    while (ptrMusic->next != NULL)
    {
        ptrMusicTmp = ptrMusic;
        ptrMusic = ptrMusic->next;
        free(ptrMusicTmp->name);
        free(ptrMusicTmp);
    }

    ptrHash = ptr->hash;
    while (ptrHash->next != NULL)
    {
        ptrHashTmp = ptrHash;
        ptrHash = ptrHash->next;
        free(ptrHashTmp);
    }

    free(ptr);
}


