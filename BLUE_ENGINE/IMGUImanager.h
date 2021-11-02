/*
*  File Name : IMGUImanager.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: Debuging system. Can make and modify objects.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "System.h"
#include <SDL.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
#include <GL/glew.h>
#include "BaseController.h"

namespace  BLUE
{
    class IMGUImanager
    {
    public:
        IMGUImanager();
        void Init();
        void Update();
        ~IMGUImanager();
        void MainWindow();
        void ObjectList();
        void ObjectManage() const;
		void AudioManage() const;
        void clearcolor() const;
        bool Initialized() const;
        void ShutDown();
    private:
		void SetColor() const;
		void SetResolution() const;
        void GenerateObject(ControllerType type, int * current_type);
        void SetName(int object_num) const;
        void SetTransform(int object_num) const;
        void SetSprite(int object_num) const;
		void SetItemtype(int object_num) const;
        void DebugDrawing() const;
        void DrawRectangle(ImVec2 pos1, ImVec2 pos2, ImU32 color) const;
        void DrawRectangle(ImVec2 pos1, ImVec2 pos2, ImVec2 pos3, ImVec2 pos4, ImU32 color) const;
        bool show_demo_window = false;
        ImVec4 clear_color = ImVec4(0.f, 0.0f, 0.f, 1.00f);
        SDL_Window* pWindow;
        SDL_GLContext glContext;
        bool initialized = false;
        ImGuiIO io;
        int screen_width, screen_height;

        BaseController *controller;
    };
    extern IMGUImanager* IMGUI_MANAGER;
}
