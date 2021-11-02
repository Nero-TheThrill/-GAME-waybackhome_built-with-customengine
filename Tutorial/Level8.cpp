/*
*  File Name : Level8.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 8.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include"Level8.h"


namespace BLUE
{
	void Level8::Init()
	{
		level.InitLEVEL("JSONFILES/Level8.txt", LV_8);
		level.level_data = 9;
		for (const auto & object : OBJECT_CONTROLLER->objects)
		{
			if (object->GetName() == "Portal")
			{
				glm::vec3 pos = object->transform->GetTranslation();
				GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
			}
		}
	}

	void Level8::Update()
	{
		level.UpdateLEVEL("JSONFILES/Level8.txt", LV_9);
	}

	void Level8::Close()
	{
		level.CloseLEVEL("JSONFILES/Level8.txt");
	}
}
