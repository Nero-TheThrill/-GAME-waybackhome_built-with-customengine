/*
*  File Name : Level10.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 10.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include"Level10.h"


namespace BLUE
{
	void Level10::Init()
	{
		level.InitLEVEL("JSONFILES/Level10.txt", LV_10);
		level.level_data = 11;
		for (const auto & object : OBJECT_CONTROLLER->objects)
		{
			if (object->GetName() == "Portal")
			{
				glm::vec3 pos = object->transform->GetTranslation();
				GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
			}
		}
	}

	void Level10::Update()
	{
		level.UpdateLEVEL("JSONFILES/Level10.txt", LV_11);
	}

	void Level10::Close()
	{
		level.CloseLEVEL("JSONFILES/Level10.txt");
	}
}
