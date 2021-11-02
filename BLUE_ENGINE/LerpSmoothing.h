/*
*  File Name : LerpSmoothing.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: The camera follows the object with velocity.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <glm/glm.hpp> /* glm::vec2 */
#include "Transform.hpp"
#include "Camera.h"

namespace BLUE
{
    class Lerper
    {
    public:
        Lerper();
        /* return the position by using lerp smooth*/
        float Lerp(float position, float target);

        /* Set the minimum/maximum velocity for moving object */
        void SetMinimumVelocity(float min_velocity);
        void SetMaximumVelocity(float max_velocity);
    private:
        float LerpVelocity(float position, float target);
        const float amount;
        float minvelocity, maxvelocity;
        float acceleration;

        float previous_velocity;
    };

    class LerpSmoothCamera
    {
    public:
        LerpSmoothCamera();

        void Init(Camera * cam, Transform * target_position);
        void Update();
        Lerper lerper;
    private:
    
        Camera* camera;
        Transform* transform;
    };
}
