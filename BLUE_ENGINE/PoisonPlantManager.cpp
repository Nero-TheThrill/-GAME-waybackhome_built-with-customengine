/*
*  File Name : PoisonPlantManager.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: manage poison plants.

*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include "PoisonPlantManager.h"
#include <iostream>
#include "PoisonBulletController.h"

namespace BLUE
{
    extern PoisonPlantManager* POISONPLANT_MANAGER = nullptr;


    void PoisonPlantManager::Update()
    {
        POISONBULLET_CONTROLLER->Update();
        dt += 1;
        if (dt >= 100)
        {
            Shoot();
            dt = 0;
        }
    }
    void PoisonPlantManager::AddPoisionPlant(PoisonplantController* ppcontroller,glm::vec2 direction)
    {
        ppvec.push_back(ppcontroller);
        pos.push_back(direction);
    }

    void PoisonPlantManager::Shoot()
    {
        for (int i = 0; i < ppvec.size(); i++)
        {
           if( ppvec.at(i)->GetCurrentState()==PRESENT)
            ppvec.at(i)->ShootPoision(pos.at(i));
        }
    }

    void PoisonPlantManager::Reset()
    {
        ppvec.clear();
        pos.clear();
        dt = 0;
    }

    PoisonPlantManager::PoisonPlantManager()
    {
        ppvec.clear();
        pos.clear();
        dt = 0;
    }

    void PoisonPlantManager::Delete(Object* obj)
    {
        for(int i=0;i<ppvec.size();i++)
        {
            if (ppvec.at(i)->GetObject() == obj)
            {
                ppvec.erase(ppvec.begin()+i);
                pos.erase(pos.begin() + i);
                return;
            }
        }
    }
}
