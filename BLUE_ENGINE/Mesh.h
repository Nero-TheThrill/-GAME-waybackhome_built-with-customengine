/*
*  File Name : Mesh.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Store all vertices' information of the sprite.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace BLUE
{
    enum class PointListType
    {
        Lines,
        LineStrip,
        Triangles,
        TriangleStrip,
        TriangleFan
    };

    struct Color
    {
        using ColorChannel = unsigned;
        //unsigned char
        ColorChannel red = 0;
        ColorChannel green = 0;
        ColorChannel blue = 0;
        ColorChannel alpha = 255;

        Color() = default;
        Color(ColorChannel red_color, ColorChannel green_color, ColorChannel blue_color, ColorChannel alpha_color = 255);
        Color(glm::vec4 color_float);
        glm::vec4 ColorToFloat() const;
    };

    /* This class has the values for vertices, colors */
    class Mesh
    {
    public:
        /* Point */
        void AddPoint(glm::vec2 point);
        glm::vec2 GetPoint(int index) const;
        void ClearPoint();
        int GetPointCount() const;
        // SetPoint: set point at once but it only works for box
        void SetPoint(glm::vec2 size = { 1.0f, 1.0f }, glm::vec2 reference_point = { 0.0f, 0.0f }, bool is_text = false);

        /* Color */
        void AddColor(Color color);
        Color GetColor(int index = 0) const;
        void ClearColor();
        // Set colors at once
        void SetColor(Color color);

        /* TextureCoordinate (UV) */
        void AddTextureCoordinate(glm::vec2 coordinate);
        glm::vec2 GetTextureCoordinate(int index) const;
        void ClearTextureCoordinate();
        // SetTextureCoordinate: set texture coordinate at once but it only works for box
        void SetTextureCoordinate(glm::vec2 reference_point = { 1.0f, 0.0f }, glm::vec2 size = { 1.0f, 1.0f }, bool filp_x = false);

        /* Point List Type */
        void SetPointListType(PointListType type);
        PointListType GetPointListType() const;

        Mesh &operator =(Mesh mesh);
    private:
        std::vector<glm::vec2> points{};
        std::vector<Color> colors{};
        std::vector<glm::vec2> textureCoordinate{};

        PointListType pointListType = PointListType::TriangleFan;
    };

    /* Helper functions for creating mesh */
    namespace CreateMesh
    {
        Mesh CreateCircle(Color color = { 255, 255, 255 }, float radius = 1.0f, std::size_t pointCount = 30);
        Mesh CreateWireCircle(Color color = { 255, 255, 255 }, float radius = 1.0f, std::size_t pointCount = 30);
        Mesh CreateBox(Color color = { 255, 255, 255 }, glm::vec2 scale = { 1.0f, 1.0f });
        Mesh CreateWireBox(Color color = { 255, 255, 255 }, glm::vec2 scale = { 1.0f, 1.0f });
        Mesh CreateLine(Color color = { 255, 255, 255 }, glm::vec2 a = { 0, 0 }, glm::vec2 b = { 1.0f, 1.0f });
    }

}