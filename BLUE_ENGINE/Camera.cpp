/*
*  File Name : Camera.cpp
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief:	OpenGL window(-1.0 to 1.0) to viewport(screen width * height)
                        Can set the position, rotation, and zooming.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace BLUE
{
    namespace CameraConstant
    {
        static constexpr glm::vec2 zoom_range(0.1f, 10.0f);
    }

    FollowObject::FollowObject() :dofollow(false), transform(nullptr), distance(0.0f)
    {
    }

    Camera::Camera() :
        screenSize(1280.0f, 720.f),
        orthoMatrix(1),
        position(0, 0),
        rotation(0.0f),
        zoom(1.0f),
        cameraMatrix(1.0f),
        needUpdate(true),
        isChange(true)
    {
    }

    void Camera::Init(int screen_width, int screen_height)
    {
        SetScreenSize({ screen_width, screen_height });
        // Set orthogonal matrix for camera
        orthoMatrix = glm::ortho(-screenSize.x / 2.f, screenSize.x / 2.f, -screenSize.y / 2.f, screenSize.y / 2.f);
    }

    void Camera::SetScreenSize(const glm::ivec2 new_screen_size)
    {
        screenSize = new_screen_size;
    }

    glm::ivec2 Camera::GetScreenSize() const
    {
        return screenSize;
    }

    void Camera::SetPosition(const glm::ivec2& new_position)
    {
        position = new_position;
        needUpdate = true;
    }

    glm::ivec2 Camera::GetPosition() const
    {
        return position;
    }

    void Camera::SetZoom(const float& new_zoom)
    {
        if (new_zoom <= CameraConstant::zoom_range.x || new_zoom > CameraConstant::zoom_range.y)
        {
            std::cout << "Camera Zoom: The value you set = " << new_zoom << " (Zoom value has to be between " << CameraConstant::zoom_range.x << " and " << CameraConstant::zoom_range.y << ")!\n";
            return;
        }

        zoom = new_zoom;
        const float ratio = 1 / zoom;
        orthoMatrix = glm::ortho(-screenSize.x / 2.f *ratio, screenSize.x / 2.f *ratio, -screenSize.y / 2.f *ratio, screenSize.y / 2.f *ratio);
        needUpdate = true;
    }

    float Camera::GetZoom() const
    {
        return zoom;
    }

    void Camera::SetRotation(const float& new_rotation)
    {
        rotation = new_rotation;

        needUpdate = true;
    }

    float Camera::GetRotation() const
    {
        return rotation;
    }

    void Camera::ResetCamera()
    {
        orthoMatrix = glm::ortho(-screenSize.x / 2.f, screenSize.x / 2.f, -screenSize.y / 2.f, screenSize.y / 2.f);
        rotation = 0.0f;
        zoom = 1.0f;
        position = { 0.0f, 0.0f };
        needUpdate = true;
    }

    glm::mat4 Camera::GetCameraMatrix()
    {
        UpdateCameraMatrix();
        return cameraMatrix;
    }

    void Camera::UpdateCameraMatrix()
    {
        // Is camera following the object?
        if (follow.dofollow)
        {
            FollowingMovement();
        }

        // Does camera screen shake function turn on?
        if (screenshake.doscreenshake)
        {
            ScreenShakeEffect();
        }

        /* Only update the camera when it needs to update
        * (When the camera's size or position has been changed) */
        if (needUpdate)
        {
            cameraMatrix = orthoMatrix;

            const glm::vec3 camera_rotation_direction = { 0.0f, 0.0f, 1.0f };
            cameraMatrix = glm::rotate(cameraMatrix, Angle::DegreeToRadian(rotation), camera_rotation_direction);

            const glm::vec3 camera_translate(-position.x, -position.y, 0.0f);
            cameraMatrix = glm::translate(cameraMatrix, camera_translate);

            needUpdate = false;
            isChange = true;
        }
    }

    bool Camera::IsCameraChanges() const
    {
        return isChange;
    }

    void Camera::ConfirmCameraChangeCompleted()
    {
        isChange = false;
    }

    void Camera::ControlCamera()
    {
        // Rotation
        const float r = 5.0f;
        if (input.IsKeyPressed(SDL_SCANCODE_KP_9))
            SetRotation(GetRotation() + r);
        if (input.IsKeyPressed(SDL_SCANCODE_KP_7))
            SetRotation(GetRotation() - r);

        // Move
        const float speed = 10.0f;
        if (input.IsKeyPressed(SDL_SCANCODE_KP_8))
            SetPosition({ GetPosition().x , GetPosition().y + speed });
        if (input.IsKeyPressed(SDL_SCANCODE_KP_4))
            SetPosition({ GetPosition().x - speed , GetPosition().y });
        if (input.IsKeyPressed(SDL_SCANCODE_KP_6))
            SetPosition({ GetPosition().x + speed , GetPosition().y });
        if (input.IsKeyPressed(SDL_SCANCODE_KP_2))
            SetPosition({ GetPosition().x , GetPosition().y - speed });

        // Zoom
        const float z = 0.1f;
        if (input.IsKeyPressed(SDL_SCANCODE_KP_3))
            SetZoom(GetZoom() + z);
        if (input.IsKeyPressed(SDL_SCANCODE_KP_1))
            SetZoom(GetZoom() - z);

        if (input.IsKeyPressed(SDL_SCANCODE_KP_5))
            ResetCamera();
    }

    void Camera::ScreenShakeEffectTurnOn(bool turn_on, int duration, float intensity)
    {
        screenshake.doscreenshake = turn_on;

        if (turn_on)
        {
            screenshake.duration = duration;
            screenshake.intensity = intensity;
            screenshake.camera_position = position;
        }
    }

    void Camera::ScreenShakeEffect()
    {
        static int time = 0;

        if (time < screenshake.duration)
        {
            /*switch(time % 25)
            {
            case 0:
                    SetRotation(screenshake.intensity/2.0f);
                    break;
            case 10:
                    SetRotation(-screenshake.intensity/2.0f);
                    break;
            case 5:
            case 15:
                    SetRotation(0.0f);
                    break;
            default:
                    break;
            }*/

            /*switch (time % 25)
            {
            case 0:
                    SetZoom(1.05f);
                    break;
            case 10:
                    SetZoom(0.95f);
                    break;
            case 5:
            case 15:
                    SetZoom(1.0f);
                    break;
            default:
                    break;
            }*/

            switch (time % 40)
            {
            case 0:
                SetPosition({ position.x, position.y + screenshake.intensity / 2.0f });
                break;
            case 10:
                SetPosition({ position.x, position.y - screenshake.intensity / 2.0f });
                break;
            case 20:
                SetPosition({ position.x + screenshake.intensity, position.y });
                break;
            case 30:
                SetPosition({ position.x - screenshake.intensity, position.y });

                break;
            default:
                break;
            }

            time += 1;
        }
        else
        {
            time = 0;
            screenshake.doscreenshake = false;
            //SetPosition(screenshake.camera_position);
        }
    }

    void Camera::SetFollowObject(Transform* transform)
    {
        follow.transform = transform;

        if (transform == nullptr)
        {
            follow.dofollow = false;
            return;
        }
        else
            follow.dofollow = true;

        follow.distance = { position.x - follow.transform->GetTranslation().x, position.y - follow.transform->GetTranslation().y };
    }

    void Camera::FollowingMovement()
    {
        SetPosition({ follow.transform->GetTranslation().x + follow.distance.x, follow.transform->GetTranslation().y + follow.distance.y });
    }

}

