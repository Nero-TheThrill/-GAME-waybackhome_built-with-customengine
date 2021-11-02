/*
*  File Name : Level11.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 11.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include"Level11.h"


namespace BLUE
{
	void Level11::Init()
	{
		level.InitLEVEL("JSONFILES/Level11.txt", LV_11);
		level.level_data = 12;
		for (const auto & object : OBJECT_CONTROLLER->objects)
		{
			if (object->GetName() == "Portal")
			{
				glm::vec3 pos = object->transform->GetTranslation();
				GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
			}
		}
	}

	void Level11::Update()
	{
		level.UpdateLEVEL("JSONFILES/Level11.txt", LV_CLEAR);
	}

	void Level11::Close()
	{
		level.CloseLEVEL("JSONFILES/Level11.txt");
	}
}
