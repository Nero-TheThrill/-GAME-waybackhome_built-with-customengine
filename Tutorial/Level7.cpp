/*
*  File Name : Level7.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 7.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include"Level7.h"


namespace BLUE
{
	void Level7::Init()
	{
		level.InitLEVEL("JSONFILES/Level7.txt", LV_7);
		level.level_data = 8;
		for (const auto & object : OBJECT_CONTROLLER->objects)
		{
			if (object->GetName() == "Portal")
			{
				glm::vec3 pos = object->transform->GetTranslation();
				GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
			}
		}
	}

	void Level7::Update()
	{
		level.UpdateLEVEL("JSONFILES/Level7.txt", LV_8);
	}

	void Level7::Close()
	{
		level.CloseLEVEL("JSONFILES/Level7.txt");
	}
}
