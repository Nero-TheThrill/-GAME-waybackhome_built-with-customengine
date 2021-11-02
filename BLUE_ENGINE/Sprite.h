/*
*  File Name : Sprite.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Set the color, texture, animation or hud for the object.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Transform.hpp"
#include "Texture.h"
#include "Mesh.h"
#include "Hud.h"

namespace BLUE
{
    enum class VertexType : int
    {
        PositionColor,
        PositionTexture,
        Count
    };

    enum class ShaderType : int
    {
        SolidColor,
        TextureWithSoildColor,
        Count
    };

    namespace AnimationSpeed
    {
        /* range of animation's speed */
        static const float speed = 0.3f;
        static const glm::vec2 range(0.0f, 100.0f);
    }

    /* For the animated sprite */
    class Animation
    {
    public:
        Animation();
        /* Use this in the SetTexture() in sprite class to know the image's size */
        void SetImageSize(glm::ivec2 image_size);

        /* Set frame by number or size */
        void SetFrame(int x = 1);
        void SetFrame(int x, int y);
        void SetFrame(glm::ivec2 frame_image_size);

        /* Set Speed of animation */
        void SetSpeed(float animation_speed);

        /* Activate or Deactivate animation */
        bool isAnimationActive() const;
        void ActivateAnimation();
        void DeactivateAnimation(int frame_number = 1);

        /* functions to set the texture coodinate in mesh class */
        bool needUpdateTextureCoordinate();
        // this function must be called after needUpdate...function is called
        void ConfirmUpdateCheckComplete();
        glm::vec2 GetReferencePoint();
        glm::vec2 GetFrameSize() const;

        /* For IMGUI */
        glm::ivec2 GetFrameNumber() const;
        float GetSpeed() const;
        float GetTimer() const;

        bool filpX;
    private:
        glm::vec2 GetReferencePoint(int frame_num);

        glm::ivec2 imageSize;
        glm::ivec2 frameSize;
        glm::ivec2 frameNumber;
        int currentFrame;

        /* Speed values */
        float speed;
        float timer;

        // Does the texture coordinate has to be changed?
        bool needUpdate;
        bool activateAnimation;
    };

    class Sprite : public Component
    {
    public:
        Sprite();
        ~Sprite() override;

        void Init() override;

        /* Initialize function */
        void SetTexture(const std::string &texture_path = "");
        void SetColor(const Color& color);

        void SetToWiredBox();

        /* Allows to set the values for animation */
        Animation * SetAnimation();

        /* functions to draw sprite in graphics class */
        Mesh GetMesh() const;
        glm::mat4 GetTransformMatrix();
        float GetDepth() const;
        VertexType GetVertexType() const;
        Texture *GetTexture();
		glm::vec2 GetPosition() const;
		glm::vec2 GetSize() const;

		void ScaleHUDRepecttoResolution(glm::vec2 window_size);

        bool isHud;
    private:
        /* vertices and color */
        Mesh mesh;
        VertexType vertexType;

        /* Texture and Animation*/
        Texture* texture;
        Animation animation;
		HUD hud;

        /* transform information */
        Transform* transform;
    };
}
