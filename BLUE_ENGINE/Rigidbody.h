/*
*  File Name : Rigidbody.h
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: It does position calculation with velocity, time, and acceleration.
*         And save previous position.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/


#pragma once
#include "Component.h"
#include "Transform.hpp"

namespace BLUE
{
    enum class RigidbodyType : int
    {
		None,
        Dynamic,
        Static,
        Count
    };
    class Rigidbody : public Component
    {
    public:
        Rigidbody();
        ~Rigidbody() override;
        void Init() override;
        void update(float dt);

        void SetBodyType(RigidbodyType new_type);
        RigidbodyType GetBodyType();

        glm::vec2 velocity;
        glm::vec2 oldpos;
        Transform* transform;
    private:
        RigidbodyType type = RigidbodyType::Dynamic;
        glm::vec2 position;
        glm::vec2 acceleration;
    };
}
