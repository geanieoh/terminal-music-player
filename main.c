#include <stdio.h>
#include <locale.h>
#include <SDL3/SDL.h>
#include "music.h"
#include "library.h"
#include "tui.h"

int main(){
    setlocale(LC_ALL, "");

    Playlist playlists[256];
    Song songs[256];
    for(int i = 0; i < 256; i++){
        playlists[i].ID = -1;
        playlists[i].songCount = 0;
        songs[i].ID = -1;
    }
    int songCount, playlistCount;

    library_parse(songs, playlists, &songCount, &playlistCount);

    char nameBuff[36];
    int buffIndex = 0;

    SDL_AudioStream* stream = NULL;
    SDL_AudioSpec spec;
    unsigned char* wav_data = NULL;
    unsigned int wav_data_len = 0;

    initscr();
    noecho();

    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    WINDOW* win = newwin(maxy, maxx, 0, 0);
    WINDOW* inputwin = newwin(maxy/4, maxx/4, (maxy/2) - (maxy/8), (maxx/2) - (maxx/8));

    keypad(win, 1);
    
    
    int c, maxElements = songCount - 1, page = 0, highlight = 0, playlistOpened = 0, addingPlaylist = 0, playlistChosen;
    draw_header(win, page, (maxx/2) - (33/2));
    while(1){
        curs_set(0);

        //draw
        switch(page){
            case 0:
                if(playlistOpened){
                    draw_playlist(win, songs, &playlists[playlistChosen], highlight);
                    maxElements = playlists[playlistChosen].songCount;
                }
                else{
                    draw_library(win, playlists, playlistCount, highlight);
                    maxElements = playlistCount - 1;
                }
                if(addingPlaylist){
                    draw_playlist_get_name(inputwin, highlight);
                    maxElements = 1;
                }
                break;
            case 1:
                draw_collection(win, songs, songCount, highlight);
                maxElements = songCount - 1;
                break;
            case 2:
                mvwprintw(win, 5, 1, "COMING SOON");
                refresh();
                break;
        }
        refresh();
        wrefresh(win);
        wrefresh(inputwin);

        //process input
        c = wgetch(win);
        switch(c){
            case KEY_UP:
                highlight--;
                if(highlight < 0) highlight = maxElements;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight > maxElements) highlight = 0;
                break;
            case 9:
                if(!addingPlaylist){
                    page++;
                    highlight = 0;
                    if(page > 2) page = 0;
                    wclear(win);
                    draw_header(win, page, (maxx/2) - (33/2));
                }
                break;
            case 10:
                if(page == 0){
                    if(addingPlaylist){
                        if(highlight == 0){
                            nameBuff[buffIndex + 1] = '\0';
                            playlist_create(nameBuff, playlists, &playlistCount);
                        }
                    }
                    else if(!playlistOpened){
                        playlistOpened = 1;
                        playlistChosen = highlight;
                        highlight = 0;
                    }
                    else{
                        //playsong
                        ;
                    }
                }
                else if(page == 1){
                    SDL_LoadWAV(songs[highlight].path, &spec, &wav_data, &wav_data_len);
                    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
                    SDL_ResumeAudioStreamDevice(stream);
                }
                break;
            case 'i':
                if(page == 0 && !addingPlaylist){
                    addingPlaylist = 1;
                }
                break;
            default:
                break;
        }
        if(c == 27 && !addingPlaylist) break;
        if(addingPlaylist){
            if(c == 27){
                addingPlaylist = 0;
            }
            else if(c > 37 && c < 127){
                nameBuff[buffIndex] = c;
                if(buffIndex < 34) buffIndex++;
                mvwaddch(inputwin, 3, buffIndex, c);
            }
        }
    }
 
    endwin();

    return 0;
}
