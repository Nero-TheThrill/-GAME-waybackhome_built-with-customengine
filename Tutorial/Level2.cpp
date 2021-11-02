/*
*  File Name : Level2.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 2.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include"Level2.h"


namespace BLUE
{
	void Level2::Init()
	{
		level.InitLEVEL("JSONFILES/level2.txt",LV_2);
		level.level_data = 3;
                for (const auto & object : OBJECT_CONTROLLER->objects)
                {
                    if (object->GetName() == "Portal")
                    {
                        glm::vec3 pos = object->transform->GetTranslation();
                        GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
                    }
                }
	}

	void Level2::Update()
	{
		level.UpdateLEVEL("JSONFILES/level2.txt", LV_3);
	}

	void Level2::Close()
	{
		level.CloseLEVEL("JSONFILES/level2.txt");
	}
}
