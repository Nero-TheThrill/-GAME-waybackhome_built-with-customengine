/*
*  File Name : Line2D.cpp
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: It includes information about line state
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Line2D.h"


namespace BLUE
{
    Line2D::Line2D() : Component(ComponentType_LINE)
    {
    }

    Line2D::~Line2D()
    {
    }

    void Line2D::Init()
    {
        start = Point2D{ 0,0 };
        end = Point2D{ 0,0 };
    }

    Point2D Line2D::GetStartPoint() const
    {
        return start;
    }

    void Line2D::SetStartPoint(Point2D newPoint)
    {
        start.x = newPoint.x;
        start.y = newPoint.y;
    }

    Point2D Line2D::GetEndPoint() const
    {
        return end;
    }

    void Line2D::SetEndPoint(Point2D newPoint)
    {
        end.x = newPoint.x;
        end.y = newPoint.y;
    }

    float Line2D::Length() const
    {
        return glm::length(end - start);
    }

    float Line2D::LengthSq() const
    {
        return glm::pow(glm::length(end - start), 2);
    }
}