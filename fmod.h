#ifndef FMOD_H_INCLUDED
#define FMOD_H_INCLUDED

void ft_fmod_check_error(FMOD_RESULT result, char *s, char *file, int line);

void ft_init_system(t_fmodSound *sound);
void ft_init_sound(t_fmodSound *sound, char *path);
void ft_init_tab(t_soundSpect *spect);

void ft_free_tab(t_soundSpect *spect);
void ft_free_sound(t_fmodSound *sound);

unsigned int ft_get_sound_length(t_fmodSound *sound);

void ft_init_sound_spect(t_fmodSound *sound, t_soundSpect **spect);
void ft_fill_spect(t_fmodSound *sound, t_soundSpect *spect);
t_soundSpect *ft_get_spect(void);

#endif // FMOD_H_INCLUDED
