/*******************************************************************************
*
*  File Name : ft_loadHash.c
*
*  Purpose :
*
*  Creation Date : 07-01-14 10:57:08
*
*  Last Modified : 07-01-14 15:27:20
*
*  Created By : Nodraak
*
*******************************************************************************/

#include <string.h>

#include "constantes.h"
#include "ft_loadHash.h"

///////////////////////////////////////////////////////////

t_data *ft_load_data(void)
{
    t_data *head = NULL;
    t_music *ptrMusic = NULL;
    t_hash *ptrHash = NULL;
    DIR *dir = NULL;
    uint64_t idFile = 1;
    char *filePath = NULL;

    head = ft_malloc(sizeof(t_data), __FILE__, __LINE__);
    dir = ft_open_dir(PATH);

    while ((filePath = ft_read_dir(dir, PATH)) != NULL)
    {
        if (ptrMusic == NULL) // first time
        {
            ft_add_music(filePath, idFile, &head->music, &head->hash);
            ptrMusic = head->music;
            ptrHash = head->hash;
        }
        else
            ft_add_music(filePath, idFile, &ptrMusic->next, &ptrHash->next);
        ptrMusic = ptrMusic->next;
        ptrHash = ptrHash->next;

        idFile++;
    }

    /* dir is closed in ft_read_dir() */
    return head;
}

void ft_add_music(char *filePath, uint64_t idFile,
                    t_music **ptrMusic, t_hash **ptrHash)
{
    FILE *file = NULL;
    char buf[BUF_SIZE];
    uint64_t hash;

    file = ft_fopen(filePath);

    while (!feof(file))
    {
        fgets(buf, BUF_SIZE-1, file);
        sscanf(buf, "%"SCNu64, &hash);

        *ptrMusic = ft_create_elem_music(idFile, filePath);
        *ptrHash = ft_create_elem_hash(idFile, hash);
    }

    fclose(file);
}

///////////////////////////////////////////////////////////

void *ft_malloc(size_t size, char *s, int l)
{
    void *ptr;

    ptr = malloc(size);
    if (ptr == NULL)
    {
        fprintf(stderr, "Malloc failed from %s l.%d with size %zd bytes.\n",
                    s, l, size);
    }
    return ptr;
}

t_music *ft_create_elem_music(uint64_t idFile, char *filePath)
{
    t_music *ptr;

    ptr = ft_malloc(sizeof(t_music), __FILE__, __LINE__);

    ptr->id_music = idFile;
    ptr->name = filePath;
    ptr->next = NULL;

    return ptr;
}

t_hash *ft_create_elem_hash(uint64_t idFile, uint64_t hash)
{
    t_hash *ptr;

    ptr = ft_malloc(sizeof(t_hash), __FILE__, __LINE__);

    ptr->id_music = idFile;
    ptr->hash = hash;
    ptr->next = NULL;

    return ptr;
}

//////////////////////////////////////////////////////////////////

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

    s = ft_malloc(BUF_SIZE, __FILE__, __LINE__);
    sprintf(s, "%s%s", path, file->d_name);

    return s;
}

FILE *ft_fopen(char *path)
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


