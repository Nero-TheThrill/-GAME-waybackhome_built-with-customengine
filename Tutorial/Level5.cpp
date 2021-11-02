/*
*  File Name : Level5.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 5.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include"Level5.h"


namespace BLUE
{
	void Level5::Init()
	{
		level.InitLEVEL("JSONFILES/Level5.txt",LV_5);
		level.level_data = 6;
                for (const auto & object : OBJECT_CONTROLLER->objects)
                {
                    if (object->GetName() == "Portal")
                    {
                        glm::vec3 pos = object->transform->GetTranslation();
                        GRAPHICS->GetCamera()->SetPosition({ pos.x, pos.y });
                    }
                }
	}

	void Level5::Update()
	{
		level.UpdateLEVEL("JSONFILES/Level5.txt", LV_6);
	}

	void Level5::Close()
	{
		level.CloseLEVEL("JSONFILES/Level5.txt");
	}
}
