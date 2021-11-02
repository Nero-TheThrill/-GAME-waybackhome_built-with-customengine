/*
*  File Name : CurbCameraMotion.cpp
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: The camera can move in limited size
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "CurbCameraMotion.h"
#include "ObjectFactory.h"
#include <iostream>
#include "Graphics.h"

namespace BLUE
{
    CurbCameraMotion::CurbCameraMotion() :
        line(nullptr),
        camera(nullptr),
        player(nullptr),
        center(0.0f, 0.0f),
        size(0.0f, 0.0f),
        player_size(0.f, 0.f),
        drawline(false),
        follow_object(false)
    {
    }

    void CurbCameraMotion::Update()
    {
        MoveCamera();
        DrawLine();
    }

	void CurbCameraMotion::Reset()
	{
		OBJECT_FACTORY->Destroy(line);
		line = nullptr;
	}

	void CurbCameraMotion::Init(Camera* camera_pointer, Transform *player_transform, float width, float height)
    {
        camera = camera_pointer;
        player = player_transform;
        player_size = player->GetScale() / 2.0f;
        size = { width / 2.0f, height / 2.0f };
        follow_object = true;
        InitLine();
    }

    void CurbCameraMotion::SetCenter(glm::vec2 center_position)
    {
        center = center_position;
    }

    void CurbCameraMotion::DrawLine(bool on)
    {
        drawline = on;
    }

    void CurbCameraMotion::FollowObject(bool follow)
    {
        follow_object = follow;
    }

    void CurbCameraMotion::DrawLine()
    {
        if (drawline)
        {
            if (line == nullptr)
                InitLine();

            if (camera != nullptr && line != nullptr)
            {
                static glm::ivec2 position(0.0f, 0.0f);

                // Move the boundary line's position only when the camera position has changed.
                if (position != camera->GetPosition())
                {
                    (line->transform)->SetTranslation({ center.x + camera->GetPosition().x, center.y + camera->GetPosition().y, Depth::range.y });
                    position = camera->GetPosition();
                }
            }
        }
        else
        {
            if (line != nullptr)
                OBJECT_FACTORY->Destroy(line);
        }
    }

    void CurbCameraMotion::InitLine()
    {
        if (line == nullptr)
        {
            line = OBJECT_FACTORY->CreateEmptyObject();
            line->SetName("line");
            line->AddComponent(new Transform());
            line->AddComponent(new Sprite());
            line->Init();
            (line->transform)->SetScale({ size.x * 2.0f, size.y * 2.0f });

            if (camera == nullptr)
            {
                (line->transform)->SetTranslation({ center.x, center.y, Depth::range.y });
                std::cout << "Camera Movement: Cannot get camera pointer!\n";
            }
            else
                (line->transform)->SetTranslation({ center.x + camera->GetPosition().x, center.y + camera->GetPosition().y, Depth::range.y });

            line->sprite->SetToWiredBox();
            line->sprite->SetColor({ 255, 0, 0, 255 });
            GRAPHICS->AddSprite(line->sprite);
        }
    }

    bool CurbCameraMotion::IsOutsideOfBoundary() const
    {
        const glm::vec3 position(player->GetTranslation());

        const glm::vec2 x(position.x - player_size.x, position.x + player_size.x);
        const glm::vec2 y(position.y - player_size.y, position.y + player_size.y);

        const glm::vec2 camera_position(camera->GetPosition());
        const glm::vec2 boundary_x(camera_position.x - size.x, camera_position.x + size.x);
        const glm::vec2 boundary_y(camera_position.y - size.y, camera_position.y + size.y);

        if (x.x < boundary_x.x || boundary_x.y < x.y)
            return false;
        if (y.x < boundary_y.x || boundary_y.y < y.y)
            return false;

        return true;
    }

    void CurbCameraMotion::MoveCamera() const
    {
        if (!follow_object)
            return;

        const glm::vec3 position(player->GetTranslation());
        const glm::vec2 x(position.x - player_size.x, position.x + player_size.x);
        const glm::vec2 y(position.y - player_size.y, position.y + player_size.y);

        glm::vec2 camera_position(camera->GetPosition());
        const glm::vec2 boundary_x(camera_position.x - size.x, camera_position.x + size.x);
        const glm::vec2 boundary_y(camera_position.y - size.y, camera_position.y + size.y);

        bool is_changed = false;

        if (x.x < boundary_x.x)
        {
            camera_position.x -= (boundary_x.x - x.x);
            is_changed = true;
        }
        else if (boundary_x.y < x.y)
        {
            camera_position.x += (x.y - boundary_x.y);
            is_changed = true;
        }

        if (y.x < boundary_y.x)
        {
            camera_position.y -= (boundary_y.x - y.x);
            is_changed = true;
        }
        else if (boundary_y.y < y.y)
        {
            camera_position.y += (y.y - boundary_y.y);
            is_changed = true;
        }

        if (is_changed)
            camera->SetPosition(camera_position);
    }

}
