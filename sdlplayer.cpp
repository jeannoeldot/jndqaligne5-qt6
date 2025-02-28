//
// C++ Implementation: sdlplayer
//
// Description:
//
//
// Author: FThauer FHammer <webmaster@pokerth.net>, (C) 2007
//
//
//
#include <QFile>
#include <QIODevice>
#include <QDataStream>

#include "sdlplayer.h"

#include <iostream>

using namespace std;

SDLPlayer::SDLPlayer()
: soundData(NULL), currentChannel(0) , audioEnabled(0)
{
    SDL_Init(SDL_INIT_AUDIO);
    initAudio();
}


SDLPlayer::~SDLPlayer()
{
    closeAudio();
    SDL_Quit();
}

void SDLPlayer::initAudio() {

    if (!audioEnabled)
    {
        audio_rate = 44100;
        audio_format = AUDIO_S16; /* 16-bit stereo */
        audio_channels = 2;
        audio_buffers = 4096;
        sound = NULL;

        if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) == 0) {
            Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
            audioEnabled = 1;
        }
    }
}

void SDLPlayer::playSound(string audioString) {

    if(audioEnabled ) {

        QFile myFile(":/sounds/"+QString::fromStdString(audioString)+".wav");

        if(myFile.open(QIODevice::ReadOnly)) {

            audioDone();

            QDataStream in(&myFile);
            soundData = new Uint8[(int)myFile.size()];
            in.readRawData( (char*)soundData, (int)myFile.size() );

            sound = Mix_QuickLoad_WAV(soundData);


            /// set channel 0 to settings volume
            Mix_Volume(0, 10*10);

            currentChannel = Mix_PlayChannel(-1, sound,0);
        }
    }
}

void SDLPlayer::audioDone() {

    if(audioEnabled) {
        Mix_HaltChannel(currentChannel);
        Mix_FreeChunk(sound);
        sound = NULL;
        delete[] soundData;
        soundData = NULL;
    }
}

void SDLPlayer::closeAudio() {

    if(audioEnabled) {
        audioDone();
        Mix_CloseAudio();
        audioEnabled = false;
    }
}
