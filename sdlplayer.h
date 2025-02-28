//
// C++ Interface: sdlplayer
//
// Description:
//
//
// Author: FThauer FHammer <webmaster@pokerth.net>, (C) 2007
//
//
//
#ifndef SDLPLAYER_H
#define SDLPLAYER_H

#include <QObject>

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <string>

class SDLPlayer : public QObject
{
    Q_OBJECT
public:
    explicit SDLPlayer();
    ~SDLPlayer();

    void initAudio();
    void playSound(std::string);
    void audioDone();
    void closeAudio();

private:

    int         audio_rate;
    Uint16      audio_format;
    int         audio_channels;
    int         audio_buffers;
    Mix_Chunk   *sound;
    Uint8       *soundData;
    int         currentChannel;

    bool        audioEnabled;
};

#endif // SDLPLAYER_H
