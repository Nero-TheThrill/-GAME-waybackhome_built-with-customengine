/*
*  File Name : Graphics.cpp
*  Primary Author : Hyun Jina
*  Secondary Author : Choi Jinwoo
*  Brief: Display the sprite and text on the screen.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Graphics.h"
#include "SDL.h" /* Get window size */
#include "Object.h" /* GetOwner() */
#include "IMGUImanager.h" /* IMGUI */
#include <iostream>
#include <cassert>
#include "SpriteText.h"
#include "PauseScreen.h"

namespace BLUE
{
    Graphics* GRAPHICS = nullptr;

    namespace
    {
        /* Helper function to get GL_primitives */
        GLenum GetGLDrawMode(PointListType pointListType)
        {
            switch (pointListType)
            {
            case PointListType::Lines:
                return GL_LINES;
            case PointListType::LineStrip:
                return GL_LINE_STRIP;
            case PointListType::Triangles:
                return GL_TRIANGLES;
            case PointListType::TriangleStrip:
                return GL_TRIANGLE_STRIP;
            case PointListType::TriangleFan:
                return GL_TRIANGLE_FAN;
            default:
                return GL_POINTS;
            }
        }
    }

    glm::ivec2 WINDOW_INFORMATION::GetWindowSize()
    {
		int screen_width, screen_height;
		SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &screen_width, &screen_height);
		return { screen_width , screen_height };
    }

    glm::ivec2 WINDOW_INFORMATION::GetMousePos()
    {
        int screen_width, screen_height;
        SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &screen_width, &screen_height);
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        mouse_x -= screen_width / 2;
        mouse_y -= screen_height / 2;

        return { mouse_x, -mouse_y };
    }

    Graphics::Graphics()
    {
        std::cout << "Graphics constructor called" << std::endl;
        assert(GRAPHICS == nullptr && "GRAPHICS is already created");
        GRAPHICS = this;

        /* Set VAO and VBO 0 */
        for (int i = 0; i < numberOfVertexObject; i++)
        {
            vertexArrayObject[i] = 0;
            vertexBufferObject[i] = 0;
        }

        /* Clear all sprite maps */
        spriteMap.clear();
        spriteTextMap.clear();
        spriteDelete.clear();
        spriteTextDelete.clear();

		window_size = WINDOW_INFORMATION::GetWindowSize();
    }

    Graphics::~Graphics()
    {
        /* Delete VAO and VBO */
        glDeleteVertexArrays(numberOfVertexObject, vertexArrayObject);
        glDeleteBuffers(numberOfVertexObject, vertexBufferObject);

        /* Delete Shader */
        shaderPositionColor.Unuse();
        shaderPositionTexture.Unuse();
        shaderText.Unuse();
		shaderTextHUD.Unuse();
		shaderPositionTextureHUD.Unuse();
    }

    void Graphics::Init()
    {
        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        /* Initialize GLEW */
        if (glewInit() != GLEW_OK)
            std::cout << "Glew_Error: could not initialize the glew!" << std::endl;
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        //glClearDepth(1.0);

        /* Get window(screen) size for setting the camera matrix in camera class */
		GetWindowSize();
        camera.Init(static_cast<int>(window_size.x), static_cast<int>(window_size.y));

        /* Compile vertex and fragment shader */
        shaderPositionColor.CompileShaders(ShaderVertexType::SpriteColor);
        shaderPositionTexture.CompileShaders(ShaderVertexType::SpriteTexture);
        shaderText.CompileShaders(ShaderVertexType::SpriteText);
		shaderPositionTextureHUD.CompileShaders(ShaderVertexType::SpriteTexture_HUD);
		shaderTextHUD.CompileShaders(ShaderVertexType::SpriteText_HUD);

        /* Generate VAO and VBO */
        glGenVertexArrays(numberOfVertexObject, vertexArrayObject);
        glGenBuffers(numberOfVertexObject, vertexBufferObject);

        /* glVertexAttribPointer */
        DescribePositionColorVertexToOpenGL();
        DescribePositionTextureCoordinateVertexToOpenGL();

        /* Initialize IMGUI */
        if (ImGuiTurnOn)
            IMGUI_MANAGER->Init();

		is_toggled_fullscreen = true;
        PAUSE_SCREEN->SetFullScreen(&isFullScreen);
    }

	void Graphics::Update()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glBlendEquation(GL_FUNC_ADD/*GL_BLEND*/);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_F11))
		{
			isFullScreen = !isFullScreen;
			PAUSE_SCREEN->SetFullScreen(&isFullScreen);
		}

		if (is_toggled_fullscreen)
		{
			if (PAUSE_SCREEN->GetFullScreen())
			{
				SDL_SetWindowFullscreen(SDL_GL_GetCurrentWindow(), SDL_WINDOW_FULLSCREEN);
			}
			else
			{
				SDL_SetWindowFullscreen(SDL_GL_GetCurrentWindow(), 0);
			}
			is_toggled_fullscreen = false;
		}

        /* erase and draw sprite/text */
        DeleteSpriteAndTextInVector();
        DrawSpriteInSpriteMap();
        DrawSpriteTextInSpriteTextMap();

        ImGuiUpdate();

        SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
    }

    void Graphics::AddSprite(Sprite* sprite)
    {
        spriteMap[sprite->GetOwner()->GetObjectID()] = sprite;
    }

    void Graphics::DeleteSprite(Sprite* sprite)
    {
        spriteDelete.push_back(sprite);
    }

    void Graphics::DeleteAllSprites()
    {
        Update();
        spriteMap.clear();
    }

    void Graphics::AddSpriteText(SpriteText* sprite_text)
    {
        spriteTextMap[sprite_text->GetOwner()->GetObjectID()] = sprite_text;
    }

    void Graphics::DeleteSpriteText(SpriteText* sprite_text)
    {
        spriteTextDelete.push_back(sprite_text);
    }

    void Graphics::DeleteAllSpriteTexts()
    {
        Update();
        spriteTextMap.clear();
    }

    void Graphics::DeleteAll()
    {
        DeleteAllSpriteTexts();
        DeleteAllSprites();
    }

    Camera *Graphics::GetCamera()
    {
        return &camera;
    }

    void Graphics::TurnImGui(bool turn_on)
    {
        ImGuiTurnOn = turn_on;
    }

	glm::vec2 Graphics::GetWindowSize()
	{
		int screen_width, screen_height;
		SDL_GetWindowSize(SDL_GL_GetCurrentWindow(), &screen_width, &screen_height);
		window_size = { screen_width, screen_height };
		return { screen_width , screen_height };
	}

	void Graphics::SetWindowSize(glm::vec2 size)
	{
		window_size = size;
	}

    bool Graphics::InitAllTextures(int index) const
    {
    	static constexpr int size = static_cast<int>(Picture::Count);

		if (index >= size)
			return true;

		if(index == -1)
		{
			for (int i = 0; i < size; i++)
			{
				TEXTURE_MANAGER->GetTexture(T(static_cast<Picture>(i)));
			}
			return true;
		}

    	TEXTURE_MANAGER->GetTexture(T(static_cast<Picture>(index)));
    	return false;
    }

	void Graphics::ImGuiUpdate()
    {
        static Input input = Input::GetInstance();

        if (input.IsKeyTriggered(SDL_SCANCODE_INSERT))
        {
            ImGuiTurnOn = !ImGuiTurnOn;
        }

        if (ImGuiTurnOn)
        {
            if (IMGUI_MANAGER->Initialized())
                IMGUI_MANAGER->Update();
            else
                IMGUI_MANAGER->Init();
        }
        else if (IMGUI_MANAGER->Initialized())
        {
            IMGUI_MANAGER->ShutDown();
        }
    }

    void Graphics::DescribePositionColorVertexToOpenGL()
    {
        /* VertexType::PositionColor */
        glBindVertexArray(vertexArrayObject[static_cast<int>(VertexType::PositionColor)]);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[static_cast<int>(VertexType::PositionColor)]);
        /* position */
        const int position_attribute_location = shaderPositionColor.GetAttributeLocation("Position");
        const void* offset_in_struct = reinterpret_cast<const void*>(offsetof(PositionColor, position));
        glVertexAttribPointer(position_attribute_location, 2, GL_FLOAT, GL_FALSE, sizeof(PositionColor), offset_in_struct);
        glEnableVertexAttribArray(position_attribute_location);
        /* color */
        const int color_attribute_location = shaderPositionColor.GetAttributeLocation("Color");
        offset_in_struct = reinterpret_cast<const void*>(offsetof(PositionColor, color));
        glVertexAttribPointer(color_attribute_location, 4, GL_UNSIGNED_INT, GL_FALSE, sizeof(PositionColor), offset_in_struct);
        glEnableVertexAttribArray(color_attribute_location);
    }

    void Graphics::DescribePositionTextureCoordinateVertexToOpenGL()
    {
        /* VertexType::PositionTexture */
        glBindVertexArray(vertexArrayObject[static_cast<int>(ShaderType::TextureWithSoildColor)]);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[static_cast<int>(ShaderType::TextureWithSoildColor)]);
        /* position */
        const int position_attribute_location = shaderPositionTexture.GetAttributeLocation("Position");
        const void* offset_in_struct = reinterpret_cast<const void*>(offsetof(PositionTexture, position));
        glVertexAttribPointer(position_attribute_location, 2, GL_FLOAT, GL_FALSE, sizeof(PositionTexture), offset_in_struct);
        glEnableVertexAttribArray(position_attribute_location);
        /* texture */
        const int texture_coordinate_attribute_location = shaderPositionTexture.GetAttributeLocation("TextureCoordinate");
        offset_in_struct = reinterpret_cast<const void*>(offsetof(PositionTexture, textureCoordinate));
        glVertexAttribPointer(texture_coordinate_attribute_location, 2, GL_FLOAT, GL_FALSE, sizeof(PositionTexture), offset_in_struct);
        glEnableVertexAttribArray(texture_coordinate_attribute_location);
    }

	void Graphics::Draw(Mesh mesh, float depth, glm::mat4 view, glm::mat4 transform)
	{
		positionColor.clear();
		positionColor.reserve(mesh.GetPointCount());

		for (int point = 0; point < mesh.GetPointCount(); point++)
			positionColor.push_back({ mesh.GetPoint(point), mesh.GetColor(point) });

		shaderPositionColor.Use();
		shaderPositionColor.SendUniformVariable("view", view);
		shaderPositionColor.SendUniformVariable("transform", transform);
		shaderPositionColor.SendUniformVariable("depth", depth);

		glBindVertexArray(vertexArrayObject[static_cast<int>(VertexType::PositionColor)]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[static_cast<int>(VertexType::PositionColor)]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(PositionColor) *positionColor.size(), static_cast<const void*>(&positionColor[0]), GL_DYNAMIC_DRAW);

		glDrawArrays(GetGLDrawMode(mesh.GetPointListType()), 0, static_cast<GLsizei>(positionColor.size()));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Graphics::Draw(Mesh mesh, float depth, glm::mat4 view, glm::mat4 transform, Texture* texture)
	{
		positionTexture.clear();
		positionTexture.reserve(mesh.GetPointCount());
		texture->Bind();

		for (int index = 0; index < mesh.GetPointCount(); index++)
			positionTexture.push_back({ mesh.GetPoint(index), mesh.GetTextureCoordinate(index) });

		shaderPositionTexture.Use();
		shaderPositionTexture.SendUniformVariable("view", view);
		shaderPositionTexture.SendUniformVariable("transform", transform);
		shaderPositionTexture.SendUniformVariable("depth", depth);
		shaderPositionTexture.SendUniformVariable("texture_sample", 0);
		shaderPositionTexture.SendUniformVariable("color", mesh.GetColor(0).ColorToFloat());
		
		glBindVertexArray(vertexArrayObject[static_cast<int>(ShaderType::TextureWithSoildColor)]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[static_cast<int>(ShaderType::TextureWithSoildColor)]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(PositionTexture) *positionTexture.size(), static_cast<const void*>(&positionTexture[0]), GL_DYNAMIC_DRAW);

		glDrawArrays(GetGLDrawMode(mesh.GetPointListType()), 0, static_cast<GLsizei>(positionTexture.size()));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Graphics::DrawHUD(Mesh mesh, float depth, Texture* texture, glm::vec2 position, glm::vec2 size)
	{
		positionTexture.clear();
		positionTexture.reserve(mesh.GetPointCount());
		texture->Bind();
		const glm::vec2 scale = 2.f * size / window_size;
		const glm::vec2 pos = position / (window_size / 2.f);
		for (int index = 0; index < mesh.GetPointCount(); index++)
			positionTexture.push_back({ pos + mesh.GetPoint(index) * scale, mesh.GetTextureCoordinate(index) });
		shaderPositionTextureHUD.Use();
		shaderPositionTextureHUD.SendUniformVariable("depth", depth);
		shaderPositionTextureHUD.SendUniformVariable("texture_sample", 0);
		shaderPositionTextureHUD.SendUniformVariable("color", mesh.GetColor(0).ColorToFloat());

		glBindVertexArray(vertexArrayObject[static_cast<int>(ShaderType::TextureWithSoildColor)]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[static_cast<int>(ShaderType::TextureWithSoildColor)]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(PositionTexture) *positionTexture.size(), static_cast<const void*>(&positionTexture[0]), GL_DYNAMIC_DRAW);

		glDrawArrays(GetGLDrawMode(mesh.GetPointListType()), 0, static_cast<GLsizei>(positionTexture.size()));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Graphics::DrawText(SpriteText* text)
	{
		const int text_length = text->GetTextLength();

		const glm::mat4 view = camera.GetCameraMatrix();
		const float depth = text->GetDepth();

		for (int text_index = 0; text_index < text_length; text_index++)
		{
			Mesh mesh = text->GetMesh(text_index);

			positionTexture.clear();
			positionTexture.reserve(mesh.GetPointCount());

			for (int point = 0; point < mesh.GetPointCount(); point++)
				positionTexture.push_back({ mesh.GetPoint(point), mesh.GetTextureCoordinate(point) });

			text->BindTexture(text_index);

			shaderText.Use();
			shaderText.SendUniformVariable("view", view);
			shaderText.SendUniformVariable("text", 0);
			shaderText.SendUniformVariable("color", mesh.GetColor(0).ColorToFloat());
			shaderText.SendUniformVariable("depth", depth);

			glBindVertexArray(vertexArrayObject[static_cast<int>(ShaderType::TextureWithSoildColor)]);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[static_cast<int>(ShaderType::TextureWithSoildColor)]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(PositionTexture) *positionTexture.size(), &positionTexture.at(0));
			glDrawArrays(GetGLDrawMode(mesh.GetPointListType()), 0, static_cast<GLsizei>(positionTexture.size()));

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	void Graphics::DrawTextHUD(SpriteText* text)
	{
		const int text_length = text->GetTextLength();
		const float depth = text->GetDepth();		
		const glm::vec2 scale = (2.f / window_size);

		for (int text_index = 0; text_index < text_length; text_index++)
		{
			Mesh mesh = text->GetMesh(text_index);

			positionTexture.clear();
			positionTexture.reserve(mesh.GetPointCount());

			for (int index = 0; index < mesh.GetPointCount(); index++)
				positionTexture.push_back({ mesh.GetPoint(index) * scale, mesh.GetTextureCoordinate(index) });
			text->BindTexture(text_index);

			shaderTextHUD.Use();
			shaderTextHUD.SendUniformVariable("text", 0);
			shaderTextHUD.SendUniformVariable("color", mesh.GetColor(0).ColorToFloat());
			shaderTextHUD.SendUniformVariable("depth", depth);

			glBindVertexArray(vertexArrayObject[static_cast<int>(ShaderType::TextureWithSoildColor)]);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[static_cast<int>(ShaderType::TextureWithSoildColor)]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(PositionTexture) *positionTexture.size(), &positionTexture.at(0));
			glDrawArrays(GetGLDrawMode(mesh.GetPointListType()), 0, static_cast<GLsizei>(positionTexture.size()));

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}


	void Graphics::DrawSpriteInSpriteMap()
    {
        /* If there is sprite to be drawn, draw it */
        for (auto sprite : spriteMap)
        {
            if (sprite.second != nullptr)
            {
                const Mesh mesh = sprite.second->GetMesh();
                const float depth = sprite.second->GetDepth();

                const glm::mat4 view = camera.GetCameraMatrix();
                const glm::mat4 transform = sprite.second->GetTransformMatrix();

                switch (sprite.second->GetVertexType())
                {
                case VertexType::PositionColor:
                {
					Draw(mesh, depth, view, transform);
                }
                break;
                case VertexType::PositionTexture:
                {
					if (sprite.second->isHud)
					{
						sprite.second->ScaleHUDRepecttoResolution(window_size);
						DrawHUD(mesh, depth, sprite.second->GetTexture(), sprite.second->GetPosition(), sprite.second->GetSize());
					}
					else
						Draw(mesh, depth, view, transform, sprite.second->GetTexture());
                }
                break;
                default:
                    break;
                }
            }
        }
    }

    void Graphics::DrawSpriteTextInSpriteTextMap()
    {
        for (auto sprite_text : spriteTextMap)
        {
            if (sprite_text.second != nullptr)
            {
				if (!sprite_text.second->isHud)
					DrawText(sprite_text.second);
				else
				{
					sprite_text.second->ScaleHUDRepecttoResolution(window_size);
					DrawTextHUD(sprite_text.second);
				}
            }
        }
    }

    void Graphics::DeleteSpriteAndTextInVector()
    {
        /* Delete Sprite */
        for (auto sprite : spriteDelete)
        {
            if (sprite == nullptr)
                continue;

            const auto delete_object_ID = spriteMap.find(sprite->GetOwner()->GetObjectID());

            if (delete_object_ID != spriteMap.end())
            {
                //delete sprite;
                //sprite = nullptr;
                spriteMap.erase(delete_object_ID);
            }
        }
        spriteDelete.clear();

        /* Delete Sprite Text */
        for (auto sprite_text : spriteTextDelete)
        {
            if (sprite_text == nullptr)
                continue;

            const auto delete_object_ID = spriteTextMap.find(sprite_text->GetOwner()->GetObjectID());

            if (delete_object_ID != spriteTextMap.end())
            {
                //delete sprite_text;
                //sprite_text = nullptr;
                spriteTextMap.erase(delete_object_ID);
            }
        }
        spriteTextDelete.clear();
    }
}
