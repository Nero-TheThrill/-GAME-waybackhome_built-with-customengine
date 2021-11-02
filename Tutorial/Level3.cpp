/*
*  File Name : Level3.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 3.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include"Level3.h"


namespace BLUE
{
    void Level3::Init()
    {
        level.InitLEVEL("JSONFILES/level3.txt",LV_3);
		level.level_data = 4;
        for (const auto & object : OBJECT_CONTROLLER->objects)
        {
            if (object->GetName() == "Portal")
            {
                glm::vec3 pos = object->transform->GetTranslation();
                GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
            }
        }
    }

    void Level3::Update()
    {
        level.UpdateLEVEL("JSONFILES/level3.txt", LV_4);
    }

    void Level3::Close()
    {
        level.CloseLEVEL("JSONFILES/level3.txt");
    }
}
