/*
*  File Name : ObjectFactory.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Managing all objects in the game.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include"ObjectType.h"
#include"System.h"
#include<map>
#include <string>
#include<vector>

namespace BLUE
{
    class Object;
    using ObjectID = unsigned;

    class ObjectFactory : public System
    {
    public:
        ObjectFactory();
        ~ObjectFactory();

        void Init() override {}
        void Update() override;

        void Destroy(Object* gameObject);

        void GiveObjectID(Object* gameObject);

        Object* CreateEmptyObject();

        int CountObjectType(ObjectType objType);

        void DestroyAllObjects();

        Object* FindObjectwithName(std::string& name) const;
        Object* FindObjectwithID(ObjectID id) const;

    private:
        ObjectID last_objectID;

        std::map<ObjectID, Object*> ObjectIDMap;
        std::vector<Object*> ObjectsToBeDeleted;
    };

    extern ObjectFactory* OBJECT_FACTORY;
}