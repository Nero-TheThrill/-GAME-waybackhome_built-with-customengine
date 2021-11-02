/*
*  File Name : Circle.cpp
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: It includes information about circle collision state
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Circle.h"

namespace BLUE {
    Circle::Circle() : Component(ComponentType_CIRCLE)
    {
    }

    Circle::~Circle()
    {
    }

    void Circle::Init()
    {
        center = Point2D{ 0,0 };
        radius = 1;
    }

    Point2D Circle::GetPos() const
    {
        return center;
    }

    void Circle::SetPos(Point2D newPoint)
    {
        center.x = newPoint.x;
        center.y = newPoint.y;
    }

    float Circle::GetRadius() const
    {
        return radius;
    }

    void Circle::SetRadius(float newRadius)
    {
        radius = newRadius;
    }
}