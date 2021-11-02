/*
*  File Name : ObjectController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Controll Objects. Check all collision with player.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once

#include <vector>
#include"Object.h"
#include "JSONWRITER.h"
#include "ControllerType.h"
#include "Helper.h"

namespace BLUE
{
    class BaseController;

    class ObjectController
    {
    public:
        ObjectController();
        void AddObject(Object* obj);
        void DeleteObject(int num);
        Object* GetObject(int num);
        void AddController(BaseController* controller);
        void DeleteController(BaseController* controller);

        int GetSize();
        std::string GetName(int num);
        BaseController * GetCollideWith(Object * obj, ControllerType ctype = ControllerType_ANYTHING);
        std::vector<BaseController*> GetVecCollideWith(Object* obj);
        void UpdateBullet(std::vector<Object *>& bulletvec);
        void Reset(std::string path);

        void Help();

        void HelpDone();


        std::vector<Color> colors;
        std::vector<Object*> objects;
        std::vector<BaseController*> controllers;
        rapidjson::JSONwriter* JSONWRITER;
    };
    extern ObjectController* OBJECT_CONTROLLER;
}
