/*
*  File Name : FutureBulletController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Controll Future Bullets. This will be inherited from bullet controller 
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "BulletController.h"

namespace BLUE
{
    class FutureBulletController : public BulletController
    {
    public:
        void Init(Object obj) override;
        void ReplayInit(Object obj, glm::vec2 mousePos, glm::vec3 playerPos, glm::vec2 cameraPos);
    };
    extern FutureBulletController* FUTUREBULLET_CONTROLLER;
}
