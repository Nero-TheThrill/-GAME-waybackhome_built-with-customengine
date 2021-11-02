/*
*  File Name : Transform.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: It contains translation, scale, and rotation information.
*         And calculate matrix, find parent.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Transform.hpp"
#include <glm/gtc/matrix_transform.hpp> /* transform matrix */
#include "Rectangle.h"
#include <iostream>

namespace BLUE
{
	float Angle::DegreeToRadian(float degree)
	{
		return (degree * PI) / 180.0f;
	}

	float Angle::RadianToDegree(float radian)
	{
		return (radian * 180.0f) / PI;
	}

	Transform::Transform() :Component(ComponentType_TRANSFORM),
		translation{ 0.0f },
		scale(1.0f, 1.0f),
		rotation(0.0f),
		needUpdate(true)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Init()
	{
	}

	glm::vec3 Transform::GetTranslation() const
	{
		return translation;
	}

	void Transform::SetTranslation(const glm::vec3 new_translation)
	{
		needUpdate = true;
		translation = new_translation;
	}

	void Transform::SetPositionX(float x)
	{
		needUpdate = true;
		translation.x = x;
	}

	void Transform::SetPositionY(float y)
	{
		needUpdate = true;
		translation.y = y;
	}

	void Transform::SetPositionZ(float z)
	{
		needUpdate = true;
		translation.z = z;
	}

	glm::vec2 Transform::GetScale() const
	{
		return scale;
	}

	void Transform::SetScale(const glm::vec2 new_scale)
	{
		if (new_scale.x <= 0.0f || new_scale.y <= 0.0f)
		{
			std::cout << "Transform: Try to set scale less than zero!\n";
			std::cout << "What you want for scale: (" << new_scale.x << ", " << new_scale.y << ")\n";
			return;
		}
		scale = new_scale;
		needUpdate = true;
	}
	void Transform::SetScaleX(int new_scale)
	{
		needUpdate = true;
		scale.x = static_cast<glm::vec2::value_type>(new_scale);
	}

	void Transform::SetScaleY(int new_scale)
	{
		needUpdate = true;
		scale.y = static_cast<glm::vec2::value_type>(new_scale);
	}

	float Transform::GetRotation() const
	{
		return rotation;
	}

	void Transform::SetRotation(float new_rotation)
	{
		needUpdate = true;
		rotation = new_rotation;
	}

	glm::mat4 Transform::GetTransformMatrix()
	{
		UpdateTrasformMatrix();
		if (parent != nullptr)
		{
			calculatedMatrix = parent->GetTransformMatrix()*transformMatrix;
			return calculatedMatrix;
		}
		return transformMatrix;
	}

	void Transform::UpdateTrasformMatrix()
	{
		if (needUpdate)
		{
			transformMatrix = glm::mat4(1.0f);
			transformMatrix = glm::translate(transformMatrix, translation);
			transformMatrix = glm::rotate(transformMatrix, Angle::DegreeToRadian(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

			transformMatrix = glm::scale(transformMatrix, { scale , 0 });
			needUpdate = false;
		}
	}
}