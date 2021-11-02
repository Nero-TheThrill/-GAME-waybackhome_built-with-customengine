/*
*  File Name : Sprite.cpp
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Set the color, texture, animation or hud for the object.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Sprite.h"
#include "Object.h"
#include "Timer.h"
#include <iostream>

namespace BLUE
{

    Animation::Animation() :
        filpX(false),
        imageSize(1, 1),
        frameSize(1, 1),
        frameNumber(1, 1),
        currentFrame(1),
        speed((AnimationSpeed::range.x + AnimationSpeed::range.y) / 2.0f),
        timer(0.0f),
        needUpdate(true),
        activateAnimation(false)
    {
    }

    void Animation::SetImageSize(glm::ivec2 image_size)
    {
        imageSize = image_size;
    }

    void Animation::SetFrame(int x)
    {
        if (x <= 0)
        {
            std::cout << "Animation Error: You cannot divide image by " << x << "!\n";
            return;
        }
        frameSize = { imageSize.x / x, imageSize.y };
        frameNumber.x = x;
    }

    void Animation::SetFrame(int x, int y)
    {
        if (x <= 0 || y <= 0)
        {
            std::cout << "Animation Error: Cannot divide image by " << x << " x " << y << "!\n";
            return;
        }

        frameSize = { (imageSize.x / x), (imageSize.y / y) };
        frameNumber = { x, y };
    }

    void Animation::SetFrame(glm::ivec2 frame_image_size)
    {
        if (frame_image_size.x <= 0 || frame_image_size.x > imageSize.x || frame_image_size.y <= 0 || frame_image_size.y > imageSize.y)
        {
            std::cout << "Animation Error: Cannot set frame size to " << frame_image_size.x << " x " << frame_image_size.y << std::endl;
            return;
        }

        if ((imageSize.x % frame_image_size.x) || (imageSize.y %frame_image_size.y))
        {
            std::cout << "Animation Warning: The frame size is not proportional to the image size! : ";
            std::cout << "Image Size ( " << imageSize.x << ", " << imageSize.y;
            std::cout << " ), Frame Size ( " << frame_image_size.x << ", " << frame_image_size.y << " )\n";
        }

        frameSize = frame_image_size;
        frameNumber = { imageSize.x / frameSize.x, imageSize.y / frameSize.y };
    }

    void Animation::SetSpeed(float animation_speed)
    {
        if (animation_speed < 0.0f)
        {
            std::cout << "Animation Error: You cannot set animation speed under 0! (" << animation_speed << ")\n";
            return;
        }
        speed = animation_speed;
    }

    bool Animation::isAnimationActive() const
    {
        return activateAnimation;
    }

    void Animation::ActivateAnimation()
    {
        activateAnimation = true;
    }

    void Animation::DeactivateAnimation(int frame_number)
    {
        activateAnimation = false;
        currentFrame = frame_number;
    }

    bool Animation::needUpdateTextureCoordinate()
    {
        if (activateAnimation)
        {
            timer += AnimationSpeed::speed;
            if (timer > (AnimationSpeed::range.x + AnimationSpeed::range.y) / speed)
            {
                if (currentFrame < frameNumber.x * frameNumber.y)
                    currentFrame++;
                else
                    currentFrame = 1;
                needUpdate = true;
                timer = 0.0f;
            }
        }
        return activateAnimation && needUpdate;
    }

    void Animation::ConfirmUpdateCheckComplete()
    {
        needUpdate = false;
    }

    glm::vec2 Animation::GetReferencePoint()
    {
        return GetReferencePoint(currentFrame);
    }

    glm::vec2 Animation::GetFrameSize() const
    {
        const float x = static_cast<float>(frameSize.x) / static_cast<float>(imageSize.x);
        const float y = static_cast<float>(frameSize.y) / static_cast<float>(imageSize.y);
        return { x, y };
    }

    glm::ivec2 Animation::GetFrameNumber() const
    {
        return frameNumber;
    }

    float Animation::GetSpeed() const
    {
        return speed;
    }

    float Animation::GetTimer() const
    {
        return timer;
    }

    glm::vec2 Animation::GetReferencePoint(int frame_num)
    {
        if (frame_num <= 0 || frame_num > frameNumber.x * frameNumber.y)
        {
            std::cout << "Animation Error: Invalied frame number (" << frame_num << ") ";
            std::cout << " (Frame number should less than " << frameNumber.x << " x " << frameNumber.y << " = " << frameNumber.x * frameNumber.y << ")!\n";
            return { 0.0f, 0.0f };
        }

        needUpdate = true;

        const float x = (frame_num % frameNumber.x == 0) ?
            1.0f : static_cast<float>(frameSize.x * (frame_num % frameNumber.x)) / static_cast<float>(imageSize.x);
        const float y = (frame_num % frameNumber.x == 0) ?
            static_cast<float>(frameSize.y * static_cast<int>((frame_num - 1) / frameNumber.x)) / static_cast<float>(imageSize.y)
            : static_cast<float>(frameSize.y * static_cast<int>(frame_num / frameNumber.x)) / static_cast<float>(imageSize.y);
        return { x, y };
    }

    Sprite::Sprite() : Component(ComponentType_SPRITE), isHud(false), vertexType(VertexType::PositionColor), transform(nullptr)
    {
    }

    Sprite::~Sprite()
    {
    }

    void Sprite::Init()
    {
        if (GetOwner()->transform != nullptr)
            transform = (GetOwner()->transform);
        else
            std::cout << "Sprite Error: Cannot get transform!\n";

        mesh = CreateMesh::CreateBox();
    }

    void Sprite::SetTexture(const std::string &texture_path)
    {
        if (texture_path.empty())
            vertexType = VertexType::PositionColor;
        else
        {
            vertexType = VertexType::PositionTexture;

			if(texture == nullptr)
				texture = TEXTURE_MANAGER->GetTexture(texture_path);
			else if(texture->GetFilePath() != texture_path)
				texture = TEXTURE_MANAGER->GetTexture(texture_path);

            animation.SetImageSize(texture->GetTextureSize());
        }
    }

    void Sprite::SetColor(const Color& color)
    {
        mesh.SetColor(color);
    }

    void Sprite::SetToWiredBox()
    {
        vertexType = VertexType::PositionColor;
        mesh = CreateMesh::CreateWireBox();
    }

    Animation* Sprite::SetAnimation()
    {
        return &animation;
    }

    Mesh Sprite::GetMesh() const
    {
        return mesh;
    }

    glm::mat4 Sprite::GetTransformMatrix()
    {
        return transform->GetTransformMatrix();
    }

    float Sprite::GetDepth() const
    {
        if (transform->GetTranslation().z <= Depth::range.x)
            return 0.99f;
        if (transform->GetTranslation().z >= Depth::range.y)
            return 0.0f;

        return 1.0f - ((transform->GetTranslation().z - Depth::range.x) / (-Depth::range.x + Depth::range.y));
    }

    VertexType Sprite::GetVertexType() const
    {
        return vertexType;
    }

    Texture *Sprite::GetTexture()
    {
        /* Is animation active and need to change the texture coordiate */
        if (animation.needUpdateTextureCoordinate())
        {
            mesh.SetTextureCoordinate(animation.GetReferencePoint(), animation.GetFrameSize(), false);
            animation.ConfirmUpdateCheckComplete();
        }

        return texture;
    }

	glm::vec2 Sprite::GetPosition() const
	{
		return { transform->GetTranslation().x, transform->GetTranslation().y };
	}

	glm::vec2 Sprite::GetSize() const
	{
		return transform->GetScale();
	}

	void Sprite::ScaleHUDRepecttoResolution(glm::vec2 window_size)
	{
		hud.previous_resolution = hud.current_resolution;
		hud.current_resolution = window_size;
		hud.ratio = hud.current_resolution / hud.previous_resolution;
		transform->SetScale(transform->GetScale() * hud.ratio);
		transform->SetTranslation(transform->GetTranslation() * glm::vec3{ hud.ratio, 1.f });
	}
}
