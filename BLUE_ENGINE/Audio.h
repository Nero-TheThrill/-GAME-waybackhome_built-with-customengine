/*
*  File Name : Audio.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: This is for playing sound in game engine
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#pragma once
#include "fmod.hpp"
#include <string>
#include <vector>

struct AudioINFO
{
    std::string path;
    std::string name;
    bool loop;
    bool startpause;
};


class Audio
{
public:
    Audio();

    void Init();

    void CreateSound(const char* path, std::string name, bool loop,bool startpause);

    void PlaySound(std::string name);
 
    void StopSound();

    void PauseSound();

    void Update();
    void volumeUp();
    void volumeDown();

    void ChangeSound(std::string stopname, std::string playname);

    ~Audio();
private:

    FMOD::System* system;
    std::vector<std::pair<std::string, std::pair<FMOD::Sound*,bool>>>SoundStorage;
    std::vector<std::pair<std::string, FMOD::Channel*>> Soundchannel;
    float Soundvolume;
}; 
extern Audio* AUDIO_MANAGER;