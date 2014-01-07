#ifndef FT_LOADHASH_H
#define FT_LOADHASH_H

t_data *ft_load_data(void);
t_hash *ft_add_music(char *filePath, uint64_t idFile, t_hash *head);

void *ft_malloc(size_t size, char *s, int l);
t_music *ft_create_elem_music(uint64_t idFile, char *filePath);
t_hash *ft_create_elem_hash(uint64_t idFile, uint64_t hash);

DIR *ft_open_dir(char *path);
char *ft_read_dir(DIR *dir, char *path);
FILE *ft_fopen(char *path);

#endif /* FT_LOADHASH_H */
