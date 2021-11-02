/*
*  File Name : Audio.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: This is for playing sound in game engine
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"Audio.h"
#include <iostream>

Audio* AUDIO_MANAGER = nullptr;
Audio::Audio()
{
    std::cout << "AUDIO INIT" << std::endl;
    FMOD::System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, nullptr);
    SoundStorage.clear();
    Soundchannel.clear();
    Soundvolume = 1.0f;

}

void Audio::Init()
{
    AUDIO_MANAGER->CreateSound("Sound/BGM.wav", "BGM", true, false);
    AUDIO_MANAGER->CreateSound("Sound/shoot_gun.wav", "shootgun", false, false);
    AUDIO_MANAGER->CreateSound("Sound/cannotshoot.wav", "cannotshoot", false, false);
    AUDIO_MANAGER->CreateSound("Sound/changebullet.wav", "changebullet", false, false);
    AUDIO_MANAGER->CreateSound("Sound/click_mouse.wav", "click_mouse", false, false);
    AUDIO_MANAGER->CreateSound("Sound/mainmenu_bgm.wav", "Mainmenu_bgm", true, false);
    AUDIO_MANAGER->CreateSound("Sound/winstate.wav", "winstate", false, false);
    AUDIO_MANAGER->CreateSound("Sound/ChangeItemState.wav", "changeitem", false, false);
    AUDIO_MANAGER->CreateSound("Sound/Cuttree.wav", "cuttree", false, false);
    AUDIO_MANAGER->CreateSound("Sound/Loselevel.wav", "loselevel", false, false);
    AUDIO_MANAGER->CreateSound("Sound/OpenBox.wav", "openbox", false, false);
    AUDIO_MANAGER->CreateSound("Sound/Pickup&down.wav", "pick", false, false);
    AUDIO_MANAGER->CreateSound("Sound/Putlog.wav", "putlog", false, false);
	AUDIO_MANAGER->CreateSound("Sound/door.wav", "door", false, false);
	AUDIO_MANAGER->CreateSound("Sound/dead.wav", "dead", false, false);
	AUDIO_MANAGER->CreateSound("Sound/fire.wav", "fire", false, false);
	AUDIO_MANAGER->CreateSound("Sound/level_change.wav", "level_change", false, false);
	AUDIO_MANAGER->CreateSound("Sound/level_end.wav", "level_end", false, false);
	AUDIO_MANAGER->CreateSound("Sound/destroy_spike.wav", "destroy_spike", false, false);

}

void Audio::CreateSound(const char* path, std::string name, bool loop, bool startpause)
{
    FMOD::Sound* sound;
    FMOD::Channel* channel=nullptr;
    std::pair<std::string, FMOD::Channel*> channeldata(name,channel);
    if (loop)
        system->createSound(path, FMOD_LOOP_NORMAL | FMOD_DEFAULT, nullptr, &sound);
    else
        system->createSound(path, FMOD_LOOP_OFF | FMOD_DEFAULT, nullptr, &sound);
    std::pair<FMOD::Sound*, bool> subdata(sound, startpause);
    std::pair<std::string, std::pair<FMOD::Sound*, bool>> data(name, subdata);
    SoundStorage.push_back(data);
    Soundchannel.push_back(channeldata);
}



void Audio::StopSound()
{
    for (auto sound : Soundchannel)
    {
        sound.second->stop();
    }
}


void Audio::PauseSound()
{

    bool getbool;
    for (auto sound : Soundchannel)
    {
        sound.second->getPaused(&getbool);
        if (getbool)
            sound.second->setPaused(false);
        else
            sound.second->setPaused(true);
    }
}



void Audio::Update()
{
    system->update();
}

void Audio::volumeUp()
{
    if(Soundvolume<1.0f)
    {
        Soundvolume += 0.1f;
    }
    for (auto sound : Soundchannel)
    {
        sound.second->setVolume(Soundvolume);
    }
}

void Audio::volumeDown()
{
    if (Soundvolume > 0.0f)
    {
        Soundvolume -= 0.1f;
    }
    for (auto sound : Soundchannel)
    {
        sound.second->setVolume(Soundvolume);
    }
}

void Audio::ChangeSound(std::string stopname,std::string playname)
{
    int count = 0;
    for (auto sound : SoundStorage)
    {
        if (sound.first == stopname)
        {
            Soundchannel.at(count).second->stop();
        }
        if(sound.first==playname)
        {
            system->playSound(sound.second.first, nullptr, sound.second.second, &(Soundchannel.at(count).second));
        }
        count++;
    }
}


Audio::~Audio()
{
    for (auto sound : SoundStorage)
    {
        sound.second.first->release();
    }
    system->close();
    system->release();
}


void Audio::PlaySound(std::string name)
{

    int count = 0;
    for (auto sound : SoundStorage)
    {
        if (sound.first == name)
        {
            system->playSound(sound.second.first, nullptr, sound.second.second, &(Soundchannel.at(count).second));
        }
        count++;
    }
    for (auto sound : Soundchannel)
    {
        sound.second->setVolume(Soundvolume);
    }
}


