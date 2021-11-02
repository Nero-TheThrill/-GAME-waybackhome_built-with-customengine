/*
*  File Name : PastBulletController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Controll Past Bullets. This will be inherited from bullet controller
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "BulletController.h"

namespace BLUE
{
    class PoisonBulletController : public BulletController
    {
    public:
        void Init(Object obj) override;
        void Init(Object obj, glm::vec2 direction);
    };
    extern PoisonBulletController* POISONBULLET_CONTROLLER;
}
