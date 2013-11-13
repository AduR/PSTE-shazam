/*******************************************************************************
*
*  File Name : sdl.c
*
*  Purpose : sdl functions - to draw the spectrogramme from the fmod tab to a bmp
*
*  Creation Date : 28-10-13 14:41:29
*
*  Last Modified : 13-11-13 14:41:29
*
*  Created By : achardon
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "constantes.h"
#include "sdl.h"

void ft_sdl_print_error(char *s, char *file, int line)
{
    while (*file != '\0')
        file++;
    while (*file != '\\')
        file--;
    file++;

    printf("erreur %s in %s:%d : %s\n", s, file, line, SDL_GetError());

    printf("pause ...");
    getchar();

    exit(EXIT_FAILURE);
}

SDL_Window *ft_init_sdl(void)
{
	SDL_Window *window = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_sdl_print_error("ft_init_sdl:sdl_init", __FILE__, __LINE__);

    //Create window
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
        ft_sdl_print_error("ft_init_sdl:create_window", __FILE__, __LINE__);

    return window;
}

void ft_free_sdl(SDL_Window *window)
{
    SDL_DestroyWindow(window);
	SDL_Quit();
}

#if 0
stuff :
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 255, 255));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
#endif
