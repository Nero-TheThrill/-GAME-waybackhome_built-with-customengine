/*
*  File Name : Collision.cpp
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: to deal with AABB, Circle collision
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Collision.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Line2D.h"
namespace BLUE
{
    Collision::Collision() : Component(ComponentType_COLLISION)
    {
    }

    Collision::~Collision()
    {
    }
    void Collision::Init()
    {
    }
    bool Collision::GetCollisionState()
    {
        return isDead;
    }
    bool Collision::GetInsideState()
    {
        return isInside;
    }

	// update Circle vs Circle collision state
	void Collision::update(const Circle & obj1, const Circle & obj2)
	{
		isDead = (CircleCircle(obj1, obj2));
	}

	// update Circle vs AABB collision state
	void Collision::update(const Circle & obj1, const Rectangle & obj2)
	{
		isDead = (CircleRectangle(obj1, obj2));
	}

	// update AABB vs AABB collision state
	void Collision::update(const Rectangle & obj1, const Rectangle & obj2)
	{
		isDead = RectangleRectangle(obj1, obj2);
		isInside = InsideRectangleRectangle(obj1, obj2);
	}

	// Circle vs Circle collision check
	bool Collision::CircleCircle(const Circle & c1, const Circle & c2)
	{
		Line2D line;
		line.SetStartPoint(c1.GetPos());
		line.SetEndPoint(c2.GetPos());
		float radiusSum = c1.GetRadius() + c2.GetRadius();
		return line.LengthSq() <= pow(radiusSum, 2);
	}

	// Circle vs AABB collision check
	bool Collision::CircleRectangle(const Circle & circle, const Rectangle & rectangle)
	{
		glm::vec2 min = rectangle.GetMin();
		glm::vec2 max = rectangle.GetMax();

		Point2D closestPos = circle.GetPos();
		if (closestPos.x < min.x) { closestPos.x = min.x; }
		else if (closestPos.x > max.x) { closestPos.x = max.x; }
		if (closestPos.y < min.y) { closestPos.y = min.y; }
		else if (closestPos.y > max.y) { closestPos.y = max.y; }

		Line2D line;
		line.SetStartPoint(circle.GetPos());
		line.SetEndPoint(closestPos);
		return  line.LengthSq() <= pow(circle.GetRadius(), 2);
	}

	// AABB vs AABB collision check
	bool Collision::RectangleRectangle(const Rectangle & rect1, const Rectangle & rect2)
	{
		glm::vec2 aMin = rect1.GetMin();
		glm::vec2 aMax = rect1.GetMax();
		glm::vec2 bMin = rect2.GetMin();
		glm::vec2 bMax = rect2.GetMax();

		bool overX = ((bMin.x <= aMax.x) && (aMin.x <= bMax.x));
		bool overY = ((bMin.y <= aMax.y) && (aMin.y <= bMax.y));
		return overX && overY;
	}

	// To avoid returning to an old point even if it touches the surface area and 
	// fix wall bugs that does not move when player touches.  
	bool Collision::InsideRectangleRectangle(const Rectangle & rect1, const Rectangle & rect2)
	{
		glm::vec2 aMin = rect1.GetMin();
		glm::vec2 aMax = rect1.GetMax();
		glm::vec2 bMin = rect2.GetMin();
		glm::vec2 bMax = rect2.GetMax();
		bool overX = ((bMin.x - aMax.x < ErrorReduction::calibration) && (aMin.x - bMax.x < ErrorReduction::calibration));
		bool overY = ((bMin.y - aMax.y < ErrorReduction::calibration) && (aMin.y - bMax.y < ErrorReduction::calibration));
		return overX && overY;
	}
}