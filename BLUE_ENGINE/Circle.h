/*
*  File Name : Circle.h
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: It includes information about circle collision state
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include <glm/glm.hpp>
#include  "Component.h"
typedef glm::vec2 Point2D;

namespace BLUE
{
    class Circle : public Component
    {
    public:
        Circle();
        ~Circle();

        void Init() override;
        Point2D GetPos() const;
        void SetPos(Point2D newPoint);
        float GetRadius() const;
        void SetRadius(float newRadius);

    private:
        Point2D center;
        float radius;
    };
}