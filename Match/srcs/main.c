/*******************************************************************************
*
*  File Name : main.c
*
*  Purpose :
*
*  Creation Date : 03-12-13 18:57:08
*
*  Last Modified : 07-01-14 18:39:37
*
*  Created By : Nodraak
*
*******************************************************************************/

#include <time.h>

#include "constantes.h"
#include "ft_loadHash.h"
#include "ft_compare.h"
#include "ft_result.h"

void ft_free(t_data *ptr);
void ft_print_data(t_data *head); // debug

void ft_print_number(clock_t n);
void ft_print_time(char *s);

int main(int argc, char *argv[])
{
    t_data *head;
    uint64_t *tab;

    if (argc != 2)
    {
        printf("Error, need hash file as param to compare.\n");
        return 0;
    }

ft_print_time("> start");
    head = ft_load_data();
ft_print_time("> load");
    tab = ft_compare(head, argv[1]);
ft_print_time("> compare");
    ft_print_result(tab, head);

    ft_free(head);
    free(tab);
    return 0;
}

void ft_free(t_data *ptr)
{
    t_music *ptrMusic = NULL, *ptrMusicTmp;
    t_hash *ptrHash = NULL, *ptrHashTmp;

    ptrMusic = ptr->music;
    while (ptrMusic != NULL)
    {
        ptrMusicTmp = ptrMusic;
        ptrMusic = ptrMusic->next;
        free(ptrMusicTmp->name);
        free(ptrMusicTmp);
    }

    ptrHash = ptr->hash;
    while (ptrHash != NULL)
    {
        ptrHashTmp = ptrHash;
        ptrHash = ptrHash->next;
        free(ptrHashTmp);
    }

    free(ptr);
}


//==== debug =====

void ft_print_number(clock_t n)
{
    if (n < 1000)
    {
        printf("%lu", n);
    }
    else
    {
        ft_print_number(n/1000);
        printf(" %03lu", n%1000);
    }
}

void ft_print_time(char *s)
{
    static clock_t time = 0;

    printf("%s : ", s);
    ft_print_number(clock() - time);
    printf("\n");
    time = clock();
}

void ft_print_data(t_data *head)
{
    t_hash *ptrHash = head->hash;
    t_music *ptrMusic = head->music;
    int i = 0;

    printf("========\n");
    while (ptrMusic != NULL)
    {
        printf("%llu %s\n", ptrMusic->id_music, ptrMusic->name);
        ptrMusic = ptrMusic->next;
    }

    printf("========\n");
    while (ptrHash != NULL && ++i < 20)
    {
        printf("%llu\n", ptrHash->hash);
        ptrHash = ptrHash->next;
    }
}

