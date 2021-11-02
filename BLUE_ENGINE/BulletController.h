/*
*  File Name : BulletController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon
*  Brief: Basic functions for the bullet. Make, Shoot, Delete
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Object.h"

namespace BLUE
{
    class BulletController
    {
    public:
        BulletController();

        virtual void Init(Object obj) = 0;
        void Update();

        void MoveBullet();
        void SetBulletPosition();
        void ReplaySetBulletPosition(glm::vec2 mousePos, glm::vec3 playerPos, glm::vec2 cameraPos);
        void Reset();

        void PoisonBulletPosition(glm::vec2 direction, Transform* plantTransform);

        void DeleteWhenCollide(int count);

        int mouseX, mouseY;

        std::vector<float> angle;
        std::vector<Object*> bullet;
        std::vector<Transform*> bullet_transform;
        std::vector<Sprite*> bullet_sprite;
        std::vector<Collision*> bullet_collision;
        std::vector<Rectangle*> bullet_rectangle;
        std::vector<Line2D*> bullet_line;
        std::vector<int> lifetime;

        unsigned bulletcount = 0;

        Object player;
    };

    //class RemainBullet
    //{
    //public:
    //    RemainBullet();
    //    void Init();
    //    void SetBulletNum(int use_num);
    //    int used_bullet_num;
    //    static constexpr int bullet_limit = 10;
    //private:
    //    int size;
    //    Object * object;
    //    Transform * transform;
    //    Sprite * sprite;
    //};
}
