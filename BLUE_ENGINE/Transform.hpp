/*
*  File Name : Transform.hpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: It contains translation, scale, and rotation information.
*         And calculate matrix, find parent.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <glm/glm.hpp>
#include "Component.h"

namespace BLUE
{
	namespace Depth
	{
		/* range of z-axis */
		static constexpr glm::vec2 range(-1000.f, 1000.0f);
	}

	namespace Angle
	{
		/* Used for rotating object or camera */
		const float PI = 4.0f * std::atan(1.0f);
		float DegreeToRadian(float degree);
		float RadianToDegree(float radian);
	}

	class Transform : public Component
	{
	public:
		Transform();
		~Transform() override;

		void Init() override;

		/* Translation */
		glm::vec3 GetTranslation() const;
		void SetTranslation(const glm::vec3 new_translation);
		void SetPositionX(float x);
		void SetPositionY(float y);
		void SetPositionZ(float z);

		/* Scale */
		glm::vec2 GetScale() const;
		void SetScale(const glm::vec2 new_scale);
		void SetScaleX(int new_scale);
		void SetScaleY(int new_scale);

		/* Rotation */
		float GetRotation() const;
		void SetRotation(float new_rotation);

		/* Get Transform Matrix to send it to shader */
		glm::mat4 GetTransformMatrix();

		/* Find parent of it */
		Transform* parent = nullptr;

		/* Calculate Transform Matrix with parent Matrix*/
		glm::mat4 calculatedMatrix;
	private:
		/* Calculate the transform matrix when it need to update
		 *  When translation, ratation, or scale was changed
		 */
		void UpdateTrasformMatrix();

		glm::vec3 translation;
		glm::vec2 scale;
		float rotation;
		glm::mat4 transformMatrix;

		/* helper variable */
		bool needUpdate;
	};
}