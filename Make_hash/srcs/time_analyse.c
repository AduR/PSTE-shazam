/*******************************************************************************
*
*  File Name : time_analyse.c
*
*  Purpose :
*
*  Creation Date : 23-11-13 15:55:04
*
*  Last Modified : 03-01-14 21:07:04
*
*  Created By : adur
*
*******************************************************************************/

#include <time.h>
#include <stdio.h>

void ft_print_number(clock_t n)
{
    if (n < 1000)
    {
        fprintf(stderr, "%lu", n);
    }
    else
    {
        ft_print_number(n/1000);
        fprintf(stderr, " %03lu", n%1000);
    }
}

void ft_print_time(char *s)
{
    static clock_t time = 0;

    fprintf(stderr, "%s : ", s);
    ft_print_number(clock() - time);
    fprintf(stderr, "\n");
    time = clock();
}

