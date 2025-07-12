#ifndef LIBRARY_H
#define LIBRARY_H

#include "music.h"

typedef struct{
    unsigned int songs[256];
    char name[64];
    int songCount;
    int ID;
} Playlist;

void library_parse(Song* songs, Playlist* playlists, int* sCount, int* pCount);
void playlist_create(char* name, Playlist* playlists, int* count);

#endif
