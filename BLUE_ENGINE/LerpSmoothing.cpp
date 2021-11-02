/*
*  File Name : LerpSmoothing.cpp
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: The camera follows the object with velocity.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "LerpSmoothing.h"

namespace BLUE
{
    Lerper::Lerper() : amount(0.025f), minvelocity(0.1f), maxvelocity(100.0f), acceleration(maxvelocity), previous_velocity(0.0f)
    {
    }

    float Lerper::LerpVelocity(float position, float target)
    {
        return (target - position) * amount;
    }

    LerpSmoothCamera::LerpSmoothCamera() : camera(nullptr), transform(nullptr)
    {
    }

    void LerpSmoothCamera::Init(Camera* cam, Transform* target_position)
    {
        camera = cam;
        transform = target_position;
    }

    void LerpSmoothCamera::Update()
    {
        const float x = lerper.Lerp(static_cast<float>(camera->GetPosition().x), static_cast<float>(transform->GetTranslation().x));
        const float y = lerper.Lerp(static_cast<float>(camera->GetPosition().y), static_cast<float>(transform->GetTranslation().y));

        camera->SetPosition({ x ,y });
    }

    float Lerper::Lerp(float position, float target)
    {
        float v = LerpVelocity(position, target);

        if (v == 0)
            return target;

        float temp = v;

        if (v*previous_velocity < 0 || abs(v) > abs(previous_velocity))
        {
            if ( /*v>0 && previous_velocity>=0 &&*/ v - previous_velocity > acceleration)
            {
                v = previous_velocity + acceleration;
            }
            else if ( /*v < 0 && previous_velocity <= 0 &&*/ previous_velocity - v > acceleration)
            {
                v = previous_velocity - acceleration;
            }
        }

        if (abs(v) < minvelocity)
        {
            v = (temp > 0) ? minvelocity : -minvelocity;
        }
        else if (abs(v) > maxvelocity)
        {
            v = (temp > 0) ? maxvelocity : -maxvelocity;
        }

        previous_velocity = v;
        position += v;

        if ((temp < 0 && position <= target) || (temp > 0 && position >= target))
        {
            position = target;
            //if(onReachedTarget != null) onReachedTarget();
        }
        return position;
    }

    void Lerper::SetMinimumVelocity(float min_velocity)
    {
        minvelocity = min_velocity;
    }

    void Lerper::SetMaximumVelocity(float max_velocity)
    {
        maxvelocity = max_velocity;
    }
}
