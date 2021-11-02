/*
*  File Name : OBB_Collision.cpp
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: to deal with OBB, OBB collision
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Rectangle.h"
#include "OBB_Collision.h"
#include <glm/glm.hpp>
namespace BLUE
{
    OBB_Collision::OBB_Collision() : Component(ComponentType_OBB)
    {
    }


    OBB_Collision::~OBB_Collision()
    {
    }
    void OBB_Collision::Init()
    {
    }
    void OBB_Collision::update()
    {
        for (int a = 0; a < 2; ++a) {

            double t = glm::dot(second_corner[0], first_axis[a]);

            // Find the extent of box 2 on axis a
            double tMin = t;
            double tMax = t;

            for (int c = 1; c < 4; ++c) {
                t = glm::dot(second_corner[c], first_axis[a]);

                if (t < tMin) {
                    tMin = t;
                }
                else if (t > tMax) {
                    tMax = t;
                }
            }

            // subtract off the origin
            // See if [tMin, tMax] intersects [0, 1]
            if ((tMin > 1 + first_origin[a]) || (tMax < first_origin[a])) {
                isDead = false;
                return;
            }
        }

		// other case check
        for (int a = 0; a < 2; ++a) {

            double t = glm::dot(first_corner[0], second_axis[a]);

            double tMin = t;
            double tMax = t;

            for (int c = 1; c < 4; ++c) {
                t = glm::dot(first_corner[c], second_axis[a]);

                if (t < tMin) {
                    tMin = t;
                }
                else if (t > tMax) {
                    tMax = t;
                }
            }

            if ((tMin > 1 + second_origin[a]) || (tMax < second_origin[a])) {
                isDead = false;
                return;
            }
        }

        isDead = true;
    }
    bool OBB_Collision::GetCollisionState()
    {
        return isDead;
    }
    void OBB_Collision::SetRectanlges(const Rectangle & rect1, const Rectangle & rect2)
    {
		//first
		glm::vec2 X1(cos(rect1.GetTransform()->GetRotation()), sin(rect1.GetTransform()->GetRotation()));
		glm::vec2 Y1(-sin(rect1.GetTransform()->GetRotation()), cos(rect1.GetTransform()->GetRotation()));

		X1 *= rect1.GetSize().x / 2;
		Y1 *= rect1.GetSize().y / 2;

		//first means first rectangle
		first_corner[0] = rect1.GetOrigin() - X1 - Y1;
		first_corner[1] = rect1.GetOrigin() + X1 - Y1;
		first_corner[2] = rect1.GetOrigin() + X1 + Y1;
		first_corner[3] = rect1.GetOrigin() - X1 + Y1;

		//second
		glm::vec2 X2(cos(rect2.GetTransform()->GetRotation()), sin(rect2.GetTransform()->GetRotation()));
		glm::vec2 Y2(-sin(rect2.GetTransform()->GetRotation()), cos(rect2.GetTransform()->GetRotation()));

		X2 *= rect2.GetSize().x / 2;
		Y2 *= rect2.GetSize().y / 2;

		//second means second rectangle
		second_corner[0] = rect2.GetOrigin() - X1 - Y1;
		second_corner[1] = rect2.GetOrigin() + X1 - Y1;
		second_corner[2] = rect2.GetOrigin() + X1 + Y1;
		second_corner[3] = rect2.GetOrigin() - X1 + Y1;

		ComputeAxis();
    }

    void OBB_Collision::ComputeAxis()
    {
		//first means first rectangle
		first_axis[0] = first_corner[1] - first_corner[0];
		first_axis[1] = first_corner[3] - first_corner[0];

		for (int a = 0; a < 2; ++a) {
			first_axis[a] /= glm::pow(glm::length(first_axis[a]), 2);
			first_origin[a] = glm::dot(first_corner[0], first_axis[a]);
		}

		//second means second rectangle
		second_axis[0] = second_corner[1] - second_corner[0];
		second_axis[1] = second_corner[3] - second_corner[0];

		for (int a = 0; a < 2; ++a) {
			second_axis[a] /= glm::pow(glm::length(second_axis[a]), 2);
			second_origin[a] = glm::dot(second_corner[0], second_axis[a]);
		}
    }
}