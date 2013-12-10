#ifndef FT_INIT_H
#define FT_INIT_H

t_wav *ft_init_wav(char *path);
t_fft *ft_init_fft(Uint32 wav_len);
void ft_perform_fft(t_fft *fft, t_wav *wav);

void ft_free_wav(t_wav *wav);
void ft_free_fft(t_fft *fft);

#endif /* FT_INIT_H */
