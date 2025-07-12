#ifndef MUSIC_H
#define MUSIC_H

#include <SDL3/SDL_audio.h>

typedef struct{
    char title[64];
    char path[256];
    int ID;
} Song;

#endif
