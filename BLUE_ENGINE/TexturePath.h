/*
*  File Name : TexturePath.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Enum to string or string to enum about texture path
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <string>

namespace BLUE
{
    constexpr unsigned int HashCode(const char* str)
    {
        return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
    }

	enum class Picture
	{
		Background_MainMenu,
		Background_LevelSelect,
		Option,
		Background_InGame,
		Background_Sea,
		Background_Sea_Light_Effect,

		Clear_Ribbon,
		Clear_Ship,
		Clear_Bird,
		Clear_Player,


        Button_Option,
        Button_Start,
        Button_Exit,
        Button_Credit,
        Button_FullScreen,
        Button_MainMenu,
        Button_Arrow_Left,
        Button_Arrow_Right,
        Button_X,

        CheckBox_False,
        CheckBox_True,

        Icon_Audio,

        Icon_Replay,
		Icon_Replay_InGame,
        Icon_Option,
        Icon_LevelSelect,
		Icon_1,
		Icon_2,
		Icon_3,
		Icon_4,
		Icon_5,
		Icon_6,
		Icon_7,
		Icon_8,
		Icon_9,
		Icon_10,
		Icon_11,
		Icon_12,
		grey_icon_2,
		grey_icon_3,
		grey_icon_4,
		grey_icon_5,
		grey_icon_6,
		grey_icon_7,
		grey_icon_8,
		grey_icon_9,
		grey_icon_10,
		grey_icon_11,
		grey_icon_12,

        Mouse,
		Mouse_Grab,

        Hud,
        Hud_BulletState_Future,
        Hud_BulletState_Past,

        Credit,
        DialogueBox,

        Splash_Digipen,
        Splash_FMOD,
        Splash_Game,

        Effect_Fade,
        Effect_Smoke,

        Player,
        Player_Animation,
        Player_Animation_Flip,
		Player_Parachute,
        Player_Particle,
        Bullet_Future,
        Bullet_Past,

		Bubble_F,
		Bubble_WASD,
		Bubble_Mouse_Wheel,
		Bubble_Mouse_Left,
		Bubble_12,

		Popup_Box,
		Popup_Yes,
		Popup_No,

        Item_Seed,
        Item_Sprout,
        Item_Tree,

        Item_Metal,
        Item_Key,
        Item_RustKey,

        Item_River,
        Item_Axe,
        Item_Portal,

        Item_Wall_1,
        Item_Wall_2,

        Item_BonFire_Yet,
        Item_BonFire,
        Item_BonFire_Burned,

        Item_Poison_Sprout,
        Item_Poison_Plant,
        Item_Poison_Dead,
        Item_Poison_Spike,

        Item_Door_Opened,
        Item_Door_Axe,
        Item_Door_Key,
        Item_Door_Log,
        Item_Door_Seed,

        Item_Box_Closed,
        Item_Box_Opened,

        Item_Vine_1,
        Item_Vine_2,
        Item_Vine_3,

        Item_Torch_Yet,
        Item_Torch,
        Item_Torch_Burned,

        Item_Log,
        Item_Bridge,
        Item_WoodBoard,
        Item_WoodBoard_Broken,

        Item_Mud,
        Item_Puddle,
        Item_Pond,

        Item_Spike_1,
        Item_Spike_2,
        Item_Spike_3,


        Count
    };

    std::string T(Picture picture);
}
