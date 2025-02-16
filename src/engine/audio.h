#ifndef AUDIO_H
#define AUDIO_H

#include "data_types.h"
#include <SDL3/SDL_mixer.h>

#define NUM_CHANNELS_MAX 32

void Audio_Init();
void Audio_Cleanup();

Mix_Chunk* Audio_LoadWav(char* file);

void Audio_PlaySong();
void Audio_StopSong();
void Audio_PauseSong();
void Audio_ResumeSong();
void Audio_SetMusicVolume(u32 vol);

void Audio_PlaySound(Mix_Chunk* snd, b8 loop);
void Audio_StopSound();
b8 Audio_IsSoundPlaying(u32 channel);

b8 Audio_IsMusicPlaying();

#endif