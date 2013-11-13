#ifndef SDL_H_INCLUDED
#define SDL_H_INCLUDED

void ft_sdl_print_error(char *s, char *file, int line);
SDL_Window *ft_init_sdl(void);
void ft_free_sdl(SDL_Window *window);

#endif // SDL_H_INCLUDED
