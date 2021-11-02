/*
*  File Name : Graphics.h
*  Primary Author : Hyun Jina
*  Secondary Author : Choi Jinwoo
*  Brief: Display the sprite and text on the screen.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once

#include "System.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Sprite.h" /* VertexType */
#include <map>
#include <GL/glew.h>

namespace BLUE
{
    struct WINDOW_INFORMATION
    {
        static glm::ivec2 GetWindowSize();
        static glm::ivec2 GetMousePos();
    };

    using ObjectID = unsigned;

    struct PositionColor
    {
        glm::vec2 position;
        Color color;
    };

    struct PositionTexture
    {
        glm::vec2 position;
        glm::vec2 textureCoordinate;
    };

    class SpriteText;
    class Graphics : public System
    {
    public:
        Graphics();
        ~Graphics();
        void Init() override;
        void Update() override;

        /* Call these to draw/erase sprite/text on the screen */
        void AddSprite(Sprite* sprite);
        void DeleteSprite(Sprite* sprite);
        void DeleteAllSprites();

        void AddSpriteText(SpriteText *sprite_text);
        void DeleteSpriteText(SpriteText *sprite_text);
        void DeleteAllSpriteTexts();

        void DeleteAll();

        Camera* GetCamera();
        void TurnImGui(bool turn_on);

		glm::vec2 GetWindowSize();
		void SetWindowSize(glm::vec2 size);

		bool InitAllTextures(int index = -1) const;
		glm::vec2 window_size;

		bool is_toggled_fullscreen;
    private:
        void ImGuiUpdate();

        void DescribePositionColorVertexToOpenGL();
        void DescribePositionTextureCoordinateVertexToOpenGL();

		void Draw(Mesh mesh, float depth, glm::mat4 view, glm::mat4 transform);
		void Draw(Mesh mesh, float depth, glm::mat4 view, glm::mat4 transform, Texture* texture);
		void DrawHUD(Mesh mesh, float depth, Texture* texture, glm::vec2 position, glm::vec2 size);
		void DrawText(SpriteText* text);
		void DrawTextHUD(SpriteText* text);

        /*Draw Sprite by using mesh */
        std::map<ObjectID, Sprite*> spriteMap;
        std::map<ObjectID, SpriteText*> spriteTextMap;
        void DrawSpriteInSpriteMap();
        void DrawSpriteTextInSpriteTextMap();

        /* Check there is sprite which have to be removed */
        std::vector<Sprite*> spriteDelete;
        std::vector<SpriteText*> spriteTextDelete;
        void DeleteSpriteAndTextInVector();

        /* Shaders */
        Shader shaderPositionColor;
        Shader shaderPositionTexture;
        Shader shaderText;
		Shader shaderPositionTextureHUD;
		Shader shaderTextHUD;

        /* Variables for Open GL Stuff */
        static const int numberOfVertexObject = static_cast<int>(VertexType::Count);
        GLuint vertexArrayObject[numberOfVertexObject];
        GLuint vertexBufferObject[numberOfVertexObject];
        std::vector <PositionColor> positionColor{};
        std::vector <PositionTexture> positionTexture{};

        Camera camera;
        bool isFullScreen = true;
        bool ImGuiTurnOn = true;
    };

    extern Graphics* GRAPHICS;
}

