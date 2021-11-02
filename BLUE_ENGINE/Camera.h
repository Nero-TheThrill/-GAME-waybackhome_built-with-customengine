/*
*  File Name : Camera.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief:	OpenGL window(-1.0 to 1.0) to viewport(screen width * height)
                        Can set the position, rotation, and zooming.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <glm/glm.hpp> /* glm::vec2 */
#include "Input.h" // camera Control
#include "Transform.hpp"

namespace BLUE
{
    struct FollowObject
    {
        FollowObject();

        bool dofollow;

        Transform * transform;
        glm::vec2 distance;
    };

    struct ScreenShake
    {
        glm::vec2 camera_position;

        bool doscreenshake;
        int duration;
        float intensity;
    };

    class Camera
    {
    public:
        Camera();

        /* Initialize the camera with window(screen) size */
        void Init(int screen_width, int screen_height);

        void SetScreenSize(const glm::ivec2 new_screen_size);
        glm::ivec2 GetScreenSize() const;

        /* Set or Get position of the camera */
        void SetPosition(const glm::ivec2& new_position);
        glm::ivec2 GetPosition() const;

        /* Set or Get Zoom */
        void SetZoom(const float& new_zoom);
        float GetZoom() const;

        /* Set or Get theta(rotate the camera) */
        void SetRotation(const float& new_rotation);
        float GetRotation() const;

        /* reset position, rotation, zoom */
        void ResetCamera();

        /* Get Camera Matrix to send it to shader */
        glm::mat4 GetCameraMatrix();

        /* Call Update when camera changed */
        void UpdateCameraMatrix();

        /* If you call IsCameraChanges and it returns true,
        *      you MUST call ConfirmCameraChangeCompleted fucntion
        *
        * IsCameraChanges: Is camera moved, rotated, or scaled?
        * ConfirmCameraChangeComplete:
        *      This function is for HUD object.
        *      The reason why it need is to prevent unneed calculation
        */
        bool IsCameraChanges() const;
        void ConfirmCameraChangeCompleted();

        /* Store position of object to follow
         * 'nullptr' means stop to follow the object */
        void SetFollowObject(Transform * transform = nullptr);

        /* Move camera by using keypad */
        void ControlCamera();

        /* turn on/off screen effect */
        void ScreenShakeEffectTurnOn(bool turn_on = true, int duration = 50, float intensity = 5);
    private:
        void FollowingMovement();
        void ScreenShakeEffect();

        glm::ivec2 screenSize;
        glm::mat4 orthoMatrix;
        glm::ivec2 position;
        float rotation;
        float zoom;

        glm::mat4 cameraMatrix;

        bool needUpdate;
        bool isChange;

        // screen effects
        ScreenShake screenshake;
        FollowObject follow;

        //Camera Control
        Input input = Input::GetInstance();
    };
}
