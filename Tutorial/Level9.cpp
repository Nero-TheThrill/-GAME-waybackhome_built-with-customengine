/*
*  File Name : Level9.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 9.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include"Level9.h"


namespace BLUE
{
	void Level9::Init()
	{
		level.InitLEVEL("JSONFILES/Level9.txt", LV_9);
		level.level_data = 10;
		for (const auto & object : OBJECT_CONTROLLER->objects)
		{
			if (object->GetName() == "Portal")
			{
				glm::vec3 pos = object->transform->GetTranslation();
				GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
			}
		}
	}

	void Level9::Update()
	{
		level.UpdateLEVEL("JSONFILES/Level9.txt", LV_10);
	}

	void Level9::Close()
	{
		level.CloseLEVEL("JSONFILES/Level9.txt");
	}
}
