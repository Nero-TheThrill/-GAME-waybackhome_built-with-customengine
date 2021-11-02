/*
*  File Name : Mesh.cpp
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Store all vertices' information of the sprite.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Mesh.h"
#include <iostream>

namespace BLUE
{
    Color::Color(ColorChannel red_color, ColorChannel green_color, ColorChannel blue_color, ColorChannel alpha_color)
        :red(red_color), green(green_color), blue(blue_color), alpha(alpha_color)
    {
    }

    Color::Color(glm::vec4 color_float)
    {
        red = static_cast<ColorChannel>(color_float.x * 255);
        green = static_cast<ColorChannel>(color_float.y * 255);
        blue = static_cast<ColorChannel>(color_float.z * 255);
        alpha = static_cast<ColorChannel>(color_float.w * 255);
    }

    glm::vec4 Color::ColorToFloat() const
    {
        return { red / 255.0f, green / 255.0f, blue / 255.0f, alpha / 255.0f };
    }

    void Mesh::AddPoint(glm::vec2 point)
    {
        points.push_back(point);
    }

    glm::vec2 Mesh::GetPoint(int index) const
    {
        return points.at(index);
    }

    int Mesh::GetPointCount() const
    {
        return static_cast<int>(points.size());
    }

    void Mesh::SetPoint(glm::vec2 size, glm::vec2 reference_point, bool is_text)
    {
        ClearPoint();
        if (is_text == false)
        {
            AddPoint({ reference_point.x + size.x / 2, reference_point.y - size.y / 2 });
            AddPoint({ reference_point.x + size.x / 2, reference_point.y + size.y / 2 });
            AddPoint({ reference_point.x - size.x / 2, reference_point.y + size.y / 2 });
            AddPoint({ reference_point.x - size.x / 2, reference_point.y - size.y / 2 });
            AddPoint({ reference_point.x + size.x / 2, reference_point.y - size.y / 2 });
        }
        else
        {
            AddPoint({ reference_point.x + size.x, reference_point.y });
            AddPoint({ reference_point.x + size.x, reference_point.y + size.y });
            AddPoint({ reference_point.x, reference_point.y + size.y });
            AddPoint({ reference_point.x, reference_point.y });
            AddPoint({ reference_point.x + size.x, reference_point.y });
        }
    }

    void Mesh::ClearPoint()
    {
        points.clear();
    }

    void Mesh::AddColor(Color color)
    {
        colors.push_back(color);
    }

    Color Mesh::GetColor(int index) const
    {
        return colors.at(index);
    }

    void Mesh::ClearColor()
    {
        colors.clear();
    }

    void Mesh::SetColor(Color color)
    {
        ClearColor();
        for (int i = 0; i < GetPointCount(); i++)
            AddColor(color);
    }

    void Mesh::AddTextureCoordinate(glm::vec2 coordinate)
    {
        textureCoordinate.push_back(coordinate);
    }

    glm::vec2 Mesh::GetTextureCoordinate(int index) const
    {
        return textureCoordinate.at(index);
    }

    void Mesh::ClearTextureCoordinate()
    {
        textureCoordinate.clear();
    }

    void Mesh::SetTextureCoordinate(glm::vec2 reference_point, glm::vec2 size, bool filp_x)
    {
        if (reference_point.x < 0.0f || reference_point.x > 1.0f
            || reference_point.y <0.0f || reference_point.y > 1.0f
            || size.x <0.0f || size.x > 1.0f || size.y < 0.0f || size.y > 1.0f)
        {
            std::cout << "Mesh Error: Texture Coordinate should be between 0.0f to 1.0f!\n";
            return;
        }

        ClearTextureCoordinate();
        if (!filp_x)
        {
            AddTextureCoordinate(reference_point);
            AddTextureCoordinate({ reference_point.x, reference_point.y + size.y });
            AddTextureCoordinate({ reference_point.x - size.x, reference_point.y + size.y });
            AddTextureCoordinate({ reference_point.x - size.x, reference_point.y });
            AddTextureCoordinate(reference_point);
        }
        else
        {
            AddTextureCoordinate({ reference_point.x - size.x, 1.0f - (reference_point.y + size.y) });
            AddTextureCoordinate({ reference_point.x - size.x, 1.0f - (reference_point.y) });
            AddTextureCoordinate({ reference_point.x,1.0f - reference_point.y });
            AddTextureCoordinate({ reference_point.x,1.0f - (reference_point.y + size.y) });
            AddTextureCoordinate({ reference_point.x - size.x, 1.0f - (reference_point.y + size.y) });
        }

        if (textureCoordinate.size() != points.size())
        {
            std::cout << "Mesh Error: size of points and texture coodinate points is different!\n";
            return;
        }
    }

    void Mesh::SetPointListType(PointListType type)
    {
        pointListType = type;
    }

    PointListType Mesh::GetPointListType() const
    {
        return pointListType;
    }

    Mesh &Mesh::operator=(Mesh mesh)
    {
        ClearPoint();
        for (int i = 0; i < mesh.GetPointCount(); i++)
            points.push_back(mesh.points.at(i));

        ClearColor();
        for (int i = 0; i < static_cast<int>(mesh.colors.size()); i++)
            colors.push_back(mesh.colors.at(i));

        ClearTextureCoordinate();
        for (int i = 0; i < static_cast<int>(mesh.textureCoordinate.size()); i++)
            textureCoordinate.push_back(mesh.textureCoordinate.at(i));

        pointListType = mesh.GetPointListType();

        return *this;
    }

    namespace CreateMesh
    {
        Mesh CreateCircle(Color color, float radius, std::size_t pointCount)
        {
            Mesh mesh;
            const float PI = 4.0f * std::atan(1.0f);
            float theta = 360.0f / pointCount / 180.f * PI;
            for (unsigned int i = 0; i <= pointCount; i++)
            {
                mesh.AddPoint({ std::cos(theta * i) * (radius / 2.0f), std::sin(theta * i) * (radius / 2.0f) });
                mesh.AddTextureCoordinate({ (1.0f + std::cos(theta * i)) / 2.0f, (1.0f + std::sin(theta * i)) / 2.0f });
            }
            mesh.SetColor(color);
            mesh.SetPointListType(PointListType::TriangleFan);
            return mesh;
        }

        Mesh CreateWireCircle(Color color, float radius, std::size_t pointCount)
        {
            Mesh mesh;
            const float PI = 4.0f * std::atan(1.0f);
            float theta = 360.0f / pointCount / 180.f * PI;
            for (unsigned int i = 0; i <= pointCount; i++)
            {
                mesh.AddPoint({ std::cos(theta * i) * (radius / 2.0f), std::sin(theta * i) * (radius / 2.0f) });
            }
            mesh.SetColor(color);
            mesh.SetPointListType(PointListType::LineStrip);
            return mesh;
        }

        Mesh CreateBox(Color color, glm::vec2 scale)
        {
            Mesh mesh;
            mesh.SetPoint(scale);
            mesh.SetTextureCoordinate();
            mesh.SetColor(color);
            mesh.SetPointListType(PointListType::TriangleStrip);
            return mesh;
        }

        Mesh CreateWireBox(Color color, glm::vec2 scale)
        {
            Mesh mesh;
            mesh.SetPoint(scale);
            mesh.SetColor(color);
            mesh.SetPointListType(PointListType::LineStrip);
            return mesh;
        }

        Mesh CreateLine(Color color, glm::vec2 a, glm::vec2 b)
        {
            Mesh mesh;
            mesh.AddPoint({ a.x, a.y });
            mesh.AddPoint({ b.x, b.y });

            mesh.SetColor(color);
            mesh.SetPointListType(PointListType::Lines);
            return mesh;
        }
    }

}
