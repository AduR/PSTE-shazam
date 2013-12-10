#ifndef CONSTANTES_H
#define CONSTANTES_H

typedef struct      s_hash
{
    uint64_t        hash;
    uint64_t        id_music; // may be uint16_t
    struct s_hash   *next;
}                   t_hash;

#endif /* CONSTANTES_H */
