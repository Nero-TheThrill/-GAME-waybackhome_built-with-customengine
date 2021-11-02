/*
*  File Name : Engine.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: Base of the engine. All systems will managed by this class.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include<SDL.h>
#include <GL/glew.h>
#include <vector>
#include "Engine.h"
#include <glm/glm.hpp>
#include"Application.h"
#include <iostream>
#include "StateManager.h"
#include "ObjectFactory.h"
#include "Graphics.h"
#include "EnemyController.h"
#include "IMGUImanager.h"
#include "Audio.h"
#include "SmokeEffects.h"
#include "PauseScreen.h"
#include "ReplaySystem.h"
#include "CursorController.h"
#include "PoisonBulletController.h"
#include "PoisonPlantManager.h"
#include "Resolution.h"
#include "Dialogue.h"
#include "ObjectController.h"
#include "PlayerController.h"
#include "PastBulletController.h"
#include "FutureBulletController.h"
#include "PopupMessage.h"

namespace BLUE
{
    Engine* ENGINE = nullptr;

    Engine::Engine()
    {
        fps_ = 0;
        GAMERUN = true;
        ENGINE = this;
        Systems.clear();
    }

    Engine::~Engine()
    {
        for (auto system : Systems)
        {
            delete system;
            system = nullptr;
        }
    }

    void Engine::Init()
    {
        std::cout << "Initialize Engine" << std::endl;
        ENEMY_CONTROLLER = new EnemyController();
        IMGUI_MANAGER = new IMGUImanager();
        OBJECT_CONTROLLER = new ObjectController();
        AUDIO_MANAGER = new Audio();
        PLAYER_CONTROLLER = new PlayerController();
        PASTBULLET_CONTROLLER = new PastBulletController();
        FUTUREBULLET_CONTROLLER = new FutureBulletController();
        SMOKE_EFFECT = new SmokeEffect();
        PAUSE_SCREEN = new PauseScreen();
        CURSOR_CONTROLLER= new CursorController();
        POISONBULLET_CONTROLLER = new PoisonBulletController();
        POISONPLANT_MANAGER = new PoisonPlantManager();
        GHOST_CONTROLLER = new GhostController();
		RESOLUTION = new Resolution();
		TEXTURE_MANAGER = new TextureManager();
		DIALOGUE = new Dialogue();
		POPUPMESSAGE = new PopupMessage();

        //Order is important
        AddSystem(new Application());
        AddSystem(new ObjectFactory());
        AddSystem(new Graphics());
        AddSystem(new StateManager());
        AUDIO_MANAGER->Init();
        for (auto blue : Systems)
        {
            blue->Init();
        }
        REPLAY_SYSTEM = new ReplaySystem();
    }

    void Engine::GameLoop()
    {
        float maxfps = 60.f;

        while (GAMERUN)
        {
            float startTicks = (float)SDL_GetTicks();

            for (auto blue : Systems)
            {
                blue->Update();
            }


            calculateFPS();
            float frameTicks = (float)SDL_GetTicks() - startTicks;
            if ((1000.f / maxfps) > frameTicks)
                SDL_Delay((Uint32)((1000.f / maxfps) - frameTicks));


        }
    }

    void Engine::Quit()
    {
        GAMERUN = false;
    }

    void Engine::AddSystem(System* system)
    {
        Systems.push_back(system);
    }

    void Engine::calculateFPS()
    {
        static const int NUM_SAMPLES = 10;
        static float frameTimes[NUM_SAMPLES];
        static int currentFrame = 0;

        static float prevTicks = (float)SDL_GetTicks();
        float currentTicks = (float)SDL_GetTicks();

        float frameTime = currentTicks - prevTicks;
        frameTimes[currentFrame % NUM_SAMPLES] = frameTime;

        prevTicks = currentTicks;

        int count;
        currentFrame++;

        if (currentFrame < NUM_SAMPLES)
            count = currentFrame;
        else
            count = NUM_SAMPLES;

        float frameTimeAverage = 0;
        for (int i = 0; i < count; i++)
            frameTimeAverage += frameTimes[i];

        frameTimeAverage /= count;

        if (frameTimeAverage > 0)
            fps_ = 1000.0f / frameTimeAverage;
        else
            fps_ = 60.0f;
    }
}

























//bool InitApp();
//GLuint CreateShader(GLenum shaderType, const char* source);
//void Initvertices();
//void Render();
//
//GLuint gShaderProgram;
//GLuint gVertexBufferObject;
//std::vector<glm::vec3>gVertices;
//
//
//int dosomething(void)
//{
//    /*GLFW window handler*/
//    GLFWwindow* window;
//
//    /* Initialize the GLFW library */
//    if (!glfwInit())
//        return -1;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "GLFW PRACTICE", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//    /* Initialize the GLEW */
//    glewInit();
//    /* Initialize */
//    InitApp();
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* DELETE BUFFER */
//
//        Render();
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//    glfwDestroyWindow(window);
//    glfwTerminate();
//    return 0;
//}
//
//GLuint CreateShader(GLenum shaderType, const char* source) {
//    GLuint shader = glCreateShader(shaderType);
//    if (shader == 0)
//        return 0;
//
//    // set shader source
//    glShaderSource(shader, 1, &source, NULL);
//
//    // compile shader object
//    glCompileShader(shader);
//
//    return shader;
//}
//
//
//bool InitApp()
//{
//    glClearColor(0.f, 0.f, 0.f, 0.f);
//
//    /* Use Depth test */
//    glEnable(GL_DEPTH_TEST);
//    /* Do not draw backside of the mesh */
//    glEnable(GL_CULL_FACE);
//    /* ccw is general, ccw=counterclockwise cw=clockwise */
//    glFrontFace(GL_CCW);
//    /* FrontFace will FILL the mesh, BackFace will draw by line */
//    glPolygonMode(GL_FRONT, GL_FILL);
//    glPolygonMode(GL_BACK, GL_LINE);
//
//    Initvertices();
//    return true;
//}
//
//void Initvertices()
//{
//    const char* vertShaderSource = R"(
//    #version 450
//
//    layout(location=0) in vec3 position;
//
//    uniform mat4 matView;
//    uniform mat4 matProj;
//
//    void main() 
//    {
//	gl_Position = vec4(position, 1.f);
//    }
//)";
//    const char*fragShaderSource = R"(
//    #version 450
//
//    out vec4 color;
//
//    void main()
//    {
//        color = vec4(1, 1, 1, 1);
//    }
// )";
//
//    GLuint vertShaderObj = CreateShader(GL_VERTEX_SHADER, vertShaderSource);
//    GLuint fragShaderObj = CreateShader(GL_FRAGMENT_SHADER, fragShaderSource);
//
//
//    gShaderProgram = glCreateProgram();
//
//
//    glAttachShader(gShaderProgram, vertShaderObj);
//    glAttachShader(gShaderProgram, fragShaderObj);
//
//
//    glDetachShader(gShaderProgram, vertShaderObj);
//    glDetachShader(gShaderProgram, fragShaderObj);
//
//
//    glDeleteShader(vertShaderObj);
//    glDeleteShader(fragShaderObj);
//
//
//    gVertices = {
//        glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.5f, 0.5f, 0.f)
//    };
//
//    // 정점 버퍼 생성 및 버퍼 데이터 정의
//    glCreateBuffers(1, &gVertexBufferObject);
//    glNamedBufferData(gVertexBufferObject, gVertices.size() * sizeof(glm::vec3), &gVertices[0], GL_STATIC_DRAW);
//
//}
//
//void Render()
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glUseProgram(gShaderProgram);
//
//
//    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
//
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, NULL);
//
//    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)gVertices.size());
//
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    glDisableVertexAttribArray(0);
//
//
//    glUseProgram(0);
//}
//
//
