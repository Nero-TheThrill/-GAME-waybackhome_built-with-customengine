/*
*  File Name : ReplaySystem.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: replay functions

*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#pragma once
#include <utility>
#include <glm/glm.hpp>
#include <queue>
#include "BulletController.h"
#include "Camera.h"
#include "GhostController.h"
#include "MouseController.h"
#include "LerpSmoothing.h"

namespace BLUE
{
    enum InfoType
    {
        MOVING,
        INTERACT,
        MOUSERIGHTPRESSED,
        MOUSERIGHTUP,
        MOUSELEFTCLICK

    };
    struct ReplayInfo
    {
        glm::vec3 playerPos;
        glm::vec2 mousePos;
        glm::vec2 cameraPos;
        glm::vec2 lerpCamPos;
        float playerRotate;
        bool IsGunFuture;
    };

    class ReplaySystem
    {
    public:
        void storeInfo(InfoType infotype, ReplayInfo replayinfo);
        void replay();
        bool shouldRepeat();
        bool IsDone();
        void Init();
        void Close();
        void Clear();
    private:
        std::queue< std::pair<InfoType, ReplayInfo>> storage;
        bool IsGunFuture=true;
        //RemainBullet remain_bullet;
        Object* player;
        Transform* playertransform;
        Camera* camera;
        Object* hud;
        Object* text;
        GhostController ghost_;
        MouseController mousecontroller;
        bool CanPicking = false;
        LerpSmoothCamera lerp;
    };
    extern ReplaySystem* REPLAY_SYSTEM;
}
