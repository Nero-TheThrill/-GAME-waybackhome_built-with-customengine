/*
*  File Name : ObjectController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon
*  Brief: Controll Objects. Check all collision with player.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"ObjectController.h"



#include "EnemyController.h"
#include "BaseController.h"
#include "SeedController.h"
#include "TreeController.h"
#include "Archiver.h"
#include "BoxController.h"
#include <iostream>
#include "RustKeyController.h"
#include "PoisonplantController.h"
#include "LogController.h"
#include "RiverController.h"
#include "AxeController.h"
#include "SpikeController.h"
#include "GhostRiverController.h"
#include "Portal.h"
#include "BlastFurnaceController.h"
#include "PoisonPlantManager.h"
#include "WallController.h"
#include "WallController1.h"
#include "WallController2.h"
#include "WallController3.h"
#include "DoorController.h"
#include "VineController.h"
#include "WoodBoardController.h"
#include "TorchController.h"
#include "PuddleController.h"
#include "PastBulletController.h"
#include "FutureBulletController.h"
#include "PoisonBulletController.h"

namespace BLUE
{
    ObjectController* OBJECT_CONTROLLER = nullptr;
    ObjectController::ObjectController()
    {
        OBJECT_CONTROLLER = this;
    }

    void ObjectController::AddObject(Object* obj)
    {
        objects.push_back(obj);
    }

    void ObjectController::DeleteObject(int num) // Use this function in IMGUI delete button
    {
        POISONPLANT_MANAGER->Delete(objects.at(num));
        GRAPHICS->DeleteSprite(objects.at(num)->sprite);
        objects.at(num)->Destroy(objects.at(num));
        objects.erase(objects.begin() + num);
        controllers.erase(controllers.begin() + num);
   
    }

    Object* ObjectController::GetObject(int num)
    {
        if (num == static_cast<int>(objects.size()))
        {
            return nullptr;
        }
        else
            return objects.at(num);
    }

    void ObjectController::AddController(BaseController* ctype)
    {

        switch (ctype->GetControllerType())
        {
        case ControllerType_SEED:
            controllers.push_back(dynamic_cast<SeedController*>(ctype));
            break;
        case ControllerType_TREE:
            controllers.push_back(dynamic_cast<TreeController*>(ctype));
            break;
        case ControllerType_BOX:
            controllers.push_back(dynamic_cast<BoxController*>(ctype));
            break;
        case ControllerType_RUSTKEY:
            controllers.push_back(dynamic_cast<RustKeyController *>(ctype));
            break;
        case ControllerType_LOG:
            controllers.push_back(dynamic_cast<LogController*>(ctype));
            break;
        case ControllerType_RIVER:
            controllers.push_back(dynamic_cast<RiverController*>(ctype));
            break;
        case ControllerType_AXE:
            controllers.push_back(dynamic_cast<AxeController*>(ctype));
            break;
        case ControllerType_GHOSTRIVER:
            controllers.push_back(dynamic_cast<GhostRiverController*>(ctype));
            break;
        case ControllerType_PORTAL:
            controllers.push_back(dynamic_cast<Portal*>(ctype));
            break;
        case ControllerType_WALL:
            controllers.push_back(dynamic_cast<Wall*>(ctype));
            break;
        case ControllerType_SPIKE:
            controllers.push_back(dynamic_cast<SpikeController*>(ctype));
            break;
        case ControllerType_BLASTFURNACE:
            controllers.push_back(dynamic_cast<BlastFurnaceController*>(ctype));
            break;
        case ControllerType_POISONPLANT:
            controllers.push_back(dynamic_cast<PoisonplantController*>(ctype));
            break;
        case ControllerType_DOOR:
            controllers.push_back(dynamic_cast<DoorController*>(ctype));
            break;
        case ControllerType_VINE:
            controllers.push_back(dynamic_cast<VineController*>(ctype));
            break;
		case ControllerType_WOODBOARD:
			controllers.push_back(dynamic_cast<WoodBoardController*>(ctype));
			break;
		case ControllerType_TORCH:
			controllers.push_back(dynamic_cast<TorchController*>(ctype));
			break;
		case ControllerType_PUDDLE:
			controllers.push_back(dynamic_cast<PuddleController*>(ctype));
			break;
		case ControllerType_WALL1:
			controllers.push_back(dynamic_cast<Wall1*>(ctype));
			break;
		case ControllerType_WALL2:
			controllers.push_back(dynamic_cast<Wall2*>(ctype));
			break;
		case ControllerType_WALL3:
			controllers.push_back(dynamic_cast<Wall3*>(ctype));
			break;
        default:
            break;
        }

    }

    void ObjectController::DeleteController(BaseController* controller)
    {
        int cnt = 0;
        for (auto ctr : controllers)
        {
            if (ctr == controller)
            {
                controllers.erase(controllers.begin() + cnt);
                objects.erase(objects.begin() + cnt);
            }
            cnt++;
        }
    }


    int ObjectController::GetSize()
    {
        return static_cast<int>(objects.size());
    }

    std::string ObjectController::GetName(int num)
    {
        return objects.at(num)->GetName();
    }

    BaseController * ObjectController::GetCollideWith(Object * obj, ControllerType ctype)
    {
		std::vector<int> number;
		std::vector<BaseController*> CollideControllers;
        unsigned count = 0;
        for (count = 0; count < objects.size(); count++)
        {
            if(ctype==ControllerType_EXCEPTPOISONPLANT)
            {
                (objects.at(count)->rectangle)->update();
                obj->rectangle->update();
                (objects.at(count)->collision)->update(*(objects.at(count)->rectangle), *(obj->rectangle));
                if (controllers.at(count)->GetControllerType()!=ControllerType_POISONPLANT&&(objects.at(count)->collision)->GetCollisionState())
                {
                    return controllers.at(count);
                }
            }
            else if ((objects.at(count) != obj && controllers.at(count)->GetControllerType() == ctype) || ctype == ControllerType_ANYTHING)  // if controllertype is anything, return first one.
            {
                if (objects.at(count) != obj) {
                    (objects.at(count)->rectangle)->update();
                    obj->rectangle->update();
                    (objects.at(count)->collision)->update(*(objects.at(count)->rectangle), *(obj->rectangle));
                    if ((obj->GetName()=="FutureBullet" && (objects.at(count)->collision)->GetCollisionState() )||
						(obj->GetName() == "PastBullet" && (objects.at(count)->collision)->GetCollisionState())||
						(obj->GetName() == "PoisonBullet" && (objects.at(count)->collision)->GetCollisionState()) ||
						(controllers.at(count)->GetControllerType() != ControllerType_WALL && (objects.at(count)->collision)->GetCollisionState()))
                    {
					

							CollideControllers.push_back(controllers.at(count));
							number.push_back(count);
	
                    }
                }
            }
        }
		if(CollideControllers.empty())
        return nullptr;
		else
		{
			float obj1_x = obj->transform->GetTranslation().x;
			float obj1_y = obj->transform->GetTranslation().y;
			float obj2_x = objects[number[0]]->transform->GetTranslation().x;
			float obj2_y = objects[number[0]]->transform->GetTranslation().y;
			float dis = std::sqrt((obj1_x - obj2_x)*(obj1_x - obj2_x) + (obj1_y - obj2_y)*(obj1_y - obj2_y));
			float Min_distance=dis;
			int returnval=0;
			for (int i = 0; i < static_cast<int>(CollideControllers.size()); i++)
			{
				obj1_x = obj->transform->GetTranslation().x;
				obj1_y = obj->transform->GetTranslation().y;
				obj2_x = objects[number[i]]->transform->GetTranslation().x;
				obj2_y = objects[number[i]]->transform->GetTranslation().y;
				dis = std::sqrt((obj1_x - obj2_x)*(obj1_x - obj2_x) + (obj1_y - obj2_y)*(obj1_y - obj2_y));
				if (Min_distance > dis)
				{
					returnval = i;
					Min_distance = dis;
				}
			}
			return CollideControllers[returnval];
		}
    }

    std::vector<BaseController*> ObjectController::GetVecCollideWith(Object* obj)
    {
        std::vector<BaseController*> CollideControllers;
        CollideControllers.clear();
        unsigned count = 0;
        for (count = 0; count < objects.size(); count++)
        {

            if (objects.at(count) != obj)
            {
                (objects.at(count)->rectangle)->update();
                (obj->rectangle)->update();
                (objects.at(count)->collision)->update(*(objects.at(count)->rectangle), *(obj->rectangle));
                if ((objects.at(count)->collision)->GetCollisionState())
                {
                    CollideControllers.push_back(controllers.at(count));
                }
            }
        }
        return CollideControllers;
    }

    void ObjectController::UpdateBullet(std::vector<Object*>& bulletvec)
    {
        int objsize = static_cast<int>(objects.size());
        int bulsize = static_cast<int>(bulletvec.size());
        //for(int bulcount=0;bulcount<bulsize;bulcount++)
        //{
        //    (bulletvec.at(bulcount)->collision)->update(*(PLAYER_CONTROLLER->GetObject()->rectangle), *(bulletvec.at(bulcount)->rectangle));
        //    if ((bulletvec.at(bulcount)->collision)->GetCollisionState())
        //    {
        //        if (bulletvec.at(bulcount)->GetName() == "PoisonBullet")
        //        {
        //            std::cout << "YEAHEFAHE" << std::endl;
        //            PLAYER_CONTROLLER->isDead = true;
        //        }
        //    }
        //}
        for (int objcount = 0; objcount < objsize; objcount++)
        {
            (objects.at(objcount)->rectangle)->update();
         
            for (int count = 0; count < bulsize; count++)
            {
                (bulletvec.at(count)->rectangle)->update();
                (bulletvec.at(count)->collision)->update(*(objects.at(objcount)->rectangle), *(bulletvec.at(count)->rectangle));
                if ((bulletvec.at(count)->collision)->GetCollisionState())
                {
                    if (bulletvec.at(count)->GetName() == "FutureBullet")
                    {

                        if (GetCollideWith(bulletvec.at(count), controllers.at(objcount)->GetControllerType()) != nullptr)
                        {
                            BaseController* collide_obj = GetCollideWith(bulletvec.at(count), ControllerType_ANYTHING);
							if (collide_obj != nullptr && collide_obj->GetControllerType() == ControllerType_DOOR)
							{
								DoorController* door = dynamic_cast<DoorController*>(collide_obj);
								if (!(door->isDead))
								{
									FUTUREBULLET_CONTROLLER->DeleteWhenCollide(count);
								}

							}
							else if (!collide_obj->isInInventory)
							{
								collide_obj->ChangeToFuture();
								FUTUREBULLET_CONTROLLER->DeleteWhenCollide(count);
							}
                        }
                     


                    }
                    else if (bulletvec.at(count)->GetName() == "PastBullet")
                    {
                        if (GetCollideWith(bulletvec.at(count), controllers.at(objcount)->GetControllerType()) != nullptr)
                        {
                            BaseController* collide_obj = GetCollideWith(bulletvec.at(count), ControllerType_ANYTHING);
							if (collide_obj != nullptr && collide_obj->GetControllerType() == ControllerType_DOOR)
							{
								DoorController* door = dynamic_cast<DoorController*>(collide_obj);
								if (!(door->isDead))
								{
									PASTBULLET_CONTROLLER->DeleteWhenCollide(count);
								}

							}
							else if (!collide_obj->isInInventory)
							{

								collide_obj->ChangeToPast();
								PASTBULLET_CONTROLLER->DeleteWhenCollide(count);
							}
                        }

                    }
                    else if (bulletvec.at(count)->GetName() == "PoisonBullet")
                    {
                        if (GetCollideWith(bulletvec.at(count), controllers.at(objcount)->GetControllerType()) != nullptr)
                        {
                            BaseController* collide_obj = GetCollideWith(bulletvec.at(count), ControllerType_EXCEPTPOISONPLANT);
							if (collide_obj != nullptr && collide_obj->GetControllerType() == ControllerType_DOOR)
							{
								DoorController* door = dynamic_cast<DoorController*>(collide_obj);
								if (!(door->isDead))
								{
									POISONBULLET_CONTROLLER->DeleteWhenCollide(count);
								}

							}
                            else if (collide_obj != nullptr)
                            {
                                if (!collide_obj->isInInventory)
                                {
                                    collide_obj->HitPoison();
                                } 
                                POISONBULLET_CONTROLLER->DeleteWhenCollide(count);
                            }
                        }

                       
                    }
                    if(objsize!= static_cast<int>(objects.size()))
                    {
                        objcount = 0;
                        count = 0;
                        objsize = static_cast<int>(objects.size());
                    }
                }
                bulsize = static_cast<int>(bulletvec.size());

            }

            objsize = static_cast<int>(objects.size());
        }
    }

    void ObjectController::Reset(std::string path)
    {
        std::string compare = "noTXT";
        if (path != compare)
        {
#ifdef DEBUG
            JSONWRITER = new rapidjson::JSONwriter();
            WriteObject(JSONWRITER, objects, static_cast<unsigned>(objects.size()));
            JSONWRITER->WriteToFile(path);
            delete JSONWRITER;
#endif
        }
        for (auto obj : objects)
        {
            obj->Destroy(obj);
        }
        for (auto controller : controllers)
        {
            delete controller;
        }
        objects.clear();
        controllers.clear();
    }

    void ObjectController::Help()
    {
        BaseController* controller=nullptr;
        Object* obj=nullptr;
        int cnt;
        int objsize = static_cast<int>(controllers.size());
        for (int objcount = 0; objcount < objsize; objcount++)
        {
           if( controllers[objcount]->isInInventory)
           {
               controller = controllers[objcount];
               obj = objects[objcount];
               cnt = objcount;
           }
        }
        if (controller != nullptr)
        {
            for (int objcount = 0; objcount < objsize; objcount++)
            {
                if (controllers[objcount] != controller)
                {
                   if( FindInteract(controller,controllers[objcount]))
                   {
                       //don't change color
                   }
                   else
                   {
                    //   colors.push_back(objects[objcount]->sprite->GetMesh().GetColor());
                       objects[objcount]->sprite->SetColor(Color(100, 100, 100));
                   }

                }
            }
        }

    }

    void ObjectController::HelpDone()
    {
        int objsize = static_cast<int>(controllers.size());
        for (int objcount = 0; objcount < objsize; objcount++)
        {

                objects[objcount]->sprite->SetColor(Color(255,255,255));

        }
    }
}
