/*
*  File Name : TutoLevel4.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Level 4.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"TutoLevel4.h"


namespace BLUE
{
    void TutoLevel4::Init()
    {
        level.InitLEVEL("JSONFILES/tutorial4.txt", LV_TUTORIAL4);
		level.level_data = 1;
        for (const auto & object : OBJECT_CONTROLLER->objects)
        {
            if (object->GetName() == "Portal")
            {
                glm::vec3 pos = object->transform->GetTranslation();
                GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
            }
        }
    }

    void TutoLevel4::Update()
    {
        level.UpdateLEVEL("JSONFILES/tutorial4.txt", LV_1);
    }

    void TutoLevel4::Close()
    {
        level.CloseLEVEL("JSONFILES/tutorial4.txt");
    }
}
