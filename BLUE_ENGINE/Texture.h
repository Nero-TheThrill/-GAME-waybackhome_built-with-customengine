/*
*  File Name : Texture.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Display the texture with the pixel data loaded in Image class by stb_image
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <string>
#include <map> /* Texture Manager */

#define GLM_FORCE_CXX03
#include <glm/glm.hpp>

namespace BLUE
{
    class Character;

    class Image
    {
    public:
        Image();
        void LoadFromFile(const std::string & file_path);
        glm::ivec2 GetImageSize() const;
        unsigned char * GetPixelData() const;
    private:
        glm::ivec2 size;
        unsigned char *pixel;
    };

    class Texture
    {
    public:
        Texture();
        void LoadFromFile(const std::string & file_path);

        void Bind(unsigned int slot = 0) const;
        void DeleteTexture();

        glm::ivec2 GetTextureSize() const;
        std::string GetFilePath() const;

        ~Texture();
        Texture(Texture&& texture) noexcept;
        Texture& operator=(Texture&& texture) noexcept;
        Texture(const Texture& texture);
        Texture& operator=(const Texture& texture);
    private:
        void LoadFromImage(const Image image);
        void GenerateTexture();
        unsigned int textureID;
        glm::ivec2 size;
        std::string file_path;
    };

    class TextureManager
    {
    public:
		TextureManager();
        Texture *GetTexture(const std::string& texture_path);
    private:
        std::map<std::string, Texture*> textureMap;
    };
	extern TextureManager * TEXTURE_MANAGER;
}

