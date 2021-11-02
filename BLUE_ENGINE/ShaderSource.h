/*
*  File Name : ShaderSource.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief:	Source files for shader.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once

const std::string VertexShader_PositionTexture_HUD =
R"(
#version 330 core
layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 TextureCoordinate;

uniform float depth;

out vec2 ourTextureCoordinate;

void main()
{
    gl_Position = vec4(Position, depth, 1.0);
    ourTextureCoordinate = vec2(TextureCoordinate.x, 1.0f-TextureCoordinate.y);
}
)";

const std::string FragmentShader_PositionTexture_HUD =
R"(
#version 330 core
out vec4 output_color;
in vec2 ourTextureCoordinate;

uniform vec4 color;
uniform sampler2D texture_sample;

void main()
{
   vec4 textureColor = texture(texture_sample, ourTextureCoordinate);
   vec4 newColor = textureColor * color;
   if(newColor.a <= 0.0f) discard;
   output_color = newColor;
}
)";

const std::string VertexShader_PositionColor =
R"(
#version 330 core
layout(location = 0) in vec2 Position;
layout(location = 1) in vec4 Color;

uniform mat4 view;
uniform mat4 transform;
uniform float depth;

out vec4 ourColor;
void main()
{
    vec4 pos = (view * transform * vec4(Position, 0.0f,1.0));
    gl_Position = vec4(pos.xy, depth, 1.0);
    ourColor = Color;
}
)";

const std::string FragmentShader_PositionColor =
R"(
#version 330 core
out vec4 output_color;
in vec4 ourColor;

void main()
{
   output_color = ourColor;
}
)";

const std::string VertexShader_PositionTexture =
R"(
#version 330 core
layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 TextureCoordinate;

uniform mat4 view;
uniform mat4 transform;
uniform float depth;

out vec2 ourTextureCoordinate;

void main()
{
    vec4 pos = (view * transform * vec4(Position, 0.0f,1.0));
    gl_Position = vec4(pos.xy, depth, 1.0);
    ourTextureCoordinate = vec2(TextureCoordinate.x, 1.0f-TextureCoordinate.y);
}
)";

const std::string FragmentShader_PositionTexture =
R"(
#version 330 core
out vec4 output_color;
in vec2 ourTextureCoordinate;

uniform vec4 color;
uniform sampler2D texture_sample;

void main()
{
   vec4 textureColor = texture(texture_sample, ourTextureCoordinate);
   vec4 newColor = textureColor * color;
   if(newColor.a <= 0.0f) discard;
   output_color = newColor;
}
)";

const std::string VertexShader_Text =
R"(
#version 330 core
layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 TextureCoordinate;

uniform mat4 view;
uniform float depth;

out vec2 ourTextureCoordinate;

void main()
{
	vec4 pos = (view * vec4(Position, 0.0f, 1.0));
	gl_Position = vec4(pos.xy, depth, 1.0);

    ourTextureCoordinate = vec2(TextureCoordinate.x, 1.0f-TextureCoordinate.y);
}
)";

const std::string FragmentShader_Text =
R"(
#version 330 core
in vec2 ourTextureCoordinate;
out vec4 output_color;

uniform sampler2D text;
uniform vec4 color;

void main()
{
    vec4 text_color = texture(text, ourTextureCoordinate);
    vec4 text_sampled = vec4(1.0, 1.0, 1.0, text_color.r);
    output_color = color * text_sampled;
}
)";

const std::string VertexShader_Text_HUD =
R"(
#version 330 core
layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 TextureCoordinate;

uniform float depth;

out vec2 ourTextureCoordinate;

void main()
{
	gl_Position = vec4(Position, depth, 1.0);
    ourTextureCoordinate = vec2(TextureCoordinate.x, 1.0f-TextureCoordinate.y);
}
)";

const std::string FragmentShader_Text_HUD =
R"(
#version 330 core
in vec2 ourTextureCoordinate;
out vec4 output_color;

uniform sampler2D text;
uniform vec4 color;

void main()
{
    vec4 text_color = texture(text, ourTextureCoordinate);
    vec4 text_sampled = vec4(1.0, 1.0, 1.0, text_color.r);
    output_color = color * text_sampled;
}
)";