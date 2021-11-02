/*
*  File Name : ObjectSpawner.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Easy to make objects.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"ObjectSpawner.h"
#include "ObjectFactory.h"

namespace BLUE
{
    extern ObjectSpawner* OBJECT_SPAWNER = nullptr;
    ObjectSpawner::ObjectSpawner()
    {
        assert(OBJECT_SPAWNER == nullptr && "ObjecctSpawner is already created");
        OBJECT_SPAWNER = this;
        transform = nullptr;
        mesh = nullptr;
        collision = nullptr;

    }

    ObjectSpawner::~ObjectSpawner()
    {
        delete transform;
        delete mesh;
        delete collision;
    }

    Object* ObjectSpawner::SpawnDefaultObject(bool addtransform, bool addcollision, bool addmesh)
    {
        Object* obj = OBJECT_FACTORY->CreateEmptyObject();
        if (addtransform)
        {
            obj->AddComponent(new Transform());
        }
        if (addmesh)
        {
            obj->AddComponent(new Sprite());
        }
        if (addcollision)
        {

            obj->AddComponent(new Collision());
        }
        return obj;
    }
}
