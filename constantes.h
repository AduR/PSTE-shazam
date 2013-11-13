#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED


#if 0
    FMOD_RESULT FMOD_DSP_SetActive(
  FMOD_DSP *  dsp,
  FMOD_BOOL  active
);

FMOD_RESULT FMOD_System_AddDSP(
  FMOD_SYSTEM *  system,
  FMOD_DSP *  dsp,
  FMOD_DSPCONNECTION **  connection
);



FMOD_RESULT FMOD_System_CreateDSP(
  FMOD_SYSTEM *  system,
  FMOD_DSP_DESCRIPTION *  description,
  FMOD_DSP **  dsp
);


FMOD_RESULT FMOD_Channel_AddDSP(
  FMOD_CHANNEL *  channel,
  FMOD_DSP *  dsp,
  FMOD_DSPCONNECTION **  connection
);

FMOD_RESULT FMOD_DSP_GetActive(
  FMOD_DSP *  dsp,
  FMOD_BOOL *  active
);

FMOD_RESULT FMOD_DSP_SetActive(
  FMOD_DSP *  dsp,
  FMOD_BOOL  active
);

FMOD_RESULT DSP::getDefaults(
  float *  frequency,
  float *  volume,
  float *  pan,
  int *  priority
);

FMOD_RESULT FMOD_DSP_SetDefaults(
  FMOD_DSP *  dsp,
  float  frequency,
  float  volume,
  float  pan,
  int  priority
);

FMOD_RESULT FMOD_DSP_SetSpeakerActive(
  FMOD_DSP *  dsp,
  FMOD_SPEAKER  speaker,
  FMOD_BOOL  active
);


/*==== tuto ====*/

result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
result = channel->setVolume(volume);
result = system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
result = channel->addDSP(dsp, 0);

/* system */
result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
result = channel->setVolume(volume);
result = system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
result = system->addDSP(dsp, 0);

#endif




/* include */
#include <fmod/fmod.h>
#include <SDL2/SDL.h>

 /* define */
#define SCREEN_WIDTH        1000
#define SCREEN_HEIGHT       600

#define FPS                 40 /* 40 ideally == fmod refresh delay */
#define FPS_DELAY           (1000/FPS)

#define NB_FREQ             128
#define SPECTRUM_COR        500 /* should be 255 - fmod return between 0 and 1 */
#define MUL_Y               5
#define MUL_X               4

#define MY_PI               3.1415926539

#define MUSIC_PATH          "son15k.mp3"

 /* struct */
typedef struct      s_fmodSound
{
    FMOD_SYSTEM     *system;
    FMOD_SOUND      *sound;
    FMOD_CHANNEL    *channel;
}                   t_fmodSound;

typedef struct      s_soundSpect
{
    unsigned int    music_len;
    unsigned int    tab_len;
    unsigned int    nb_freq;
    float           **tab;
}                   t_soundSpect;

#endif /* CONSTANTES_H_INCLUDED */
