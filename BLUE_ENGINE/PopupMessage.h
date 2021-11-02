/*
*  File Name : PopupMessage.h
*  Primary Author : Hyun Jina
*  Secondary Author : 
*  Brief: Popup message that asking 'are you really want to quit/restart?'
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Button.h"

namespace BLUE
{
	class PopupMessage
	{
	public:
		PopupMessage();
		~PopupMessage();

		void Init();
		
		bool isExist() const;
		bool IsClicked(int mouse_x, int mouse_y, bool &yes_clicked);
		void ChangeBoxImage(const std::string & texture);
		
		void Delete();
	private:
		void Init(Object *&object, glm::vec2 size, glm::vec3 pos, const std::string & texture, const std::string & name);

		bool is_initialize;
		
		Object * background, *box;
		Button yes, no;
	};
	extern PopupMessage* POPUPMESSAGE;
}
