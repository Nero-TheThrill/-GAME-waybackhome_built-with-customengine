/*
*  File Name : PopupMessage.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Popup message that asking 'are you really want to quit/restart?'
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "PopupMessage.h"
#include "ObjectFactory.h"
#include "Graphics.h"
#include "TexturePath.h"
#include "LevelHeaderCollection.h"

namespace BLUE
{
	extern PopupMessage* POPUPMESSAGE = nullptr;

	PopupMessage::PopupMessage()
		: is_initialize(false),
		background(nullptr),
		box(nullptr)
	{
		POPUPMESSAGE = this;
	}

	PopupMessage::~PopupMessage()
	{
		Delete();
	}

	void PopupMessage::Init()
	{
		if (is_initialize)
			return;

		Init(box, { 370, 256 }, { 0, 0, 950 }, T(Picture::Popup_Box), "box");
		Init(background, { 1281, 721 }, { 0, 0, 940 }, T(Picture::Effect_Fade), "back");
		background->sprite->SetColor({ 0, 0, 0, 100 });

		no.Init({ 100, -75, 960 }, { 129, 41 }, T(Picture::Popup_No));
		no.SetHud(true);

		yes.Init({ -100, -75, 960 }, { 129, 42 }, T(Picture::Popup_Yes));
		yes.SetHud(true);

		is_initialize = true;

		DIALOGUE->SetTextZ(980);
	}

	bool PopupMessage::isExist() const
	{
		return is_initialize;
	}

	bool PopupMessage::IsClicked(int mouse_x, int mouse_y, bool& yes_clicked) 
	{
		if (!is_initialize)
			return false;

		if(Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_ESCAPE))
		{
			Delete();
			return false;
		}

		bool is_clicked = yes.IsButtonClicked(mouse_x, mouse_y);

		if (is_clicked)
		{
			yes_clicked = true;
			return is_clicked;
		}

		is_clicked = no.IsButtonClicked(mouse_x, mouse_y);
	
		if(is_clicked)
			yes_clicked = false;

		return is_clicked;
	}

	void PopupMessage::ChangeBoxImage(const std::string& texture)
	{
		if(is_initialize)
			box->sprite->SetTexture(texture);
	}

	void PopupMessage::Delete()
	{
		if (is_initialize)
		{
			yes.Delete();
			no.Delete();

			GRAPHICS->DeleteSprite(box->sprite);
			OBJECT_FACTORY->Destroy(box);
			box = nullptr;

			GRAPHICS->DeleteSprite(background->sprite);
			OBJECT_FACTORY->Destroy(background);
			background = nullptr;

			DIALOGUE->SetTextZ(300.5f);

			is_initialize = false;
		}
	}

	void PopupMessage::Init(Object*& object, glm::vec2 size, glm::vec3 pos, const std::string& texture,	const std::string& name)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->AddComponent(new Sprite());
		object->AddComponent(new Transform());
		object->SetName(name);
		object->Init();

		object->transform->SetScale(size);
		object->transform->SetTranslation(pos);

		object->sprite->SetTexture(texture);
		object->sprite->isHud = true;

		GRAPHICS->AddSprite(object->sprite);
	}
}
