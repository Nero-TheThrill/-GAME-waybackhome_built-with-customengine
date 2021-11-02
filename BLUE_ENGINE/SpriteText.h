/*
*  File Name : SpriteText.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Display the text on the screen.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#pragma once
#include "Mesh.h"
#include "Transform.hpp"

#include <map> /* Character Map */

/* Load Font */
#include <ft2build.h>
#include <string>

#include FT_FREETYPE_H
#include "Hud.h"

namespace BLUE
{
    class Character
    {
    public:
        Character();
        Character(const Character& character);
        Character &operator=(const Character& character);

        unsigned texture;
        glm::ivec2 size;
        glm::ivec2 bearing;
        int advance;
    };

    class SpriteText : public Component
    {
    public:
        SpriteText();
        ~SpriteText() override;

        void Init() override;

        /* Initialize the Text
         * Font path must set first( before set text ) */
        void SetFontPath(const std::string &font_path);
        void SetText(const std::string &text_string);

        // Set text's color
        void SetColor(const Color& text_color);
        // Set individual letter's color
        void SetColor(const Color& text_color, int index);

        /* functions to draw text on the screen in graphics class */
        int GetTextLength() const;
        Mesh GetMesh(int index) const;
        float GetDepth() const;
        void BindTexture(int index);

		void ScaleHUDRepecttoResolution(glm::vec2 window_size);
		glm::vec2 GetPosition() const;
		glm::vec2 GetSize() const;

		bool isHud;
    private:
        void LoadFromFile(const std::string & font_path);
		// Store text's characters in character map
        void SetCharacter(const FT_Face &face, char c);
		// Set meshes according to each characters
        void SetMeshes();
        unsigned int* GetTexture(int index);
        void GenerateTexture(unsigned *texture, glm::vec2 size, unsigned char*pixel_data) const;
		void EachLetterHasDifferentColor(bool each_has_different_color);

    	std::map<unsigned char, Character> characters;

        std::string text;
        const float pixel_size; //default pixel size
        std::vector<Mesh> meshes;		
		std::vector<Color> color;
		bool has_different_color;

        std::string fontPath;		
        /* transform information */
        Transform* transform;

		HUD hud;
    };

}
