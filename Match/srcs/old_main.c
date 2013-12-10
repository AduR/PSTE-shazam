/*******************************************************************************
*
*  File Name : main.c
*
*  Purpose :
*
*  Creation Date : 03-12-13 18:57:08
*
*  Last Modified : 09-12-13 17:02:53
*
*  Created By : Nodraak
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

#include <string.h>
#include <time.h>

#include "constantes.h"

#define BUF_SIZE    1000
#define NB_HASH     10

char *ft_get_next_file(void)
{
    static DIR *dir = NULL;
    static struct dirent *file = NULL;
    static char *s = NULL;

    if (dir == NULL)
    {
        dir = opendir("./Hash");
        if (dir == NULL)
        {
            perror("erreur opendir\n");
            exit(EXIT_FAILURE);
        }
        // read . and ..
        file = readdir(dir);
        file = readdir(dir);
    }

    file = readdir(dir);
    if (file == NULL)
    {
        closedir(dir);
        return NULL;
    }

    if (s != NULL)
        free(s), s = NULL;
    s = malloc(BUF_SIZE);
    sprintf(s, "%s%s", "./Hash/", file->d_name);

    return s;
}

long int my_abs(long int nb)
{
    return (nb < 0 ? -nb : nb);
}

int ft_get_matchs(FILE *ref, FILE *f)
{
    char s1[BUF_SIZE+1], s2[BUF_SIZE+1];
    unsigned int n1, n2, matchs = 0;

    while (!feof(ref))
    {
        fgets(s1, BUF_SIZE, ref);
        sscanf(s1, "%u", &n1);

        rewind(f);
        while (!feof(f))
        {
            fgets(s2, BUF_SIZE, f);
            sscanf(s2, "%u", &n2);

            if (my_abs(n1-n2) == 0)
                matchs++;
        }
    }

    return matchs;
}

FILE *my_fopen(char *path)
{
    FILE *f = fopen(path, "r");
    if (f == NULL)
    {
        printf("Erreur my_fopen for file %s.\n", path);
        exit(EXIT_FAILURE);
    }
    return f;
}


int main(int argc, char *argv[])
{
    FILE *ref = NULL, *f = NULL;
    char *s = NULL, *musics[NB_HASH];
    t_hash hash[NB_HASH];
    uint64_t i = 0, current_musique = 0;
    char s2[BUF_SIZE];

    // malloc



printf("%lums\n", clock()*1000/CLOCKS_PER_SEC);

    if (argc != 2)
    {
        printf("usage : ./prog hash_unknow.txt\n");
        return 0;
    }

    f = my_fopen(argv[1]);

printf("=== start loading hash ===\n");
    do {
printf("start %lums\n", clock()*1000/CLOCKS_PER_SEC);
        s = ft_get_next_file();

        if (s != NULL && strcmp(argv[1], s) != 0)
        {
            ref = my_fopen(s);
            musics[current_musique] = strdup(s);

            while (!feof(ref))
            {
                unsigned int n2;
                fgets(s2, BUF_SIZE, ref);
                sscanf(s2, "%u", &n2);
                hash[i].hash = n2;
                hash[i].id_musique = current_musique;
                i++;
            }
            current_musique++;
            //int n = ft_get_matchs(ref, f);
            //printf("File %s\t%d similitudes.\n", s, n);

            fclose(ref);
        }
printf("end %lums\n", clock()*1000/CLOCKS_PER_SEC);
    } while (s != NULL);
    
    printf("=== start computing ===\n");
     i = 0, current_musique = 0;
    do {
printf("start %lums\n", clock()*1000/CLOCKS_PER_SEC);
        //s = ft_get_next_file();

        if (s != NULL && strcmp(argv[1], s) != 0)
        {
            ref = my_fopen(musics[current_musique]);

            while (!feof(ref))
            {
                unsigned int n2;
                fgets(s2, BUF_SIZE, ref);
                sscanf(s2, "%u", &n2);

                int j;
                for (j = 0; j < XX; j++)
                {
                    if (n2 == hash[i].hash)
                        hash[i].match++;
                }
                i++;
            }
            current_musique++;
            //int n = ft_get_matchs(ref, f);
            //printf("File %s\t%d similitudes.\n", s, n);

            fclose(ref);
        }
printf("end %lums\n", clock()*1000/CLOCKS_PER_SEC);
    } while (s != NULL);


    fclose(f);
printf("%lums\n", clock()*1000/CLOCKS_PER_SEC);

    return 0;
}


