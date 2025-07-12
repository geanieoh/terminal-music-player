#include "tui.h"

void draw_library(WINDOW* win, Playlist* playlists, int size, int highlight){
    for(int i = 0; i < size; i++){
        if(i == highlight) wattron(win, A_REVERSE);
    
        mvwprintw(win, i + 5, 1, playlists[i].name);
        wattroff(win, A_REVERSE);
        refresh();
    }
}

void draw_collection(WINDOW* win, Song* songs, int size, int highlight){
    for(int i = 0; i < size; i++){
        if(i == highlight) wattron(win, A_REVERSE);
        
        mvwprintw(win, i + 5, 1, songs[i].title);
        wattroff(win, A_REVERSE);
        refresh();
    }
}

void draw_header(WINDOW* win, int page, int middle){
    if(page == 0) wattron(win, A_REVERSE);
    mvwprintw(win, 1, middle, "LIBRARY");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 1, middle + 7, " - ");

    if(page == 1) wattron(win, A_REVERSE);
    mvwprintw(win, 1, middle + 10, "COLLECTION");
    wattroff(win, A_REVERSE);
    mvwprintw(win, 1, middle + 20, " - ");

    if(page == 2) wattron(win, A_REVERSE);
    mvwprintw(win, 1, middle + 23, "DOWNLOAD");
    wattroff(win, A_REVERSE);
}

void draw_playlist(WINDOW* win, Song* songs, Playlist* playlist, int highlight){
    for(int i = 0; i < playlist->songCount; i++){
        if(i == highlight) wattron(win, A_REVERSE);
    
        mvwprintw(win, i + 5, 1, songs[playlist->songs[i]].title);
        wattroff(win, A_REVERSE);
        refresh();
    }
}

void draw_playlist_get_name(WINDOW* win, int highlight){
    char options[2][16] = {"   Done   ", "  Cancel  "};

    box(win, 0, 0);
    refresh();
    wrefresh(win);

    mvwprintw(win, 1, 12, "Name Playlist");
    refresh();
    for(int i = 0; i < 2; i++){
        if(i == highlight) wattron(win, A_REVERSE);
        
        mvwprintw(win, i + 5, 13, options[i]);
        wattroff(win, A_REVERSE);
        refresh();
    }
    wrefresh(win);
}
