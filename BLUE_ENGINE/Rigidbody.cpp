/*
*  File Name : Rigidbody.cpp
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: It does position calculation with velocity, time, and acceleration.
*         And save previous position.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include "Rigidbody.h"
#include "Object.h"

namespace BLUE
{
    Rigidbody::Rigidbody() :Component(ComponentType_RIGIDBODY)
    {
    }

    Rigidbody::~Rigidbody()
    {
    }

    void Rigidbody::Init()
    {
        transform = GetOwner()->transform;
        position = { transform->GetTranslation().x, transform->GetTranslation().y };
        velocity = { 0,0 };
        acceleration = { 0,0 };
    }

    void Rigidbody::update(float dt)
    {
        position = { transform->GetTranslation().x, transform->GetTranslation().y };
        oldpos = position;
        position = position + glm::vec2({ velocity.x*dt,velocity.y*dt })
            + glm::vec2({ acceleration.x*dt*dt*0.5f, acceleration.y*dt*dt*0.5f });
        velocity = velocity + acceleration * dt;

        const float z = transform->GetTranslation().z;
        transform->SetTranslation({ position, z });
    }

    void Rigidbody::SetBodyType(RigidbodyType new_type)
    {
        type = new_type;
    }

    RigidbodyType Rigidbody::GetBodyType()
    {
        return type;
    }


}
