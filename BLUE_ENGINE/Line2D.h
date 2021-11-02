/*
*  File Name : Line2D.h
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: It includes information about line state
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <glm/glm.hpp>
#include  "Component.h"

typedef glm::vec2 Point2D;

namespace BLUE
{
    class Line2D : public Component
    {
    public:
        Line2D();
        ~Line2D();
        void Init() override;

        Point2D GetStartPoint() const;
        void SetStartPoint(Point2D newPoint);
        Point2D GetEndPoint() const;
        void SetEndPoint(Point2D newPoint);

        float Length() const;
        float LengthSq() const;
    private:
        Point2D start;
        Point2D end;
    };
}