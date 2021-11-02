/*
*  File Name : CurbCameraMotion.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: The camera can move in limited size
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Object.h"
#include "Camera.h"

namespace BLUE
{
    class CurbCameraMotion
    {
    public:
        CurbCameraMotion();
		
        /* This should be written in update function */
        void Update();
		void Reset();

        /* Initialize the class
         *  width = total width, height = total height
         */
        void Init(Camera * camera_pointer, Transform * player_transform, float width = 300.0f, float height = 300.0f);
        /* Center is already initialized to (0.0f, 0.0f) */
        void SetCenter(glm::vec2 center_position);
        /* Draw the boundary or not */
        void DrawLine(bool on);

        void FollowObject(bool follow);
    private:
        /* Update function */
        void DrawLine();

        /* Initialize the line(boundary) */
        void InitLine();
        /* Is the player in the boundary */
        bool IsOutsideOfBoundary() const;
        /* Move camera's position */
        void MoveCamera() const;

        Object *line;
        Camera *camera;
        Transform *player;

        glm::vec2 center;
        glm::vec2 size;

        glm::vec2 player_size;

        bool drawline;
        bool follow_object;
    };
}
