/*******************************************************************************
*
*  File Name : main.c
*
*  Purpose :
*
*  Creation Date : 03-12-13 18:57:08
*
*  Last Modified : 10-12-13 14:59:47
*
*  Created By : Nodraak
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#include <time.h>

#include "constantes.h"

#define BUF_SIZE    1000
#define NB_HASH     30      // nb hash files, not single hash
#define PATH        "./Hash/"

// chained list
t_hash *ft_create_elem(uint64_t hash, uint64_t id);
// init
t_hash *ft_load_hash(void);
// files
DIR *ft_open_dir(char *path);
char *ft_read_dir(DIR *dir, char *path);
FILE *my_fopen(char *path);
// free
void ft_free(t_hash *head);

int ft_get_matchs(t_hash *root, FILE *file);
void ft_compute(t_hash *root, char *path);

///////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    t_hash *head;

    if (argc != 2)
    {
        printf("Error, need hash file to analyse.\n");
        return 0;
    }

    head = ft_load_hash();
    ft_compute(head, argv[1]);

    ft_free(head);
    return 0;
}

///////////////////////////////////////////////////////////

void ft_compute(t_hash *root, char *path)
{
    int id;
    FILE *f;

    f = my_fopen(path);
    id = ft_get_matchs(root, f);

    //printf("result : %d\n", id);
}


/////////////////////////////////////////////////////////////

t_hash *ft_create_elem(uint64_t hash, uint64_t id)
{
    t_hash *ptr;

    ptr = malloc(sizeof(t_hash));
    if (ptr == NULL)
    {
        char s[BUF_SIZE];
        sprintf(s, "Error in ft_create_elem() in %s l.%d ", __FILE__, __LINE__);
        perror(s);
        exit(EXIT_FAILURE);
    }
    ptr->hash = hash;
    ptr->id_music = id;

    return ptr;
}

t_hash *ft_load_hash(void)
{
    t_hash *root = NULL, *ptr = NULL;
    char *file_path = NULL, buf[BUF_SIZE];
    uint64_t hash, current_file = 1;
    DIR *dir = NULL;
    FILE *file = NULL;

    dir = ft_open_dir(PATH);

    while ((file_path = ft_read_dir(dir, PATH)) != NULL)
    {
        file = my_fopen(file_path);
        printf("%llu %s\n", current_file, file_path);

        while (!feof(file))
        {
            fgets(buf, BUF_SIZE-1, file);
            sscanf(buf, "%" SCNu64, &hash);
            if (root == NULL)
            {
                root = ft_create_elem(hash, current_file);
                ptr = root;
            }
            else
            {
                ptr->next = ft_create_elem(hash, current_file);
                ptr = ptr->next;
            }
        }
        current_file++;

        fclose(file);
        free(file_path);
    }
    // dir is closed in ft_read_dir()

    return root;
}

DIR *ft_open_dir(char *path)
{
    DIR *dir;

    dir = opendir(path);
    if (dir == NULL)
    {
        perror("Error ft_open_dir() ");
        exit(EXIT_FAILURE);
    }

    // read . and ..
    readdir(dir);
    readdir(dir);

    return dir;
}

char *ft_read_dir(DIR *dir, char *path)
{
    struct dirent *file;
    char *s;

    file = readdir(dir);
    if (file == NULL)
    {
        closedir(dir);
        return NULL;
    }

    s = malloc(BUF_SIZE);
    sprintf(s, "%s%s", path, file->d_name);

    return s;
}

FILE *my_fopen(char *path)
{
    FILE *f = fopen(path, "r");

    if (f == NULL)
    {
        char s[BUF_SIZE];
        sprintf(s, "Erreur my_fopen for file %s ", path);
        perror(s);
        exit(EXIT_FAILURE);
    }

    return f;
}

void ft_free(t_hash *head)
{
    t_hash *ptr;

    while (head != NULL)
    {
        ptr = head;
        head = head->next;
        free(ptr);
    }
}


//////////////////////////////////////////////////////////////////////

//printf("%lums\n", clock()*1000/CLOCKS_PER_SEC);

int ft_get_matchs(t_hash *root, FILE *file)
{
    char s[BUF_SIZE];
    uint64_t hash, i, max, id_max1, id_max2;
    t_hash *ptr;
    uint64_t tab[NB_HASH] = {0};

    while (!feof(file))
    {
        fgets(s, BUF_SIZE-1, file);
        sscanf(s, "%" SCNu64, &hash);
        ptr = root;

        while (ptr != NULL)
        {
            if (hash == ptr->hash)
                tab[ptr->id_music]++;
            ptr = ptr->next;
        }
    }

    printf("== results ==\n");
    for (i = 0; i < NB_HASH; i++)
    {
        printf("%llu with %llu matchs\n", i, tab[i]);
    }

/*
    max = 0;
    for (i = 0; i < NB_HASH; i++)
    {
        if (tab[i] > max && i != id_max1)
            max = tab[i], id_max2 = i;
    }
    printf("result 2 : %llu with %llu matchs\n", id_max2, max);
*/
    return id_max1;
}


