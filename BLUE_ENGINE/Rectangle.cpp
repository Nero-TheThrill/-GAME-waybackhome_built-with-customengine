/*
*  File Name : Rectangle.cpp
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: It includes information about rectangle collision state
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include  "Object.h"
namespace BLUE
{
	Rectangle::Rectangle() : Component(ComponentType_RECTANGLE)
	{
	}
	Rectangle::~Rectangle()
	{
	}
	void Rectangle::Init()
	{
		transform = (Transform*)GetOwner()->GetComponent(ComponentType_TRANSFORM);
		size = glm::vec2(transform->GetScale().x, transform->GetScale().y);
		origin = glm::vec2(transform->GetTranslation().x - size.x / 2, transform->GetTranslation().y - size.y / 2);
	}
	void Rectangle::update()
	{
		transform = (Transform*)GetOwner()->GetComponent(ComponentType_TRANSFORM);
		if(!size_updated)
			size = glm::vec2(transform->GetScale().x, transform->GetScale().y);
		origin = glm::vec2(transform->GetTranslation().x-size.x/2, transform->GetTranslation().y - size.y / 2);
	}
	void Rectangle::update(glm::vec2 newSize)
	{
		transform = (Transform*)GetOwner()->GetComponent(ComponentType_TRANSFORM);
		if (size == newSize)
			size_updated = true;
		size = newSize;
		origin = glm::vec2(transform->GetTranslation().x - size.x / 2, transform->GetTranslation().y - size.y / 2);
	}
	Point2D Rectangle::GetOrigin() const
	{
		return origin;
	}

	void Rectangle::SetOrigin(Point2D newPoint)
	{
		origin.x = newPoint.x;
		origin.y = newPoint.y;
	}

	glm::vec2 Rectangle::GetSize() const
	{
		return size;
	}

	void Rectangle::SetSize(glm::vec2 newSize)
	{
		size.x = newSize.x;
		size.y = newSize.y;
	}

	glm::vec2 Rectangle::GetMin() const
	{
		glm::vec2 p1 = this->GetOrigin();
		glm::vec2 p2 = this->GetOrigin() + this->GetSize();

		return glm::vec2(glm::min(p1.x, p2.x), glm::min(p1.y, p2.y));
	}

	glm::vec2 Rectangle::GetMax() const
	{
		glm::vec2 p1 = this->GetOrigin();
		glm::vec2 p2 = this->GetOrigin() + this->GetSize();

		return glm::vec2(glm::max(p1.x, p2.x), glm::max(p1.y, p2.y));
	}
	Transform * Rectangle::GetTransform() const
	{
		return transform;
	}
}
