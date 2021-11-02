/*
*  File Name : Shader.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Compile and generate the shader to display the sprite on the screen.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Shader.h"
#include <stdio.h> /* print error */
#include <vector>   /* errorLog */
#include <fstream>  /* ReadFile(...) */
#include "ShaderSource.h" /* Shader Sources */

namespace BLUE
{

    Shader::Shader() : programID(0), numAttributes_(0) {}

    Shader::~Shader()
    {
		Unuse();
    }

    void Shader::CompileShaders(const ShaderVertexType type)
    {
        programID = glCreateProgram();

        vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        if (vertexShaderID == NULL)
            printf("Shader Error: Vertex shader failed to created!\n");

        fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        if (fragmentShaderID == NULL)
            printf("Shader Error: Fragment shader failed to created!\n");

        switch (type)
        {
        case ShaderVertexType::SpriteColor:
        {
            CompileIndividualShader(vertexShaderID, VertexShader_PositionColor.c_str());
            CompileIndividualShader(fragmentShaderID, FragmentShader_PositionColor.c_str());
        }
        break;
        case ShaderVertexType::SpriteTexture:
        {
            CompileIndividualShader(vertexShaderID, VertexShader_PositionTexture.c_str());
            CompileIndividualShader(fragmentShaderID, FragmentShader_PositionTexture.c_str());
        }
        break;
		case ShaderVertexType::SpriteTexture_HUD:
		{
			CompileIndividualShader(vertexShaderID, VertexShader_PositionTexture_HUD.c_str());
			CompileIndividualShader(fragmentShaderID, FragmentShader_PositionTexture_HUD.c_str());
		}
		break;
        case ShaderVertexType::SpriteText:
        {
            CompileIndividualShader(vertexShaderID, VertexShader_Text.c_str());
            CompileIndividualShader(fragmentShaderID, FragmentShader_Text.c_str());
        }
		break;
		case ShaderVertexType::SpriteText_HUD:
        {
			CompileIndividualShader(vertexShaderID, VertexShader_Text_HUD.c_str());
			CompileIndividualShader(fragmentShaderID, FragmentShader_Text_HUD.c_str());
        }
		break;
        }


        LinkShaders();
    }

    void Shader::AddAttribute(const std::string& attribute_name)
    {
        glBindAttribLocation(programID, numAttributes_++, attribute_name.c_str());
    }

    GLint Shader::GetAttributeLocation(const std::string& attribute_name)
    {
        GLint location = glGetAttribLocation(programID, attribute_name.c_str());
        if (location == GL_INVALID_OPERATION)
            printf("Shader Error: could not find attribute location!\n");
        return location;
    }

    void Shader::LinkShaders()
    {
        glAttachShader(programID, vertexShaderID);
        glAttachShader(programID, fragmentShaderID);
        glLinkProgram(programID);

        GLint isLinked = NULL;
        glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);

        /* If linking is failed */
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(programID, maxLength, &maxLength, &errorLog[0]);

            glDeleteShader(programID);
            glDeleteShader(vertexShaderID);
            glDeleteShader(fragmentShaderID);

            printf("Shader Error: fail to link!\n");
            printf("%s\n", &(errorLog[0]));
        }
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    GLint Shader::GetUniformLocation(const std::string& uniform_name)
    {
        /* Get location where the uniform is */
        GLint location = glGetUniformLocation(programID, uniform_name.c_str());
        if (location == GL_INVALID_INDEX)
            printf("Shader Error: could not find uniform %s in shader(%d)!\n", uniform_name.c_str(), programID);
        return location;
    }

    void Shader::SendUniformVariable(const std::string& name, const int i)
    {
        glUniform1i(GetUniformLocation(name), i);
    }

    void Shader::SendUniformVariable(const std::string& name, const float f)
    {
        glUniform1f(GetUniformLocation(name), f);
    }

    void Shader::SendUniformVariable(const std::string& name, const glm::vec3 vec3)
    {
        glUniform3fv(GetUniformLocation(name), 1, &vec3[0]);
    }

    void Shader::SendUniformVariable(const std::string& name, const glm::vec4 vec4)
    {
        glUniform4fv(GetUniformLocation(name), 1, &vec4[0]);
    }

    void Shader::SendUniformVariable(const std::string& name, const glm::mat4 mat4)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &(mat4[0][0]));
    }

    void Shader::Use()
    {
        glUseProgram(programID);
        for (int i = 0; i < numAttributes_; i++)
        {
            glEnableVertexAttribArray(i);
        }
    }

    void Shader::Unuse()
    {
        glDeleteProgram(programID);
        for (int i = 0; i < numAttributes_; i++)
        {
            glDisableVertexAttribArray(i);
        }
    }

    void Shader::CompileIndividualShader(GLuint id, const char * content_source)
    {
        glShaderSource(id, 1, &content_source, NULL);
        glCompileShader(id);

        GLint isCompiled = NULL;
        glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

        /* If shader compile is failed */
        if (isCompiled == false)
        {
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

            glDeleteShader(id);

            printf("Shader Error: fail to compile!\n");
            printf("%s\n", &(errorLog[0]));
        }
    }

    const char * Shader::ReadFile(const std::string file_path)
    {
        std::ifstream file(file_path);

        if (file.fail())
        {
            perror(file_path.c_str());
            printf("Shader Error: Failed to open the \n");
        }

        std::string fileContents = "";
        std::string line;

        while (std::getline(file, line))
            fileContents += line + "\n";
        file.close();

        const char * contentPtr = fileContents.c_str();

        return contentPtr;
    }
}