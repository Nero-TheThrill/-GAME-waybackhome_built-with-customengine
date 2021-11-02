/*
*  File Name : Object.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Components will be add in this class. 
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"Object.h"
#include <cassert>
#include "ObjectFactory.h"
#include <iostream>
#include "Graphics.h"

namespace BLUE
{
    Object::Object()
    {
        objectID = 0;
        objType = ObjectType_NULL;
        shapeType = ShapeType_NULL;
        transform = nullptr;
        sprite = nullptr;
        collision = nullptr;
        line = nullptr;
        circle = nullptr;
        rectangle = nullptr;
        rigidbody = nullptr;
        spritetext = nullptr;
        obb = nullptr;
        allocatedchart.clear();
        allocatedchart[SPRITE] = false;
        allocatedchart[COLLISION] = false;
        allocatedchart[RIGIDBODY] = false;
        allocatedchart[TRANSFORM] = false;
        allocatedchart[LINE] = false;
        allocatedchart[CIRCLE] = false;
        allocatedchart[RECTANGLE] = false;
        allocatedchart[SPRITETEXT] = false;
        allocatedchart[OBB] = false;
    }

    Object::~Object()
    {
        //delete the pointer of components that allocated
        /*       delete particle;
        particle = nullptr;
        delete transform;
        transform = nullptr;
        delete sprite;
        sprite = nullptr;
        delete collision;
        collision = nullptr;
        delete line;
        line = nullptr;
        delete circle;
        circle = nullptr;
        delete rectangle;
        rectangle = nullptr;*/
    }

    void Object::Init()
    {
        //call Init() function for all existing pointer
        if (transform != nullptr)
            transform->Init();

        if (sprite != nullptr)
            sprite->Init();

        if (collision != nullptr)
            collision->Init();

        if (line != nullptr)
            line->Init();

        if (circle != nullptr)
            circle->Init();

        if (rectangle != nullptr)
            rectangle->Init();

        if (rigidbody != nullptr)
            rigidbody->Init();

        if (spritetext != nullptr)
            spritetext->Init();

        if (obb != nullptr)
            obb->Init();

    }

    void Object::Destroy(Object* obj)
    {
        //std::cout << "Destroy called" << std::endl;
        OBJECT_FACTORY->Destroy(obj);
    }

    bool Object::AddComponent(Component* component)
    {
        //<example of using this function>
        //component_transform=dynamic_cast<Transform*>(component);
        component->SetOwner(this);
        switch (component->GetComponentType())
        {
        case ComponentType_SPRITE:
            sprite = dynamic_cast<Sprite*>(component);
            GRAPHICS->AddSprite(sprite);
            allocatedchart[SPRITE]= true;
            return true;
        case ComponentType_COLLISION:
            collision = dynamic_cast<Collision*>(component);
            allocatedchart[COLLISION] = true;
            return true;
        case ComponentType_RIGIDBODY:
            rigidbody = dynamic_cast<Rigidbody*>(component);
            allocatedchart[RIGIDBODY] = true;
            return true;
        case ComponentType_TRANSFORM:
            transform = dynamic_cast<Transform*>(component);
            allocatedchart[TRANSFORM] = true;
            return true;
        case ComponentType_LINE:
            line = dynamic_cast<Line2D*>(component);
            allocatedchart[LINE] = true;
            return true;
        case ComponentType_CIRCLE:
            circle = dynamic_cast<Circle*>(component);
            allocatedchart[CIRCLE] = true;
            return true;
        case ComponentType_RECTANGLE:
            rectangle = dynamic_cast<Rectangle*>(component);
            allocatedchart[RECTANGLE] = true;
            return true;
        case ComponentType_SPRITETEXT:
            spritetext = dynamic_cast<SpriteText*>(component);
            allocatedchart[SPRITETEXT] = true;
            return true;
        case ComponentType_OBB:
            obb = dynamic_cast<OBB_Collision*>(component);
            allocatedchart[OBB] = true;
            return true;
        default:
            assert(!"Can't add an unknown component");
            break;
        }
        return false;
    }

    Component* Object::GetComponent(ComponentType ctype)
    {//<example of using this function>
        switch (ctype)
        {
        case ComponentType_TRANSFORM:
            return transform;
        case ComponentType_SPRITE:
            return sprite;
        case ComponentType_COLLISION:
            return collision;
        case ComponentType_LINE:
            return line;
        case ComponentType_CIRCLE:
            return circle;
        case ComponentType_RECTANGLE:
            return rectangle;
        case ComponentType_RIGIDBODY:
            return rigidbody;
        case ComponentType_SPRITETEXT:
            return spritetext;
        case ComponentType_OBB:
            return obb;
        default:
            assert(!"Can't get an unknown component");
        }
        return nullptr;
    }

}
