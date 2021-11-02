/*
*  File Name : Dialogue.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Show the dialogue
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "ObjectFactory.h"

namespace BLUE
{
	/* dialogue type */
    enum class dialogue_name
    {
        dialogue_1,
        d2,
		d3,
		d4,
		d5,
		d6
	};

	/* All dialogues are saved in this struct */
	struct dialogue_collection
	{
		dialogue_collection();

		/* Initialize Individual vector for dialogue */
		void Init(dialogue_name name, std::initializer_list<std::string> dialogue);
		/* Get string vector from enum */
		std::vector<std::string> *GetStrings(dialogue_name dialogue);
	private:

		/* one vector(std::string) for one enum */
		std::vector<std::string> dialogue_1;
                std::vector<std::string> d2;
				std::vector<std::string> d3;
				std::vector<std::string> d4;
				std::vector<std::string> d5;
				std::vector<std::string> d6;

	};

	class Dialogue
	{
	public:
		Dialogue();
		~Dialogue();

		/* Delete the box and text when the dialogue is finished*/
		void DeleteObject();

		/* Make the box and text */
		void Init(dialogue_name dialogue);
		void Update();

		/* Set current dialogue string */
		void SetCurrentDialogue(dialogue_name name);

		void SetTextZ(float z);

		bool dialogue_on = false;
	private:
		/* Set text */
		void SetText(const std::string &string);
		/* Render the text*/
		void RenderText(const std::string &string);

		const float ratioofdialogue;

		bool isChanged;
		bool isFullSentence;
		bool isFinish;
		bool isInitialized;

		int string_index;
		int dialogue_size;

		Object* box;
		Object* text;

		dialogue_collection collection;
		dialogue_name current_dialogue;

		int timer;
		int index;
	};
	extern Dialogue *DIALOGUE;
}

