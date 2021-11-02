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
    class PastBulletController : public BulletController
    {
    public:
        void Init(Object obj) override;
        void ReplayInit(Object obj, glm::vec2 mousePos, glm::vec3 playerPos, glm::vec2 cameraPos);
    };
    extern PastBulletController* PASTBULLET_CONTROLLER;
}
