/*
*  File Name : PlayerController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Control player class. To make code simple.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include "CursorController.h"
#include <SDL.h>
#include "ObjectFactory.h"
#include"Graphics.h"
#include "TexturePath.h"
#include "PlayerController.h"

namespace BLUE
{
    extern CursorController* CURSOR_CONTROLLER = nullptr;
    CursorController::CursorController()
    {
        CURSOR_CONTROLLER = this;
        mx = 0;
        my = 0;
    }

    void CursorController::Init()
    {
#ifndef DEBUG
        obj = OBJECT_FACTORY->CreateEmptyObject();
        obj->SetName("Cursor");
        obj->AddComponent(new Transform());
        obj->AddComponent(new Sprite());
        obj->Init();
        (obj->transform)->SetScale({ 50, 90 });
        (obj->transform)->SetTranslation({ 0, 0,999 });
		(obj->sprite)->SetTexture(T(Picture::Mouse));
        GRAPHICS->AddSprite(obj->sprite);
#endif

    }


    void CursorController::Update()
    {
#ifndef DEBUG
		if (Input::GetInstance().IsMousePressed(SDL_BUTTON_LEFT) && !PLAYER_CONTROLLER->CanUsingInventory)
			obj->sprite->SetTexture(T(Picture::Mouse_Grab));
		else
			obj->sprite->SetTexture(T(Picture::Mouse));

        SDL_GetMouseState(&mx, &my);
        obj->transform->SetTranslation({ mx + GRAPHICS->GetCamera()->GetPosition().x - 640,360 - my + GRAPHICS->GetCamera()->GetPosition().y,999 });
#endif

    }


}
