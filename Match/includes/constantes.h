#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>
#include <sys/types.h>

#include <stdint.h>     // uint64_t
#include <inttypes.h>   // uint64_t printf and scanf


#define BUF_SIZE    1024
#define PATH        "./Hash/"
#define NB_HASH     30 // to remove

typedef struct      s_hash
{
    uint64_t        id_music; // may be uint16_t
    uint64_t        hash;
    struct s_hash   *next;
}                   t_hash;

typedef struct      s_music
{
    uint64_t        id_music; // may be uint16_t
    char            *name;
    // add other stuff like artist name
    struct s_music  *next;
}                   t_music;

typedef struct      s_data
{
    t_music         *music;
    t_hash          *hash;
}                   t_data;

#endif /* CONSTANTES_H */
