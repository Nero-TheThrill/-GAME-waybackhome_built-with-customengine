/*
*  File Name : Collision.h
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: to deal with AABB, Circle collision
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/


#include "Component.h"
namespace BLUE
{
    namespace ErrorReduction
    {
        static constexpr float calibration = -10;
    }
    class Circle;
    class Rectangle;
    class Collision : public Component
    {
    public:
        Collision();
        ~Collision() override;
        void Init() override;
        void update(const Circle& obj1, const Circle& obj2);
        void update(const Circle& obj1, const Rectangle& obj2);
        void update(const Rectangle& obj1, const Rectangle& obj2);

        bool GetCollisionState();
        bool GetInsideState();
        bool CircleCircle(const Circle& c1, const Circle& c2);
        bool CircleRectangle(const Circle& circle, const Rectangle& rectangle);
        bool RectangleRectangle(const Rectangle& rect1, const Rectangle& rect2);
        bool InsideRectangleRectangle(const Rectangle& rect1, const Rectangle& rect2);

    private:
        bool isDead = false;
        bool isInside = false;
    };
}