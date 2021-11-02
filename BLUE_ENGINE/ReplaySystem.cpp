/*
*  File Name : ReplaySystem.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: replay functions

*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include "ReplaySystem.h"
#include <iostream>
#include "PlayerController.h"
#include "Archiver.h"
#include "FutureBulletController.h"
#include "PastBulletController.h"
#include "SmokeEffects.h"

namespace BLUE
{
    extern ReplaySystem* REPLAY_SYSTEM = nullptr;

    void ReplaySystem::storeInfo(InfoType infotype, ReplayInfo replayinfo)
    {
        storage.push(std::make_pair(infotype, replayinfo));
    }

    void ReplaySystem::replay()
    {
        while (shouldRepeat()) {};
    }

    bool ReplaySystem::shouldRepeat()
    {
        lerp.Update();

        std::pair<InfoType, ReplayInfo> info = storage.front();




        FUTUREBULLET_CONTROLLER->Update();
        PASTBULLET_CONTROLLER->Update();
        ((Rectangle*)player->GetComponent(ComponentType_RECTANGLE))->update();
        SMOKE_EFFECT->Update();
        ghost_.update();
        if(IsGunFuture!=info.second.IsGunFuture)
        {
            AUDIO_MANAGER->PlaySound("changebullet");
            if(!IsGunFuture)
            {
                (text->sprite)->SetTexture(T(Picture::Bullet_Future));
            }
            else
            {
                (text->sprite)->SetTexture(T(Picture::Bullet_Past));
            }
            IsGunFuture = !IsGunFuture;
        }

        IsGunFuture = info.second.IsGunFuture;

        int mX = static_cast<int>(info.second.mousePos.x);
        int mY = static_cast<int>(-info.second.mousePos.y);
        int fixedmX = mX - static_cast<int>(info.second.cameraPos.x);
        int fixedmY = -mY + static_cast<int>(info.second.cameraPos.y);
        switch (info.first)
        {
        case MOVING:
            PLAYER_CONTROLLER->SetPosition(info.second.playerPos);
            PLAYER_CONTROLLER->SetRotate(info.second.playerRotate);
            storage.pop();
            return false;
        case INTERACT:
            PLAYER_CONTROLLER->interaction();
            storage.pop();
            return true;
        case MOUSERIGHTPRESSED:

           if (fixedmX >= Inventory::location.x - Inventory::scale.x / 2 && fixedmX <= Inventory::location.x + Inventory::scale.x / 2 && fixedmY >= -Inventory::location.y - Inventory::scale.y / 2 && fixedmY <= -Inventory::location.y + Inventory::scale.y / 2)
                CanPicking = true;
            std::cout << mX-info.second.cameraPos.x << " " << mY-info.second.cameraPos.y << std::endl;
            if (CanPicking)
            {

                for (unsigned int i = 0; i < OBJECT_CONTROLLER->controllers.size(); ++i)
                {

                    if (OBJECT_CONTROLLER->controllers.at(i)->isInInventory)
                    {
                        (OBJECT_CONTROLLER->objects.at(i)->transform)->SetTranslation({ mX, mY, 10 });
                        (OBJECT_CONTROLLER->objects.at(i)->sprite)->isHud = false;
                    }
                }
            }
            storage.pop();
            return true;
        case MOUSERIGHTUP:
            if (CanPicking)
            {
                BaseController* tmpbasecontroller = nullptr;
                size_t previous_size = OBJECT_CONTROLLER->controllers.size();
                for (unsigned int i = 0; i < previous_size; ++i)
                {

                    if (OBJECT_CONTROLLER->controllers.at(i)->isInInventory)
                    {
                        tmpbasecontroller = OBJECT_CONTROLLER->controllers.at(i);
                        OBJECT_CONTROLLER->controllers.at(i)->Interact(ControllerType_NULL);
                        break;
                    }
                }
                for (unsigned int i = 0; i<previous_size; ++i)
                {
                    if (tmpbasecontroller == OBJECT_CONTROLLER->controllers.at(i) && tmpbasecontroller != nullptr)
                    {
                        AUDIO_MANAGER->PlaySound("pick");
                        (OBJECT_CONTROLLER->objects.at(i)->transform)->SetTranslation(
                            { info.second.cameraPos.x + info.second.mousePos.x, info.second.cameraPos.y - info.second.mousePos.y, (OBJECT_CONTROLLER->objects.at(i)->transform)->GetTranslation().z });
                        const glm::vec2 prev_scale = { OBJECT_CONTROLLER->controllers.at(i)->previouswidth, OBJECT_CONTROLLER->controllers.at(i)->previousheight };
                        (OBJECT_CONTROLLER->objects.at(i)->transform)->SetScale(prev_scale);
                        OBJECT_CONTROLLER->controllers.at(i)->isInInventory = false;
                    }
                }
                PLAYER_CONTROLLER->SetInventoryState(true);
                CanPicking = false;
            }
            storage.pop();
            return true;
        /*case MOUSELEFTCLICK:
            if (remain_bullet.used_bullet_num < remain_bullet.bullet_limit)
            {
                AUDIO_MANAGER->PlaySound("shootgun");
                remain_bullet.SetBulletNum(++remain_bullet.used_bullet_num);

                if (IsGunFuture)
                    FUTUREBULLET_CONTROLLER->ReplayInit(*(PLAYER_CONTROLLER->GetObject()),info.second.mousePos,info.second.playerPos, info.second.cameraPos);
                else
                    PASTBULLET_CONTROLLER->ReplayInit(*(PLAYER_CONTROLLER->GetObject()), info.second.mousePos, info.second.playerPos, info.second.cameraPos);
            }
            else
            {
                AUDIO_MANAGER->PlaySound("cannotshoot");
            }
            storage.pop();
            return true;*/
        default:

            storage.pop();
            return false;
        }
    }

    bool ReplaySystem::IsDone()
    {
        return storage.empty();
    }

    void ReplaySystem::Init()
    {
        player = PLAYER_CONTROLLER->Spawn();
        PLAYER_CONTROLLER->isClearTheGame = false;
        playertransform = PLAYER_CONTROLLER->GetTransform();
        camera = GRAPHICS->GetCamera();
      //  remain_bullet.Init();
        text = OBJECT_FACTORY->CreateEmptyObject();
        text->SetName("Text");
        text->AddComponent(new Transform());
        text->AddComponent(new Sprite());
        text->Init();
        (text->transform)->SetScale({ 80, 80 });
        (text->transform)->SetTranslation({ -600, 320, 900 });
        if (IsGunFuture)
            (text->sprite)->SetTexture(T(Picture::Bullet_Future));
        else
            (text->sprite)->SetTexture(T(Picture::Bullet_Past));
        (text->sprite)->isHud = true;
      
        hud = OBJECT_FACTORY->CreateEmptyObject();
        hud->SetName("HUD");
        hud->AddComponent(new Transform());
        hud->AddComponent(new Sprite());
        hud->Init();
        (hud->transform)->SetScale({ 1280, 720 });
        (hud->transform)->SetTranslation({ 0, 0,800 });
        (hud->sprite)->SetTexture(T(Picture::Hud));
        (hud->sprite)->isHud = true;
        GRAPHICS->AddSprite(hud->sprite);
        ghost_.Spawn(0, 0, 0);
        lerp.Init(camera, player->transform);
    }

    void ReplaySystem::Close()
    {
        AUDIO_MANAGER->StopSound();
        OBJECT_CONTROLLER->Reset("noTXT");
        FUTUREBULLET_CONTROLLER->Reset();
        PASTBULLET_CONTROLLER->Reset();
        GRAPHICS->DeleteAll();
        OBJECT_FACTORY->DestroyAllObjects();
    }

    void ReplaySystem::Clear()
    {
        while (!storage.empty())
        {
            storage.pop();
        }

    }
}
