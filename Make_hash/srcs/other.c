/*******************************************************************************
*
*  File Name :
*
*  Purpose :
*
*  Creation Date : 09-12-13 13:45:35
*
*  Last Modified : 09-12-13 15:55:29
*
*  Created By :
*
*******************************************************************************/

int my_abs_cast_norm(double n)
{
    return (n < 0 ? (int)(-n)/INTENSITY_DIV : (int)(n)/INTENSITY_DIV);
}

void ft_print_spect(t_fft *fft, char *path)
{
    unsigned int times, i;

    printf("file : %s\nfft->lenb : %d chunks\nfft-lent : %.3f sec\n",
            path, fft->lenB, fft->lenT);
    printf("echant %d\n\n", ECHANT);

    for (times = 0; times < fft->lenB; times++)
    {
        printf("===== chunk %d/%d, time sec %.3f/%.3f =====\n",
                times, fft->lenB, (double)times*fft->lenT/fft->lenB, fft->lenT);
        for (i = 0; i < CHUNK_SIZE; i++)
            printf("%d\t%d\t%d\n", i * ECHANT / CHUNK_SIZE,
                                    my_abs_cast_norm(fft->out[times][i][0]),
                                    my_abs_cast_norm(fft->out[times][i][1]));
    }
}

