/*
*  File Name : LevelUpdateCollection.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Jina Hyun
*  Brief: level update functions
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#pragma once
#include "LevelHeaderCollection.h"

namespace BLUE
{
    class LevelCollection
    {
    private:
		void InitDialogue();
		void InitBubble();
		void UpdateBubble();

		void Playing(std::string levelTXT, GameLevels nextLevel);
		void MouseEvent();
		void ChangeBulletState();

		void StoreInformation(InfoType info_type);

		void UpdateFunctions();

        bool IsFuture;
        bool is_future_gun;

        Camera *camera;

        MouseController mousecontroller;
        GhostController ghost_;

        Object* player;
        Object* hud;
        Object* arrow;
        Object* background;
		Button option, replay;

		Object * bubble, *x;
		      
        rapidjson::JSONwriter* JSONWRITER;
        rapidjson::JSONreader* JSONREADER;
        bool IsPaused;

        ReplayInfo info;
        LerpSmoothCamera lerp;

        GameLevels levelinfo;
        bool ReplayOn;

        FadeEffect fade_effect;
		bool is_restarted, is_bubble_exist, iven_used_at_least_once;

		bool imgod;

		int mouse_x, mouse_y;
    public:
		bool canUseGun = true;
		int level_data = 0;
		LevelCollection();
		~LevelCollection();

        void InitLEVEL(std::string levelTXT, GameLevels linfo);
        void CloseLEVEL(std::string levelTXT);
        void UpdateLEVEL(std::string levelTXT, GameLevels nextLevel);
        void SetReplayOn(bool shouldreplay);
		void MakeObject(Object *&object, glm::vec2 size, glm::vec3 position, Picture picture, bool is_hud = false, const std::string & name = "object");
    };
	extern bool play_once[12];
	extern bool goingnext[11];
}
