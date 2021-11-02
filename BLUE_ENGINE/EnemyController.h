/*
*  File Name : EnemyController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Control enemies. This is for just engine proof. Deprecated
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "ObjectFactory.h"
#include "Graphics.h"
#include "Object.h"
#include "JSONREADER.h"
#include "JSONWRITER.h"

namespace BLUE
{
    class EnemyController
    {
    public:

        EnemyController();

        void Init(float x, float y, float z);
        void update();
        void check_collision_with(Object* obj);
        void EnemyControllerReset();

        int mouseX, mouseY;
        std::vector<float> angle;
        std::vector<Object*> enemy;
        std::vector<Transform*> enemy_transform;
        std::vector<Sprite*> enemy_sprite;
        std::vector<Collision*> enemy_collision;
        std::vector<Rectangle*> enemy_rectangle;
        std::vector<Line2D*> enemy_line;
        rapidjson::JSONwriter* JSONWRITER;
        unsigned enemycount = 0;
    };
    extern EnemyController* ENEMY_CONTROLLER;
}
