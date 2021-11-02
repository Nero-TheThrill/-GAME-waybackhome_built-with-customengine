/*
*  File Name : Dialogue.cpp
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Show the dialogue
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Dialogue.h"
#include "Object.h"
#include "Graphics.h"
#include "TexturePath.h"

namespace BLUE
{
    dialogue_collection::dialogue_collection()
    {
        Init(dialogue_name::dialogue_1,
            {
                "MOVE: \"A\",\"S\",\"W\",\"D\" keys\nGET  ITEM: \"F\" key"
            });
        Init(dialogue_name::d2,
            {
					"USE ITEM: DRAG and DROP \nwith MOUSE LEFT CLICK"
            });
		Init(dialogue_name::d3,
			{
				"Shooting: Mouse Left Click",
				"Change Bullet State: Mouse Wheel",
				"Scroll Down or 1: Past Bullet \n Scroll UP or 2: Future Bullet"
            });
        Init(dialogue_name::d4,
            {
                    "*DANGER*\n IF YOU DIE, THE LEVEL WILL BE RESTARTED"
            });
		Init(dialogue_name::d5,
			{
					"Make a GOLDEN AXE and Open the DOOR!"
			});
		Init(dialogue_name::d6,
			{
					"The bullet from flower will destroy the spike!"
			});
    }

    void dialogue_collection::Init(dialogue_name name, std::initializer_list<std::string> dialogue)
    {
        std::vector<std::string> *strings = nullptr;
        strings = GetStrings(name);
        for (const std::string &str : dialogue)
        {
            strings->push_back(str);
        }
    }

    std::vector<std::string>* dialogue_collection::GetStrings(dialogue_name dialogue)
    {
        switch (dialogue)
        {
        case dialogue_name::dialogue_1:
            return &dialogue_1;
        case dialogue_name::d2:
            return &d2;
        case dialogue_name::d3:
            return &d3;
        case dialogue_name::d4:
            return &d4;
		case dialogue_name::d5:
			return &d5;
		case dialogue_name::d6:
			return &d6;
        }
        return &dialogue_1;
    }

    Dialogue *DIALOGUE = nullptr;

    Dialogue::Dialogue() :
        ratioofdialogue(0.2f),
        isChanged(true),
        isFullSentence(true),
        isFinish(false),
        isInitialized(false),
        string_index(0),
        dialogue_size(0),
        box(nullptr),
        text(nullptr),
        current_dialogue(dialogue_name::dialogue_1),
        timer(0),
        index(1)
    {
        DIALOGUE = this;
    }

    Dialogue::~Dialogue()
    {
        DeleteObject();
    }

    void Dialogue::DeleteObject()
    {
        dialogue_on = false;
        if (box != nullptr)
        {
            GRAPHICS->DeleteSprite(box->sprite);
            OBJECT_FACTORY->Destroy(box);
            box = nullptr;
        }
        if (text != nullptr)
        {
            GRAPHICS->DeleteSpriteText(text->spritetext);
            OBJECT_FACTORY->Destroy(text);
            text = nullptr;
        }
        isInitialized = false;
        timer = 0;
        index = 1;
    }

    void Dialogue::Init(dialogue_name dialogue)
    {
        dialogue_on = true;
        timer = 0;
        index = 1;
        SetCurrentDialogue(dialogue);
        static glm::vec2 window_size = GRAPHICS->window_size;

        const float box_size_y = window_size.y * ratioofdialogue;

        // You can change the box's y position here
        const float box_position_y = (-window_size.y / 2.f) + (box_size_y / 2.f);

        // Initialize the box
        if (box == nullptr)
        {
            box = OBJECT_FACTORY->CreateEmptyObject();
            box->SetName("box");
            box->AddComponent(new Transform());
            box->AddComponent(new Sprite());
            box->Init();
            box->sprite->SetTexture(T(Picture::DialogueBox));
            box->sprite->isHud = true;
            box->transform->SetScale({ window_size.x, box_size_y });
            box->transform->SetTranslation({ 0.f, box_position_y, 300.f });
            GRAPHICS->AddSprite(box->sprite);
        }

        // Initialize the text
        if (text == nullptr)
        {
            /* margin of left and top for the text */
            constexpr float left_margin = 25.f;
            constexpr float upper_margin = 0.f;
            constexpr float letter_size = 50.f;

            text = OBJECT_FACTORY->CreateEmptyObject();
            text->SetName("text");
            text->AddComponent(new Transform());
            text->AddComponent(new SpriteText());
            text->Init();
            text->transform->SetScale({ letter_size, letter_size });
            text->transform->SetTranslation({ -window_size.x / 2.f + left_margin, box_position_y + letter_size / 2.f + upper_margin, 300.5f });
            text->spritetext->SetFontPath("font/NanumSquareRoundB.ttf");
            text->spritetext->isHud = true;
            GRAPHICS->AddSpriteText(text->spritetext);
        }
        isInitialized = true;
        isFinish = false;
    }

    void Dialogue::Update()
    {
        static std::vector<std::string> dialog = *collection.GetStrings(current_dialogue);

        /* if the dialogue type is changed */
        if (isChanged)
        {
            dialog = *collection.GetStrings(current_dialogue);
            dialogue_size = static_cast<int>(dialog.size());
            string_index = 0;
            isChanged = false;
            isFinish = false;

            if (!isInitialized)
                Init(current_dialogue);
        }

        /* if the dialogue is finished */
        if (isFinish)
        {
            if (isInitialized)
                DeleteObject();
            return;
        }

        RenderText(dialog.at(string_index));
    }

    void Dialogue::SetCurrentDialogue(dialogue_name name)
    {
        current_dialogue = name;
        isChanged = true;
    }

    void Dialogue::SetTextZ(float z)
    {
		if (isInitialized)
			text->transform->SetPositionZ(z);
    }

    void Dialogue::SetText(const std::string& string)
    {
		if(isInitialized)
	        text->spritetext->SetText(string);
    }

    void Dialogue::RenderText(const std::string& string)
    {
        /* you can set the speed of dialogue */
        constexpr int speed = 15;

        const int size = static_cast<int>(string.length());

        if (index >= size)
            isFullSentence = true;
        else
            isFullSentence = false;

        static Input input = Input::GetInstance();
        if (input.IsMouseTriggered(SDL_BUTTON_LEFT))
        {
            /* if full-sentence is written */
            if (isFullSentence)
            {
                /* go to next string */
                string_index++;
                index = 0;

                if (/* if last string */ string_index >= dialogue_size)
                {
                    isFinish = true;
                }
            }
            /* if individual letter is written */
            else
            {
                index = size;
            }
            isFullSentence = !isFullSentence;
        }

        /* Set Text */
        if (!(timer % speed))
        {
            SetText(string.substr(0, index));

            if (index < size)
                index++;
        }

        timer += 10;
    }
}
