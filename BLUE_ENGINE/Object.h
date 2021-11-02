/*
*  File Name : Object.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: Components will be add in this class. 
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include"ComponentType.h"

#include "ObjectType.h"
#include<string>
#include"Component.h"
#include "Transform.hpp"
#include "Sprite.h"
#include "Collision.h"
#include "Line2D.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Rigidbody.h"
#include "SpriteText.h"
#include "OBB_Collision.h"
#include "ControllerType.h"

namespace BLUE
{
    using ObjectID = unsigned;

    class ObjectFactory;
    class Component;

    class Object
    {
    public:
        friend class ObjectFactory;

        Object();
        ~Object();

        void Init();
        void Destroy(Object* obj);

        bool AddComponent(Component* component);
        Component* GetComponent(ComponentType ctype);


        ObjectID GetObjectID()
        {
            return objectID;
        }
        void SetObjectID(ObjectID objID)
        {
            objectID = objID;
        }
        ShapeType GetShapeType()
        {
            return shapeType;
        }
        void SetShapeType(ShapeType shapetype)
        {
            shapeType = shapetype;
        }
        ObjectType GetObjectType()
        {
            return objType;
        }
        void SetObjectType(ObjectType objtype)
        {
            objType = objtype;
        }
        void SetName(const std::string& name)
        {
            objName = name;
        }
        std::string GetName() const
        {
            return objName;
        }
        std::string objName = "";
        glm::vec2 direction;
		ControllerType item_type;
//    private:
        enum allocated
        {
            TRANSFORM,
            SPRITE,
            COLLISION,
            LINE,
            CIRCLE,
            RECTANGLE,
            RIGIDBODY,
            SPRITETEXT,
            OBB
        };
        std::map<allocated, bool> allocatedchart;
        ObjectID objectID;
        ObjectType objType;
        ShapeType shapeType;
        Sprite* sprite;
        Transform* transform;
        Collision* collision;
        Line2D* line;
        Circle* circle;
        Rectangle* rectangle;
        Rigidbody* rigidbody;
        SpriteText* spritetext;
        OBB_Collision* obb;
    };

}
