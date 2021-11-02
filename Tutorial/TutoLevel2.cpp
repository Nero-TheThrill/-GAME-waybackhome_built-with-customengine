/*
*  File Name : TutoLevel2.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Level 2.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"TutoLevel2.h"


namespace BLUE
{
    void TutoLevel2::Init()
    {
        level.InitLEVEL("JSONFILES/tutorial2.txt",LV_TUTORIAL2);

        for (const auto & object : OBJECT_CONTROLLER->objects)
        {
            if (object->GetName() == "Portal")
            {
                glm::vec3 pos = object->transform->GetTranslation();
                GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
            }
        }
		level.canUseGun = false;
    }

    void TutoLevel2::Update()
    {
        level.UpdateLEVEL("JSONFILES/tutorial2.txt", LV_TUTORIAL3);
    }

    void TutoLevel2::Close()
    {
        level.CloseLEVEL("JSONFILES/tutorial2.txt");
		level.canUseGun = true;
    }
}
