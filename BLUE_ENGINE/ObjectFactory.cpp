/*
*  File Name : ObjectFactory.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Managing all objects in the game.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "ObjectFactory.h"
#include <cassert>
#include "Object.h"
#include <iostream>

namespace BLUE
{
    extern ObjectFactory* OBJECT_FACTORY = nullptr;

    ObjectFactory::ObjectFactory()
    {
        std::cout << "ObjectFactory constructor called" << std::endl;
        assert(OBJECT_FACTORY == nullptr && "ObjectFactory is already created");
        OBJECT_FACTORY = this;
        last_objectID = 0;
    }

    ObjectFactory::~ObjectFactory()
    {
    }

    void ObjectFactory::Update()
    {
        for (auto obj : ObjectsToBeDeleted)
        {
            if (obj == nullptr)
                continue;

            auto delete_objID = ObjectIDMap.find(obj->objectID);

            if (delete_objID != ObjectIDMap.end())
            {
                if (obj->allocatedchart[Object::SPRITE])
                {
					delete obj->sprite;
					obj->sprite = nullptr;
                }
                if (obj->allocatedchart[Object::COLLISION])
				{
					delete obj->collision;
					obj->collision = nullptr;
				}
                if (obj->allocatedchart[Object::RIGIDBODY])
				{
					delete obj->rigidbody;
					obj->rigidbody = nullptr;
				}
                if (obj->allocatedchart[Object::TRANSFORM])
				{
					delete obj->transform;
					obj->transform = nullptr;
				}
                if (obj->allocatedchart[Object::LINE])
				{
					delete obj->line;
					obj->line = nullptr;
				}
                if (obj->allocatedchart[Object::CIRCLE])
				{
					delete obj->circle;
					obj->circle = nullptr;
				}
                if (obj->allocatedchart[Object::RECTANGLE])
				{
					delete obj->rectangle;
					obj->rectangle = nullptr;
				}
                if (obj->allocatedchart[Object::SPRITETEXT])
				{
					delete obj->spritetext;
					obj->spritetext = nullptr;
				}
                if (obj->allocatedchart[Object::OBB])
				{
					delete obj->obb;
					obj->obb = nullptr;
				}

                delete obj;
				obj = nullptr;

                ObjectIDMap.erase(delete_objID);
            }
        }
        ObjectsToBeDeleted.clear();
    }

    void ObjectFactory::Destroy(Object* obj)
    {
        ObjectsToBeDeleted.push_back(obj);
    }

    void ObjectFactory::GiveObjectID(Object* obj)
    {
        ++last_objectID;
        obj->objectID = last_objectID;

        ObjectIDMap[last_objectID] = obj;
    }

    Object* ObjectFactory::CreateEmptyObject()
    {
        Object* obj = new Object();

        GiveObjectID(obj);

        return obj;
    }

    int ObjectFactory::CountObjectType(ObjectType objType)
    {
        int count = 0;

        for (auto blue = ObjectIDMap.begin(); blue != ObjectIDMap.end(); ++blue)
        {
            if ((*blue).second->GetObjectType() == objType)
            {
                count++;
            }
        }
        return count;
    }
    void ObjectFactory::DestroyAllObjects()
    {
        Update();
        for (auto blue : ObjectIDMap)
        {
            if (blue.second->allocatedchart[Object::SPRITE])
            {
				delete blue.second->sprite;
				blue.second->sprite = nullptr;
            }
            if (blue.second->allocatedchart[Object::COLLISION])
            {
				delete blue.second->collision;
				blue.second->collision = nullptr;
            }
            if (blue.second->allocatedchart[Object::RIGIDBODY])
			{
				delete blue.second->rigidbody;
				blue.second->rigidbody = nullptr;
			}
            if (blue.second->allocatedchart[Object::TRANSFORM])
			{
				delete blue.second->transform;
				blue.second->transform = nullptr;
			}
            if (blue.second->allocatedchart[Object::LINE])
			{
				delete blue.second->line;
				blue.second->line = nullptr;
			}
            if (blue.second->allocatedchart[Object::CIRCLE])
			{
				delete blue.second->circle;
				blue.second->circle = nullptr;
			}
            if (blue.second->allocatedchart[Object::RECTANGLE])
			{
				delete blue.second->rectangle;
				blue.second->rectangle = nullptr;
			}
            if (blue.second->allocatedchart[Object::SPRITETEXT])
			{
				delete blue.second->spritetext;
				blue.second->spritetext = nullptr;
			}
            if (blue.second->allocatedchart[Object::OBB])
			{
				delete blue.second->obb;
				blue.second->obb = nullptr;
			}
            delete blue.second;
			blue.second = nullptr;
        }

        ObjectIDMap.clear();
    }
    Object* ObjectFactory::FindObjectwithName(std::string& name) const
    {
        for (const auto obj : ObjectIDMap)
        {
            if (obj.second->objName == name)
                return obj.second;
        }
        return nullptr;
    }
    Object* ObjectFactory::FindObjectwithID(ObjectID id) const
    {
        for (const auto obj : ObjectIDMap)
        {
            if (obj.second->GetObjectID() == id)
                return obj.second;
        }
        return nullptr;
    }
}
