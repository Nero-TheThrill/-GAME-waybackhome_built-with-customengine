/*
*  File Name : TutoLevel1.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Level 1.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"TutoLevel1.h"

namespace BLUE
{
	void TutoLevel1::Init()
	{
	    level.InitLEVEL("JSONFILES/tutorial1.txt",LV_TUTORIAL1);
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

	void TutoLevel1::Update()
	{
		level.UpdateLEVEL("JSONFILES/tutorial1.txt", LV_TUTORIAL2);
	}

    void TutoLevel1::Close()
    {
        level.CloseLEVEL("JSONFILES/tutorial1.txt");
		level.canUseGun = true;
    }
}
