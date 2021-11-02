/*
*  File Name : Level1.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Level 1.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include"Level1.h"

namespace BLUE
{
	void Level1::Init()
	{
		level.InitLEVEL("JSONFILES/level1.txt",LV_1);
		level.level_data = 2;
                for (const auto & object : OBJECT_CONTROLLER->objects)
                {
                    if (object->GetName() == "Portal")
                    {
                        glm::vec3 pos = object->transform->GetTranslation();
                        GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
                    }
                }

	}

	void Level1::Update()
	{
		level.UpdateLEVEL("JSONFILES/level1.txt", LV_2);
	}

	void Level1::Close()
	{
		level.CloseLEVEL("JSONFILES/level1.txt");
	}


}
