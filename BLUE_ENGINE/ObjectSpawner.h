/*
*  File Name : ObjectSpawner.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Easy to make objects.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Object.h"

namespace BLUE
{
    class ObjectSpawner
    {
    private:
        Transform * transform;
        Collision* collision;
        Mesh* mesh;
    public:
        ObjectSpawner();
        ~ObjectSpawner();
        Object* SpawnDefaultObject(bool addtransform = false, bool addcollision = false, bool addmesh = false);
    };
    extern ObjectSpawner* OBJECT_SPAWNER;

}