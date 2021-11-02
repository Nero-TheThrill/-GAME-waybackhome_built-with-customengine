/*
*  File Name : Texture.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Display the texture with the pixel data loaded in Image class by stb_image
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Texture.h"
#include <GL/glew.h>

/* load image */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

namespace BLUE
{
	TextureManager * TEXTURE_MANAGER = nullptr;

    Image::Image() : size{ 0, 0 }, pixel(nullptr)
    {
    }

	void Image::LoadFromFile(const std::string& file_path)
    {
        int Channels = 0;

        pixel = stbi_load(file_path.c_str(), &size.x, &size.y, &Channels, STBI_rgb_alpha);

        if (pixel == nullptr)
            std::cout << "Texture: Load image from " << file_path << " fail!\n";
    }

    glm::ivec2 Image::GetImageSize() const
    {
        return size;
    }

    unsigned char* Image::GetPixelData() const
    {
        return pixel;
    }

    Texture::Texture() : textureID(0), size{ 0, 0 }, file_path("")
    {
    }

    void Texture::LoadFromFile(const std::string& file_path_)
    {
		DeleteTexture();
        Image image;
        image.LoadFromFile(file_path_);
        LoadFromImage(image);
		
        this->file_path = file_path_;
    }

    void Texture::LoadFromImage(const Image image)
    {
        size = image.GetImageSize();
        GenerateTexture();
        constexpr int base_mipmap_level = 0;
        constexpr int zero_border = 0;
        glTexImage2D(GL_TEXTURE_2D, base_mipmap_level, GL_RGBA8, size.x, size.y, zero_border, GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixelData());
    }

    void Texture::GenerateTexture()
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    }


    void Texture::Bind(unsigned slot) const
    {
        if (textureID == 0)
            return;
        if (slot >= 32)
        {
            printf("Texture Error: slot is more than 32 in Bind function!\n");
            return;
        }

        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    void Texture::DeleteTexture()
    {
        if (textureID)
            glDeleteTextures(1, &textureID);
        textureID = 0;
    }

    glm::ivec2 Texture::GetTextureSize() const
    {
        return size;
    }

    std::string Texture::GetFilePath() const
    {
        return file_path;
    }

    Texture::~Texture()
    {
        DeleteTexture();
    }

    Texture::Texture(Texture&& texture) noexcept
        : textureID{ texture.textureID }, size(texture.size)
    {
        texture.textureID = 0;
        texture.size = { 0, 0 };
    }

    Texture& Texture::operator=(Texture&& texture) noexcept
    {
        if (this == &texture)
            return *this;

        textureID = texture.textureID;
        size = texture.size;

        texture.textureID = 0;
        texture.size = { 0, 0 };

        return *this;
    }

    Texture::Texture(const Texture& texture)
        : textureID{ texture.textureID }, size(texture.size)
    {
    }

    Texture& Texture::operator=(const Texture& texture)
    {
        if (this == &texture)
            return *this;

        textureID = texture.textureID;
        size = texture.size;

        return *this;
    }

	TextureManager::TextureManager()
	{
		TEXTURE_MANAGER = this;
	}

    Texture *TextureManager::GetTexture(const std::string& texture_path)
    {
        if (!textureMap.count(texture_path))
        {

           // std::cout << "Texture Manager: New image is loaded from " << texture_path << "\n";

			Texture* new_texture = new Texture();
            new_texture->LoadFromFile(texture_path);
            textureMap.insert(std::make_pair(texture_path, new_texture));
			return new_texture;
        }
        const auto texture = textureMap.find(texture_path);
       // std::cout << "Texture Manager: Use cached texture: " << texture_path << "\n";
        return (texture->second);
    }
}
