/*******************************************************************************
*
*  File Name : main.c
*
*  Purpose : main file - one function to move
*
*  Creation Date : 28-10-13 14:39:29
*
*  Last Modified : 13-11-13 14:39:29
*
*  Created By : achardon
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <fmod/fmod.h>
#include <SDL2/SDL.h>

#include "constantes.h"
#include "fmod.h"
#include "sdl.h"

void ft_blit_spect_to_surface(t_soundSpect *spect, SDL_Surface *screen);


int main(int argc, char *argv[])
{
    (void)argc, (void)argv;
    t_soundSpect *spect;
    SDL_Window *window;

    spect = ft_get_spect();
    window  = ft_init_sdl();
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    ft_blit_spect_to_surface(spect, screen);
    SDL_UpdateWindowSurface(window);
    SDL_SaveBMP(screen, "out.bmp");

    /* free */
    ft_free_tab(spect);
    ft_free_sdl(window);

    /* because windows dont wait for us to see the sdl spectrogramme while codeblocks do */
    printf("pause ...");
    getchar();

    return 0;
}

void ft_blit_spect_to_surface(t_soundSpect *spect, SDL_Surface *screen)
{
    unsigned int x, y;
    int b; /* blue color component - used to show the intensity in the spectrogramme */
    SDL_Rect pos;

    SDL_Surface *pixel = SDL_CreateRGBSurface(SDL_SWSURFACE, MUL_X, MUL_Y, 32, 0, 0, 0, 0);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

    for (x = 0; x < spect->tab_len; x++)
    {
printf("=== frame %d - time %.3f ===\n", x, (float)x*FPS/1000);
        for (y = 0; y < NB_FREQ; y++)
        //for (y = 0; y < spect->nb_freq; y++)
        {
            pos.x = x*MUL_X;
            pos.y = y*MUL_Y;

            b = (int)(spect->tab[x][y] * SPECTRUM_COR);

            if (b > 255) /* red */
                SDL_FillRect(pixel, NULL, SDL_MapRGB(pixel->format, 128, 0, 0));
            else if (b < 0) /* green */
                SDL_FillRect(pixel, NULL, SDL_MapRGB(pixel->format, 0, 128, 0));
            else
                SDL_FillRect(pixel, NULL, SDL_MapRGB(pixel->format, 0, 0, b));
            SDL_BlitSurface(pixel, NULL, screen, &pos);
        }
    }

    printf("posx = %d\nposy = %d\n", x*MUL_X, y*MUL_Y);

    SDL_FreeSurface(pixel);
}

