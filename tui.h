#ifndef TUI_H
#define TUI_H

#include <ncurses.h>
#include "music.h"
#include "library.h"

void draw_header(WINDOW* win, int page, int middle);
void draw_library(WINDOW* win, Playlist* playlists, int size, int highlight);
void draw_collection(WINDOW* win, Song* songs, int size, int highlight);
void draw_playlist(WINDOW* win,Song* songs, Playlist* playlist, int highlight);
void draw_playlist_get_name(WINDOW* win, int highlight);

#endif
