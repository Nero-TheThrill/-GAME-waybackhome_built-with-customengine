/*
*  File Name : System.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: base of all system
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#pragma once
namespace BLUE
{
    class System
    {
    public:
        //Initialize the System
        virtual void Init() = 0;

        //All Systems are updated every frame
        virtual void Update() = 0;

        //All Systems need a virtual destructor to their destructors called
        virtual ~System()
        {
        }
    };

};