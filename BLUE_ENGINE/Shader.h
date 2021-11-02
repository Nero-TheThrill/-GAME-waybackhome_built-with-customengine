/*
*  File Name : Shader.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Compile and generate the shader to display the sprite on the screen.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <GL/glew.h>
#include <string> /* shader name */
#include <glm/glm.hpp> /* vector and matrix */

namespace BLUE
{
    enum class ShaderVertexType
    {
        SpriteColor,
        SpriteTexture,
		SpriteTexture_HUD,
        SpriteText,
		SpriteText_HUD
        /* Add if you make new shadersources */
    };

    class Shader
    {
    public:
        Shader();
        ~Shader();

        /* Compile Shaders
        * vertex_type = PositionColor or PositionTexture */
        void CompileShaders(const ShaderVertexType type);

        void AddAttribute(const std::string& attribute_name);
        GLint GetAttributeLocation(const std::string& attribute_name);

        /* For Uniform variables in shader source */
        GLint GetUniformLocation(const std::string& uniform_name);
        void SendUniformVariable(const std::string& name, const int i);
        void SendUniformVariable(const std::string& name, const float f);
        void SendUniformVariable(const std::string& name, const glm::vec3 vec3);
        void SendUniformVariable(const std::string& name, const glm::vec4 vec4);
        void SendUniformVariable(const std::string& name, const glm::mat4 mat4);

        /* Use or Unuse the shader */
        void Use();
        void Unuse();
    private:
        /* Linking vertex and fragment shader*/
        void LinkShaders();
        /* Compile vertex/fragment Shader */
        void CompileIndividualShader(GLuint id, const char * content_source);

        /* Read shader source file from file_path
        * (Don't use it because sometimes shaders doesn't compile when you use this func) */
        const char * ReadFile(const std::string file_path);

        GLuint programID;
        GLuint vertexShaderID;
        GLuint fragmentShaderID;

        int numAttributes_;
    };

}
