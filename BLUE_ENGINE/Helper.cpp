/*
*  File Name : Helper.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: If the object cannot interact, the object's color is changed to grey. 
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Helper.h"
#include "DoorController.h"
#include "TorchController.h"
#include "BlastFurnaceController.h"
#include "BoxController.h"
#include "WoodBoardController.h"
#include "RustKeyController.h"
#include "RiverController.h"

bool FindInteract(BLUE::BaseController* base1, BLUE::BaseController* base2)
{
    BLUE::ControllerType ctype1 = base1->GetControllerType();
    BLUE::ControllerType ctype2 = base2->GetControllerType();

    switch(ctype1)
    {
    case BLUE::ControllerType_AXE:
        if (ctype2 == BLUE::ControllerType_TREE)
            return true;
        if (ctype2 == BLUE::ControllerType_DOOR)
        {
            return  dynamic_cast<BLUE::DoorController*>(base2)->GetCurrentState() == BLUE::PRESENT  &&
                BLUE::ControllerType_AXE == dynamic_cast<BLUE::DoorController*>(base2)->GetItemType();
        }
		if (ctype2 == BLUE::ControllerType_RIVER)
		{
			return true;
		}
        break;
    case BLUE::ControllerType_LOG:

        if (ctype2 == BLUE::ControllerType_TORCH)
            return true;
        if (ctype2 == BLUE::ControllerType_BLASTFURNACE)
            return true;
        if (ctype2 == BLUE::ControllerType_DOOR)
        {
            return  dynamic_cast<BLUE::DoorController*>(base2)->GetCurrentState()==BLUE::PRESENT  &&
            BLUE::ControllerType_LOG == dynamic_cast<BLUE::DoorController*>(base2)->GetItemType();
        }
		if (ctype2 == BLUE::ControllerType_RIVER)
		{
			return true;
		}
        break;
    case BLUE::ControllerType_POISONPLANT:
        if (ctype2 == BLUE::ControllerType_TORCH)
        {
            return dynamic_cast<BLUE::TorchController*>(base2)->GetCurrentState() == BLUE::PRESENT;
        }
        if (ctype2 == BLUE::ControllerType_BLASTFURNACE)
        {
            return dynamic_cast<BLUE::BlastFurnaceController*>(base2)->GetCurrentState() == BLUE::PRESENT;
        }
        if (ctype2 == BLUE::ControllerType_RIVER)
        {
            return true;
        }
        break;
    case BLUE::ControllerType_RUSTKEY:
        if (ctype2 == BLUE::ControllerType_BOX)
        {
            return true;
        }       
        if (ctype2 == BLUE::ControllerType_DOOR)
        {
            return  dynamic_cast<BLUE::DoorController*>(base2)->GetCurrentState() == BLUE::PRESENT  &&
                BLUE::ControllerType_RUSTKEY == dynamic_cast<BLUE::DoorController*>(base2)->GetItemType();
        }      
        if (ctype2 == BLUE::ControllerType_TORCH)
        {
            return dynamic_cast<BLUE::RustKeyController*>(base1)->GetCurrentState() == BLUE::PAST &&
            dynamic_cast<BLUE::TorchController*>(base2)->GetCurrentState() == BLUE::PAST;
        }
		if (ctype2 == BLUE::ControllerType_RIVER)
		{
			return true;
		}
        break;
    case BLUE::ControllerType_SEED:
        if (ctype2 == BLUE::ControllerType_DOOR)
        {
            return BLUE::ControllerType_SEED == dynamic_cast<BLUE::DoorController*>(base2)->GetItemType();
        }
        if (ctype2 == BLUE::ControllerType_TORCH)
        {
            return dynamic_cast<BLUE::TorchController*>(base2)->GetCurrentState() == BLUE::PRESENT;
        }
        if (ctype2 == BLUE::ControllerType_BLASTFURNACE)
        {
            return dynamic_cast<BLUE::BlastFurnaceController*>(base2)->GetCurrentState() == BLUE::PRESENT;
        }      
        if (ctype2 == BLUE::ControllerType_RIVER)
        {
            return true;
        }

        break;
    case BLUE::ControllerType_TORCH:
		if (ctype2 == BLUE::ControllerType_RUSTKEY)
		{
			return dynamic_cast<BLUE::TorchController*>(base1)->GetCurrentState() == BLUE::PAST &&
				dynamic_cast<BLUE::RustKeyController*>(base2)->GetCurrentState() == BLUE::PAST;
		}
        if (ctype2 == BLUE::ControllerType_VINE)
        {
            return dynamic_cast<BLUE::TorchController*>(base1)->GetCurrentState() == BLUE::PRESENT;
        }

        if (ctype2 == BLUE::ControllerType_TREE)
        {
            return dynamic_cast<BLUE::TorchController*>(base1)->GetCurrentState() == BLUE::PRESENT;
        }
        if (ctype2 == BLUE::ControllerType_LOG)
        {
            return dynamic_cast<BLUE::TorchController*>(base1)->GetCurrentState() == BLUE::PRESENT;
        }
        if (ctype2 == BLUE::ControllerType_WOODBOARD)
        {
            return dynamic_cast<BLUE::TorchController*>(base1)->GetCurrentState() == BLUE::PRESENT;
        }
		if (ctype2 == BLUE::ControllerType_BLASTFURNACE)
		{
			return dynamic_cast<BLUE::TorchController*>(base1)->GetCurrentState() == BLUE::PAST &&
				dynamic_cast<BLUE::BlastFurnaceController*>(base2)->GetCurrentState() == BLUE::PRESENT;
		}
		if (ctype2 == BLUE::ControllerType_BLASTFURNACE)
		{
			return dynamic_cast<BLUE::TorchController*>(base1)->GetCurrentState() == BLUE::PRESENT &&
				dynamic_cast<BLUE::BlastFurnaceController*>(base2)->GetCurrentState() == BLUE::PAST;
		}
		if (ctype2 == BLUE::ControllerType_RIVER)
		{
			return true;
		}
        break;
    case BLUE::ControllerType_WOODBOARD:
		if (ctype2 == BLUE::ControllerType_RIVER)
		{
			return true;
		}

        if (ctype2 == BLUE::ControllerType_TORCH)
        {
            return dynamic_cast<BLUE::TorchController*>(base2)->GetCurrentState() == BLUE::PRESENT;
        }
        if (ctype2 == BLUE::ControllerType_BLASTFURNACE)
        {
            return dynamic_cast<BLUE::BlastFurnaceController*>(base2)->GetCurrentState() == BLUE::PRESENT;
        }
        break;
    }
    return false;

}
