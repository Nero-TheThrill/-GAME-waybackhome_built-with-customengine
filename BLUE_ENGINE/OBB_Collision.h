/*
*  File Name : OBB_Collision.h
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: to deal with OBB, OBB collision
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Component.h"
namespace BLUE
{
    class Circle;
    class Rectangle;
    class OBB_Collision : public Component
    {
    public:
        OBB_Collision();
        ~OBB_Collision() override;
        void Init() override;
        void update();

        bool GetCollisionState();
        void SetRectanlges(const Rectangle& rect1, const Rectangle& rect2);
        void ComputeAxis();


    private:
        bool isDead = false;
        // Corners of the box, where 0 is the lower left
        glm::vec2         first_corner[4];
        // Two edges of the box extended away from corner[0]
        glm::vec2         first_axis[2];
        double          first_origin[2];
        glm::vec2         second_corner[4];
        glm::vec2         second_axis[2];
        double          second_origin[2];
    };

}