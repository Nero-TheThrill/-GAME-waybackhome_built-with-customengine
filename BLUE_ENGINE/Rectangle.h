/*
*  File Name : Rectangle.h
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: It includes information about rectangle collision state
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include <glm/glm.hpp>
#include  "Component.h"
#include "Transform.hpp"
typedef glm::vec2 Point2D;

namespace BLUE
{
	class Rectangle: public Component
	{
	public:
		Rectangle();
		~Rectangle();

		void Init() override;
		void update();
		void update(glm::vec2 newSize);
		//origin is min
		Point2D GetOrigin() const;
		void SetOrigin(Point2D newPoint);
		//size is min to max vector
		glm::vec2 GetSize() const;
		void SetSize(glm::vec2 newSize);

		glm::vec2 GetMin() const;
		glm::vec2 GetMax() const;

		Transform* GetTransform() const;

	private:
		Point2D origin;
		glm::vec2 size;
		bool size_updated = false;

		Transform* transform;
	};
}