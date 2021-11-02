/*
*  File Name : Level4.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 4.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include"Level4.h"


namespace BLUE
{
	void Level4::Init()
	{
		level.InitLEVEL("JSONFILES/Level4.txt",LV_4);
		level.level_data = 5;
                for (const auto & object : OBJECT_CONTROLLER->objects)
                {
                    if (object->GetName() == "Portal")
                    {
                        glm::vec3 pos = object->transform->GetTranslation();
                        GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
                    }
                }
	}

	void Level4::Update()
	{
		level.UpdateLEVEL("JSONFILES/Level4.txt", LV_5);
	}

	void Level4::Close()
	{
		level.CloseLEVEL("JSONFILES/Level4.txt");
	}
}
