/*
*  File Name : TexturePath.cpp
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Enum to string or string to enum about texture path
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "TexturePath.h"

namespace BLUE
{
    std::string T(Picture picture)
    {
        std::string texture_path = "texture/";

        switch (picture)
        {
        case Picture::Background_MainMenu:
            texture_path += "etc/Menu";
            break;
		case Picture::Background_LevelSelect:
			texture_path += "etc/Level_Select";
			break;
        case Picture::Option:
            texture_path += "etc/Option";
            break;
        case Picture::Background_InGame:
            texture_path += "etc/Background";
            break;
						

		case Picture::Background_Sea:
			texture_path += "ClearScreen/Sea";
        	break;
		case Picture::Background_Sea_Light_Effect:
			texture_path += "ClearScreen/Light";
			break;
		case Picture::Clear_Ribbon:
			texture_path += "ClearScreen/Ribbon";
			break;
		case Picture::Clear_Ship:
			texture_path += "ClearScreen/Ship";
			break;
		case Picture::Clear_Bird:
			texture_path += "ClearScreen/Bird";
			break;
		case Picture::Clear_Player:
			texture_path += "ClearScreen/player_animation";
			break;


        case Picture::Button_Option:
            texture_path += "Button/Option";
            break;
        case Picture::Button_Start:
            texture_path += "Button/Start";
            break;
        case Picture::Button_Exit:
            texture_path += "Button/end";
            break;
        case Picture::Button_Credit:
            texture_path += "Button/credit";
            break;
        case Picture::Button_FullScreen:
            texture_path += "Button/fullscreen";
            break;
        case Picture::Button_MainMenu:
            texture_path += "Button/mainmenu";
            break;
        case Picture::Button_Arrow_Left:
            texture_path += "Button/volumeDown";
            break;
        case Picture::Button_Arrow_Right:
            texture_path += "Button/volumeUp";
            break;


        case Picture::CheckBox_False:
            texture_path += "Button/CheckBoxFalse";
            break;
        case Picture::CheckBox_True:
            texture_path += "Button/CheckBoxTrue";
            break;


        case Picture::Icon_Audio:
            texture_path += "Icon/audio";
            break;


        case Picture::Mouse:
            texture_path += "Setting/mouse";
            break;
		case Picture::Mouse_Grab:
			texture_path += "Setting/mouse_grab";
			break;

        case Picture::Hud:
            texture_path += "etc/hud";
            break;
        case Picture::Hud_BulletState_Future:
            texture_path += "etc/Future";
            break;
        case Picture::Hud_BulletState_Past:
            texture_path += "etc/Past";
            break;

        case Picture::Credit:
            texture_path += "etc/credit_info";
            break;
        case Picture::DialogueBox:
            texture_path += "etc/Dialogue_Box";
            break;


        case Picture::Splash_Digipen:
            texture_path += "etc/DigipenLogo";
            break;
        case Picture::Splash_FMOD:
            texture_path += "etc/FMOD";
            break;
        case Picture::Splash_Game:
            texture_path += "etc/game_splash";
            break;

        case Picture::Effect_Fade:
            texture_path += "Effect/White";
            break;
        case Picture::Effect_Smoke:
            texture_path += "Effect/Smoke";
            break;

		case Picture::Popup_Box:
			texture_path += "Setting/Popup_Box";
			break;
		case Picture::Popup_Yes:
			texture_path += "Setting/Popup_Yes";
			break;
		case Picture::Popup_No:
			texture_path += "Setting/Popup_No";
			break;


        case Picture::Player:
            texture_path += "Player/player";
            break;
        case Picture::Player_Animation:
            texture_path += "Player/character_animation";
            break;
        case Picture::Player_Animation_Flip:
            texture_path += "Player/character_animation_flip";
            break;
        case Picture::Player_Particle:
            texture_path += "Effect/particle";
            break;
		case Picture::Player_Parachute:
			texture_path += "Player/player_animation";
			break;
        case Picture::Bullet_Future:
            texture_path += "Player/Bullet_Future";
            break;
        case Picture::Bullet_Past:
            texture_path += "Player/Bullet_Past";
            break;


        case Picture::Item_Seed:
            texture_path += "Item/Seed";
            break;
        case Picture::Item_Sprout:
            texture_path += "Item/Sprout";
            break;
        case Picture::Item_Tree:
            texture_path += "Item/Tree";
            break;

        case Picture::Item_Metal:
            texture_path += "Item/Metal";
            break;
        case Picture::Item_Key:
            texture_path += "Item/Key";
            break;
        case Picture::Item_RustKey:
            texture_path += "Item/Key_Rust";
            break;

        case Picture::Item_River:
            texture_path += "Item/river";
            break;
        case Picture::Item_Axe:
            texture_path += "Item/Axe";
            break;
        case Picture::Item_Portal:
            texture_path += "Item/Portal";
            break;

        case Picture::Item_Wall_1:
            texture_path += "Item/Wall_1";
            break;        
        case Picture::Item_Wall_2:
            texture_path += "Item/Wall_2";
            break;

        case Picture::Item_BonFire_Yet:
            texture_path += "Item/Bonfire_Yet";
            break;
        case Picture::Item_BonFire:
            texture_path += "Item/Bonfire";
            break;
        case Picture::Item_BonFire_Burned:
            texture_path += "Item/Bonfire_Burned";
            break;

        case Picture::Item_Poison_Sprout:
            texture_path += "Item/PoisonPlant_Sprout";
            break;
        case Picture::Item_Poison_Plant:
            texture_path += "Item/PoisonPlant";
            break;
        case Picture::Item_Poison_Dead:
            texture_path += "Item/PoisonPlant_Dead";
            break;
        case Picture::Item_Poison_Spike:
            texture_path += "Item/PoisonPlant_Spike";
            break;

        case Picture::Item_Door_Opened:
            texture_path += "Item/OpenDoor";
            break;

        case Picture::Item_Door_Axe:
            texture_path += "Item/Door_Axe";
            break;
        case Picture::Item_Door_Key:
            texture_path += "Item/Door_Key";
            break;
        case Picture::Item_Door_Log:
            texture_path += "Item/Door_Log";
            break;
        case Picture::Item_Door_Seed:
            texture_path += "Item/Door_Seed";
            break;

        case Picture::Item_Box_Closed:
            texture_path += "Item/Box_Closed";
            break;
        case Picture::Item_Box_Opened:
            texture_path += "Item/Box_Opened";
            break;

        case Picture::Item_Vine_1:
            texture_path += "Item/Vine_1";
            break;
        case Picture::Item_Vine_2:
            texture_path += "Item/Vine_2";
            break;
        case Picture::Item_Vine_3:
            texture_path += "Item/Vine_3";
            break;

        case Picture::Item_Torch_Yet:
            texture_path += "Item/Torch_Yet";
            break;
        case Picture::Item_Torch:
            texture_path += "Item/Torch";
            break;
        case Picture::Item_Torch_Burned:
            texture_path += "Item/Torch_Burned";
            break;

        case Picture::Item_Log:
            texture_path += "Item/Log";
            break;
        case Picture::Item_Bridge:
            texture_path += "Item/Bridge";
            break;
        case Picture::Item_WoodBoard:
            texture_path += "Item/Woodboard";
            break;
        case Picture::Item_WoodBoard_Broken:
            texture_path += "Item/Woodboard_Broken";
            break;

        case Picture::Item_Mud:
            texture_path += "Item/Mud";
            break;
        case Picture::Item_Puddle:
            texture_path += "Item/Puddle";
            break;
        case Picture::Item_Pond:
            texture_path += "Item/Pond";
            break;

        case Picture::Item_Spike_1:
            texture_path += "Item/Spike_1";
            break;
        case Picture::Item_Spike_2:
            texture_path += "Item/Spike_2";
            break;
        case Picture::Item_Spike_3:
            texture_path += "Item/Spike_3";
            break;


        case Picture::Button_X:
            texture_path += "Button/x";
            break;


        case Picture::Icon_Replay:
            texture_path += "Icon/Replay";
            break;
        case Picture::Icon_Replay_InGame:
            texture_path += "Icon/Ingame_replay";
            break;
        case Picture::Icon_Option:
            texture_path += "Icon/Option";
            break;
        case Picture::Icon_LevelSelect:
            texture_path += "Icon/LevelSelect";
            break;


        case Picture::Icon_1: 
			texture_path += "Button/Number/1";
        	break;
        case Picture::Icon_2:
			texture_path += "Button/Number/2";
			break;
        case Picture::Icon_3:
			texture_path += "Button/Number/3";
			break;
        case Picture::Icon_4:
			texture_path += "Button/Number/4";
			break;
        case Picture::Icon_5:
			texture_path += "Button/Number/5";
			break;
        case Picture::Icon_6:
			texture_path += "Button/Number/6";
			break;
        case Picture::Icon_7:
			texture_path += "Button/Number/7";
			break;
        case Picture::Icon_8:
			texture_path += "Button/Number/8";
			break;
        case Picture::Icon_9:
			texture_path += "Button/Number/9";
			break;
        case Picture::Icon_10:
			texture_path += "Button/Number/10";
			break;
        case Picture::Icon_11:
			texture_path += "Button/Number/11";
			break;
        case Picture::Icon_12:
			texture_path += "Button/Number/12";
			break;
		case Picture::grey_icon_2:
			texture_path += "Button/Number/grey_2";
			break;
		case Picture::grey_icon_3:
			texture_path += "Button/Number/grey_3";
			break;
		case Picture::grey_icon_4:
			texture_path += "Button/Number/grey_4";
			break;
		case Picture::grey_icon_5:
			texture_path += "Button/Number/grey_5";
			break;
		case Picture::grey_icon_6:
			texture_path += "Button/Number/grey_6";
			break;
		case Picture::grey_icon_7:
			texture_path += "Button/Number/grey_7";
			break;
		case Picture::grey_icon_8:
			texture_path += "Button/Number/grey_8";
			break;
		case Picture::grey_icon_9:
			texture_path += "Button/Number/grey_9";
			break;
		case Picture::grey_icon_10:
			texture_path += "Button/Number/grey_10";
			break;
		case Picture::grey_icon_11:
			texture_path += "Button/Number/grey_11";
			break;
		case Picture::grey_icon_12:
			texture_path += "Button/Number/grey_12";
			break;

        case Picture::Bubble_F: 
			texture_path += "Setting/Bubble_F";
        	break;
        case Picture::Bubble_WASD:
			texture_path += "Setting/Bubble_WASD";
			break;
        case Picture::Bubble_Mouse_Wheel:
			texture_path += "Setting/Bubble_MouseWheel";
			break;
        case Picture::Bubble_Mouse_Left:
			texture_path += "Setting/Bubble_MouseLeft";
			break;
		case Picture::Bubble_12:
			texture_path += "Setting/Bubble_12";
			break;

		case Picture::Count:
            return "";
        }

        texture_path += ".png";

        return texture_path;
    }
}
