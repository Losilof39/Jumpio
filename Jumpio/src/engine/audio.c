#include "audio.h"
#include "log.h"

void Audio_Init()
{
    SDL_AudioSpec spec;

    /* Initialize variables */
    spec.freq = MIX_DEFAULT_FREQUENCY;
    spec.format = MIX_DEFAULT_FORMAT;
    spec.channels = MIX_DEFAULT_CHANNELS;

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        log_error("Unable to set up sound.");
    }

    if (!Mix_Init(MIX_INIT_MP3)) {
        log_error("Couldn't initialize audio with MP3 support: %s", SDL_GetError());
    }

    if (!Mix_OpenAudio(0, &spec)) {
        log_error("Couldn't open audio: %s", SDL_GetError());
    }
    else 
    {
        Mix_QuerySpec(&spec.freq, &spec.format, &spec.channels);
    }

    if (Mix_AllocateChannels(NUM_CHANNELS_MAX) != NUM_CHANNELS_MAX)
    {
        log_error("Couldn't allocate %d channels: %s", NUM_CHANNELS_MAX, SDL_GetError());
    }

    log_info("Opened audio at %d Hz %d bit%s %s audio buffer", spec.freq,
        (spec.format & 0xFF),
        (SDL_AUDIO_ISFLOAT(spec.format) ? " (float)" : ""),
        (spec.channels > 2) ? "surround" : (spec.channels > 1) ? "stereo" : "mono");
}

void Audio_Cleanup()
{
    Mix_CloseAudio();
}

Mix_Chunk* Audio_LoadWav(char* file)
{
    return Mix_LoadWAV(file);
}

Mix_Chunk* Audio_LoadMP3(char* file)
{
    return Mix_LoadWAV(file);
}

void Audio_PlaySong()
{
}

void Audio_StopSong()
{
}

void Audio_PauseSong()
{
}

void Audio_ResumeSong()
{
}

void Audio_SetMusicVolume(u32 vol)
{
    Mix_VolumeMusic(vol);
}

void Audio_PlaySound(Mix_Chunk* snd, b8 loop)
{
    Mix_PlayChannel(0, snd, loop);
}

void Audio_StopSound()
{
}

b8 Audio_IsSoundPlaying(u32 channel)
{
    if (channel < 0 || channel >= NUM_CHANNELS_MAX)
    {
        return false;
    }

    return Mix_Playing(channel);
}

b8 Audio_IsMusicPlaying()
{
    return Mix_PlayingMusic();
}
