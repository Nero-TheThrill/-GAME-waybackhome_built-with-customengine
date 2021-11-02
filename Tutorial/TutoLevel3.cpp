/*
*  File Name : TutoLevel.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Level 3.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"TutoLevel3.h"


namespace BLUE
{
    void TutoLevel3::Init()
    {
        level.InitLEVEL("JSONFILES/tutorial3.txt", LV_TUTORIAL3);
        for (const auto & object : OBJECT_CONTROLLER->objects)
        {
            if (object->GetName() == "Portal")
            {
                glm::vec3 pos = object->transform->GetTranslation();
                GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
            }
        }
    }

    void TutoLevel3::Update()
    {
        level.UpdateLEVEL("JSONFILES/tutorial3.txt", LV_TUTORIAL4);
    }

    void TutoLevel3::Close()
    {
        level.CloseLEVEL("JSONFILES/tutorial3.txt");
    }
}
