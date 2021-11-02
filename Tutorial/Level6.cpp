/*
*  File Name : Level6.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 6.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include"Level6.h"


namespace BLUE
{
	void Level6::Init()
	{
		level.InitLEVEL("JSONFILES/Level6.txt",LV_6);
		level.level_data = 7;
                for (const auto & object : OBJECT_CONTROLLER->objects)
                {
                    if (object->GetName() == "Portal")
                    {
                        glm::vec3 pos = object->transform->GetTranslation();
                        GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
                    }
                }
	}

	void Level6::Update()
	{
		level.UpdateLEVEL("JSONFILES/Level6.txt", LV_7);
	}

	void Level6::Close()
	{
		level.CloseLEVEL("JSONFILES/Level6.txt");
	}
}
