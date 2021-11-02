/*
*  File Name : Archiver.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Make easy to load/save objects.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Object.h"
#include "EnemyController.h"
#include "TreeController.h"
#include "SeedController.h"
#include "ObjectController.h"
#include <fmod.hpp>
#include "Audio.h"

namespace BLUE
{
    template <typename Archiver>
    Archiver& operator&(Archiver& ar, Object*& obj)
    {
        ar.StartObject();
        ar.Member("ObjectName") & obj->GetName();
        ar.Member("ObjectTranslationX") & ((Transform*)obj->GetComponent(ComponentType_TRANSFORM))->GetTranslation().x;
        ar.Member("ObjectTranslationY") & ((Transform*)obj->GetComponent(ComponentType_TRANSFORM))->GetTranslation().y;
        ar.Member("ObjectTranslationZ") & ((Transform*)obj->GetComponent(ComponentType_TRANSFORM))->GetTranslation().z;
        for(int i = 0;i< OBJECT_CONTROLLER->GetSize();i++)
        {
            if (OBJECT_CONTROLLER->objects[i] == obj)
            {
                int curstate = static_cast<int>(OBJECT_CONTROLLER->controllers[i]->GetCurrentState());
                ar.Member("CurrentState") & curstate;
                break;
            }
        }
        if (obj->GetName() == "Wall")
        {
            ar.Member("ObjectScaleX") & ((Transform*)obj->GetComponent(ComponentType_TRANSFORM))->GetScale().x;
            ar.Member("ObjectScaleY") & ((Transform*)obj->GetComponent(ComponentType_TRANSFORM))->GetScale().y;
        }
		if (obj->GetName() == "Wall1")
		{
			ar.Member("ObjectScaleX") & ((Transform*)obj->GetComponent(ComponentType_TRANSFORM))->GetScale().x;
			ar.Member("ObjectScaleY") & ((Transform*)obj->GetComponent(ComponentType_TRANSFORM))->GetScale().y;
		}
		if (obj->GetName() == "Wall2")
		{
			ar.Member("ObjectScaleX") & ((Transform*)obj->GetComponent(ComponentType_TRANSFORM))->GetScale().x;
			ar.Member("ObjectScaleY") & ((Transform*)obj->GetComponent(ComponentType_TRANSFORM))->GetScale().y;
		}
		if (obj->GetName() == "Wall3")
		{
			ar.Member("ObjectScaleX") & ((Transform*)obj->GetComponent(ComponentType_TRANSFORM))->GetScale().x;
			ar.Member("ObjectScaleY") & ((Transform*)obj->GetComponent(ComponentType_TRANSFORM))->GetScale().y;
		}
        if(obj->GetName()=="PoisonPlant")
        {
            ar.Member("ObjectDirectionX") & (obj->direction.x);
            ar.Member("ObjectDirectionY") & (obj->direction.y);
        }
        if (obj->GetName() == "Door")
        {
            ar.Member("ObjectItemType") & static_cast<double>(obj->item_type);
        }
        return ar.EndObject();
    }
    template <typename Archiver>
    Archiver& WriteObject(Archiver* ar, std::vector<Object*> vec, unsigned objcount)
    {
        size_t arrsize = vec.size();
        ar->StartObject();
        ar->Member("ArrayName") & "ObjectArray";
        ar->Member("ArraySize") & objcount;
        ar->Member("Objects");
        ar->StartArray(&arrsize);
        for (auto obj : vec)
        {
            *ar & obj;
        }
        ar->EndArray();
        return ar->EndObject();
    }
    template <typename Archiver>
    Archiver& operator&(Archiver& ar, AudioINFO*& audioinfo)
    {
        ar.StartObject();
        ar.Member("AudioPath") & audioinfo->path;
        ar.Member("AudioName") & audioinfo->name;
        ar.Member("AudioLoop") & audioinfo->loop;
        ar.Member("AudioStartpause") & audioinfo->startpause;
        return ar.EndObject();
    }
    template <typename Archiver>
    Archiver& WriteAudio(Archiver* ar, std::vector<std::pair<std::string, std::pair<FMOD::Sound*, bool>>> vec, unsigned objcount)
    {
        size_t arrsize = vec.size();
        ar->StartObject();
        ar->Member("ArrayName") & "AudioArray";
        ar->Member("ArraySize") & objcount;
        ar->Member("Audio");
        ar->StartArray(&arrsize);
        for (auto obj : vec)
        {

            *ar & obj;

        }
        ar->EndArray();
        return ar->EndObject();
    }
    inline std::string ReadFromFile(const std::string& path)
    {
        std::string dat;
        char tmp[100];

        dat.clear();

        std::ifstream inStream(path);
        while (!inStream.eof())
        {
            inStream.getline(tmp, sizeof(tmp));
            dat += tmp;
            dat += "\n";
        }
        inStream.close();
        return dat;
    }
}
