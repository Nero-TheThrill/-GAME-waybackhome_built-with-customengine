/*
*  File Name : Input.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: managing input
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <SDL.h>
#include <bitset>
#include <glm/glm.hpp>
#define NUM_MOUSECODE 10
#define NUM_WHEELCODE 5

class Input
{

public:

    //"Input::GetInstance(). to use functions of Input Class.
    //////////////////////////////
    static Input& GetInstance()
    {
        static Input input;
        return input;
    }
    //////////////////////////////


    void Reset(void);
    void SetKeyPressed(SDL_Scancode key, SDL_EventType eType);
    static bool IsKeyPressed(SDL_Scancode key);
    static bool IsKeyTriggered(SDL_Scancode key);
    static bool IsKeyReleased(SDL_Scancode key);
    static bool IsAnyKeyPressed();
    static bool IsAnyKeyTriggered();
    static bool IsAnyKeyReleased();
    void SetMousePos(float x, float y);
    glm::vec2 GetMousePos();
    void SetMousePressed(int mButton, SDL_EventType eMouseButton);
    static bool IsMousePressed(int key);
    static bool IsMouseTriggered(int key);
    static bool IsMouseDoubleClicked(int key);
    static bool IsMouseReleased(int key);
    static int GetMouseWheelState();
    void SetMouseWheelState(int state);


};
