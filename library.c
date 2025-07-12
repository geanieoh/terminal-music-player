#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "library.h"

void library_add_songs(Song* songs, int* Count);

void library_parse(Song* songs, Playlist* playlists, int* sCount, int* pCount){
    library_add_songs(songs, sCount);

    FILE* file = fopen("library/library.txt", "r");
    if(!file){
        file = fopen("library/library.txt", "w");
        fclose(file);
        *sCount = 0;
        *pCount = 0;
        return;
    }
    
    int pID = 0, songsInPlaylist;
    char buff[256];
    while(fgets(buff, sizeof(buff), file)){
        if(buff[0] == 'p'){
            songsInPlaylist = 0;
            Playlist playlist;
            for(int i = 2; i < sizeof(buff); i++){
                if(buff[i] == '\n'){
                    playlist.name[i - 2] = '\0';
                    break;
                }
                playlist.name[i - 2] = buff[i];
            }
            playlist.ID = pID;
            playlists[pID] = playlist;            

            pID++;
        }
        
        if(buff[0] == 's'){
            int num;
            sscanf(buff, "s %d", &num);
            
            if(songs[num].ID != -1){
                playlists[pID - 1].songs[songsInPlaylist] = songs[num].ID;
                playlists[pID - 1].songCount++;
                songsInPlaylist++;
            }
        }
    }
    *pCount = pID;

    fclose(file);
}

void library_add_songs(Song* songs, int* count){
    int songsCount = 0;
    struct dirent* entry;
    DIR* dir = opendir("library");
    if(!dir){
        printf("'library' directory not found");
        return;
    }

    while(entry = readdir(dir)){
        int songFound = 0, i;
        if(entry->d_name[0] == '.' && (entry->d_name[1] == '\0' || entry->d_name[2] == '\0')) continue; //current directory reads as "." and parent directory reads as ".."

        for(i = 0; i < 256; i++){
            if(entry->d_name[i] == '.' && entry->d_name[i + 1] == 'w' && entry->d_name[i + 4] == '\0'){
                songFound = 1;
                break;
            }
        }
        
        if(songFound){
            Song song;
            song.ID = songsCount;
            song.path[0] = 'l'; song.path[1] = 'i'; song.path[2] = 'b'; song.path[3] = 'r'; song.path[4] = 'a'; song.path[5] = 'r'; song.path[6] = 'y'; song.path[7] = '/';
            for(int j = 0; j < i + 4; j++){
                song.path[j + 8] = entry->d_name[j];
            }
            song.path[i + 12] = '\0';
            for(int j = 0; j < i; j++){
                song.title[j] = entry->d_name[j];
            }
            song.title[i] = '\0';
            songs[songsCount] = song;
            songsCount++;
        }
    }   
    *count = songsCount;
 
    closedir(dir);
}

void playlist_add_song(char* path, char* playlist){

}

void playlist_create(char* name, Playlist* playlists, int* count){
    FILE* file = fopen("library/library.txt", "a");

    char input[64] = {'p', ' ',};
    for(int i = 2; i < 64; i++){
        input[i] = name[i - 2];
        if(name[i - 2] == '\0'){
            input[i] = '\n';
            break;
        }
    }
    
    fputs(input, file);

    Playlist playlist;
    int id;
    for(int i = 0; i < 256; i++){
        if(playlists[i].ID == -1){
            id = i;
            break;
        }
    }

    for(int i = 0; i < 64; i++){
        playlist.name[i] = name[i];
        if(name[i] == '\0') break;
    }
    playlist.ID = id;
    playlist.songCount = 0;
    playlists[id] = playlist;

    (*count)++;
}
