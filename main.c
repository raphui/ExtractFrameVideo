#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vlc/vlc.h>

#include "types.h"

int main( int argc , char *argv[] )
{
    int ms = 0;
    libvlc_instance_t *vlcInstance = NULL;
    libvlc_media_t *vlcMedia = NULL;
    libvlc_media_player_t *vlcMediaPlayer = NULL;

    const char * const vlcArgs[] = { "--rate=1 " ,
                                    "--video-filter=scene" ,
                                    "--vout=dummy" ,
                                    "--scene-format=jpeg" ,
                                    "--scene-ratio=1" ,
                                    "--scene-prefix=img" ,
                                    "--scene-path=./images/"};

    if( argc < 2 )
    {
        printf("Usage: ./tool ms_time\n");
        return PC_ERROR;
    }

    ms = strtol( argv[2] , NULL , 10 );

    printf("Getting frame at %d ms.\n" , ms );

    vlcInstance = libvlc_new( sizeof( vlcArgs ) / sizeof( vlcArgs[0] ) , vlcArgs );

//    vlcInstance = libvlc_new( 0 , NULL );

    if( vlcInstance == NULL )
    {
        printf("Cannot get vlc instance.\n");
        return PC_ERROR;
    }

    vlcMedia = libvlc_media_new_path( vlcInstance , argv[1] );

    if( vlcMedia == NULL )
    {
        printf("Cannot get the media.\n");
        return PC_ERROR;
    }

    vlcMediaPlayer = libvlc_media_player_new_from_media( vlcMedia );

    if( vlcMediaPlayer == NULL )
    {
        printf("Cannot get the media player.\n");
        return PC_ERROR;
    }

    printf("Vlc has been init.\n");
    printf("Let's play the media.\n");

    libvlc_media_player_play( vlcMediaPlayer );

    libvlc_media_player_set_time( vlcMediaPlayer , ms );

    do
    {
        //nothing
    } while( libvlc_media_player_get_time( vlcMediaPlayer ) <= ms );

    //Removing useless files, don't know atm why they are generated

    remove("images/img00001.jpeg");
    remove("images/img00001.jpeg.swp");
    remove("images/img00002.jpeg.swp");
    remove("images/img00003.jpeg");
    remove("images/img00003.jpeg.swp");

    printf("Done\n");

    printf("\n");
    return 0;
}
