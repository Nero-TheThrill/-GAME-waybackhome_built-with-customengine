/*
*  File Name : PoisonPlantManager.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: manage poison plants.

*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <vector>
#include "PoisonplantController.h"

namespace BLUE
{
    class PoisonPlantManager
    {
    public:
        void Update();
        void AddPoisionPlant(PoisonplantController* ppcontroller, glm::vec2 direction);
        void Shoot();
        void Reset();
        PoisonPlantManager();
        void Delete(Object* obj);

    private:
        std::vector<PoisonplantController*> ppvec;
        std::vector<glm::vec2>pos;
        float dt = 0;
    };
    extern PoisonPlantManager* POISONPLANT_MANAGER;
}
