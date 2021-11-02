/*
*  File Name : SpriteText.cpp
*  Primary Author : Hyun Jina
*  Secondary Author : 
*  Brief: Display the text on the screen.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "SpriteText.h"
#include <GL/glew.h> /* Texture */
#include "Object.h"  /* Get transform */
#include <algorithm> /* sort, erase string */
#include <iostream>

namespace BLUE
{
    Character::Character() : size(0, 0), bearing(0, 0), advance(0)
    {
    }

    Character::Character(const Character& character) : texture(character.texture), size(character.size), bearing(character.bearing), advance(character.advance)
    {
    }

    Character &Character::operator=(const Character& character)
    {
        texture = character.texture;
        size = character.size;
        bearing = character.bearing;
        advance = character.advance;
        return *this;
    }

    SpriteText::SpriteText() : Component(ComponentType_SPRITETEXT), pixel_size(48), has_different_color(false), transform(nullptr)
    {
        characters.clear();
        meshes.clear();
		color.clear();
		color.push_back({ 0, 0, 0 });
    }

    SpriteText::~SpriteText()
    {
    }

    void SpriteText::Init()
    {
        transform = dynamic_cast<Transform*>(GetOwner()->GetComponent(ComponentType_TRANSFORM));
    }

    void SpriteText::SetFontPath(const std::string& font_path)
    {
        fontPath = font_path;
        //LoadFromFile(font_path);
    }

    void SpriteText::SetText(const std::string& text_string)
    {
        if (text != text_string)
        {
            text = text_string;

			// check: new character should be loaded
            bool needNewCharacter = false;
            for (std::string::const_iterator c = text.begin(); c != text.end(); ++c)
            {
                if (!characters.count(*c))
                {
                    needNewCharacter = true;
                    break;
                }
            }

            if (needNewCharacter)
                LoadFromFile(fontPath);
            SetMeshes();
        }
    }

    void SpriteText::SetColor(const Color& text_color)
    {
        color.front() = text_color;
    }

	void SpriteText::SetColor(const Color& text_color, int index)
	{
		if (has_different_color == false)
			EachLetterHasDifferentColor(true);

		if(index > static_cast<int>(text.length()))
		{
			std::cout << "Sprite Text Error: There isn't " << index << " th letter in text (Text Length: " << text.length() << ")\n";
			return;
		}

		if(color.size() != text.length())
		{
			while (color.size() == text.length())
				color.push_back({ 0, 0, 0 });
		}

		color.at(index - 1) = text_color;
		meshes.at(index - 1).SetColor(color.at(index - 1));
	}

	void SpriteText::EachLetterHasDifferentColor(bool each_has_different_color)
	{
		has_different_color = each_has_different_color;

		const Color text_color = color.at(0);		
		if(has_different_color)
		{
			for (int i = 1; i < static_cast<int>(text.length()); i++)
				color.push_back(text_color);
		}
		else
		{
			for(Mesh mesh : meshes)
			{
				mesh.SetColor(text_color);
			}
			color.clear();
			color.push_back(text_color);
		}
	}

	int SpriteText::GetTextLength() const
    {
        if (static_cast<int>(text.length()) != static_cast<int>(meshes.size()))
        {
            std::cout << "Sprite Text Error: text length and meshes size is different!\n";
            std::cout << "Text Length = " << text.length() << "  meshes.size() = " << meshes.size() << "!\n";
            return 0;
        }
        return static_cast<int>(text.length());
    }

    Mesh SpriteText::GetMesh(int index) const
    {
        if (index < 0 || index >= static_cast<int>(meshes.size()))
        {
            std::cout << "Sprite Text Error: Invalid index to access the mesh ( " << index << " )!\n";
            return meshes.front();
        }
        return meshes.at(index);
    }

    float SpriteText::GetDepth() const
    {
		if (transform->GetTranslation().z <= Depth::range.x)
			return 0.99f;
		if (transform->GetTranslation().z >= Depth::range.y)
			return 0.0f;

		return 1.0f - ((transform->GetTranslation().z - Depth::range.x) / (-Depth::range.x + Depth::range.y));
    }

    void SpriteText::BindTexture(int index)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, *GetTexture(index));
    }

	void SpriteText::ScaleHUDRepecttoResolution(glm::vec2 window_size)
	{
		hud.previous_resolution = hud.current_resolution;
		hud.current_resolution = window_size;
		hud.ratio = hud.current_resolution / hud.previous_resolution;
		transform->SetScale(transform->GetScale() * hud.ratio);
		transform->SetTranslation(transform->GetTranslation() * glm::vec3{ hud.ratio, 1.f });
	}

	glm::vec2 SpriteText::GetPosition() const
	{
		return { transform->GetTranslation().x, transform->GetTranslation().y };
	}

	glm::vec2 SpriteText::GetSize() const
	{
		return transform->GetScale();
	}

	void SpriteText::LoadFromFile(const std::string& font_path)
    {
        FT_Library ft_library;
        if (FT_Init_FreeType(&ft_library))
        {
            std::cout << "Text Error: Couldn't initialize the freetype!\n";
            return;
        }

        FT_Face face;
        if (FT_New_Face(ft_library, font_path.c_str(), 0, &face))
        {
            std::cout << "Text Error: Failed to load font from " << font_path.c_str() << "!\n";
            FT_Done_FreeType(ft_library);
            return;
        }

        FT_Set_Pixel_Sizes(face, static_cast<FT_UInt>(pixel_size), 0);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        std::string newChar = text;
        newChar.erase(std::unique(newChar.begin(), newChar.end()), newChar.end());
        for (std::string::const_iterator c = newChar.begin(); c != newChar.end(); ++c)
        {
            if (!characters.count(*c))
                SetCharacter(face, *c);
        }

        FT_Done_Face(face);
        FT_Done_FreeType(ft_library);
    }

    void SpriteText::SetCharacter(const FT_Face& face, char c)
    {
		// Load each characters from ttf file
        if (FT_Load_Char(face, c, FT_LOAD_RENDER /*| FT_LOAD_NO_BITMAP*/))
        {
            std::cout << "Text Error: Failed to load glyph " << c << " !\n";
            return;
        }
        Character character;
        GenerateTexture(&character.texture, { face->glyph->bitmap.width, face->glyph->bitmap.rows }, face->glyph->bitmap.buffer);
        character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        character.advance = face->glyph->advance.x;

        characters.insert(std::make_pair(c, character));
    }

    void SpriteText::SetMeshes()
    {
        meshes.clear();
        const glm::vec2 scale = transform->GetScale() / pixel_size;
        glm::vec2 location = transform->GetTranslation();
		float current_y = 0.f;
		const float initial_x = location.x;

        for (const char& c : text)
        {
            if (!characters.count(c))
            {
                std::cout << "Text Error: There is no " << c << " character in map!\n";
                continue;
            }

            const Character character = characters.find(c)->second;

			if (c == '\n')
			{
				location.x = initial_x;
				current_y -= transform->GetScale().y;
			}

            glm::vec2 position(character.bearing.x *scale.x, (character.bearing.y - character.size.y) * scale.y + current_y);
            glm::vec2 size(character.size);
            position += location;
            size *= scale;

            Mesh mesh;
			mesh.SetPoint(size, position, true);
            mesh.SetTextureCoordinate();
	        mesh.SetColor(color.front());
            meshes.push_back(mesh);

            location.x += ((character.advance >> 6)) * scale.x;
        }
    }

    unsigned int *SpriteText::GetTexture(int index)
    {
        if (index < 0 || index >= GetTextLength())
        {
            std::cout << "Sprite Text Error: Invalid index to access the texture ( " << index << " )!\n";
            return &characters[text.at(0)].texture;
        }
        return &characters[text.at(index)].texture;
    }

    void SpriteText::GenerateTexture(unsigned *texture, glm::vec2 size, unsigned char* pixel_data) const
    {
        glGenTextures(1, texture);
        glBindTexture(GL_TEXTURE_2D, *texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, static_cast<GLsizei>(size.x), static_cast<GLsizei>(size.y), 0, GL_RED, GL_UNSIGNED_BYTE, pixel_data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}
