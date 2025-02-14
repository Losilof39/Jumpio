#ifndef AUDIO_H
#define AUDIO_H

#include "core.h"

#define NUM_CHANNELS_MAX 32

void Audio_Init();
void Audio_Cleanup();

void Audio_PlaySong();
void Audio_StopSong();
void Audio_PauseSong();
void Audio_ResumeSong();
void Audio_SetMusicVolume(u32 vol);

void Audio_PlaySound();
void Audio_StopSound();
b8 Audio_IsSoundPlaying(u32 channel);

b8 Audio_IsMusicPlaying();

#endif