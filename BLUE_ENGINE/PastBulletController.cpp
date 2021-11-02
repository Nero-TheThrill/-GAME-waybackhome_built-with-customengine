/*
*  File Name : PastBulletController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Controll Past Bullets. This will be inherited from bullet controller 
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "PastBulletController.h"
#include "Graphics.h"
#include "ObjectFactory.h"
#include "TexturePath.h"

namespace BLUE
{
    PastBulletController* PASTBULLET_CONTROLLER = nullptr;

    void PastBulletController::Init(Object obj)
    {
        bullet.push_back(OBJECT_FACTORY->CreateEmptyObject());
        bullet_transform.push_back(new Transform());
        bullet_sprite.push_back(new Sprite());
        bullet_collision.push_back(new Collision());
        bullet_rectangle.push_back(new Rectangle());
        bullet_line.push_back(new Line2D());
        lifetime.push_back(0);
        bullet.at(bulletcount)->SetName("PastBullet");
        bullet.at(bulletcount)->AddComponent(bullet_transform.at(bulletcount));
        bullet.at(bulletcount)->AddComponent(bullet_sprite.at(bulletcount));
        bullet.at(bulletcount)->AddComponent(bullet_collision.at(bulletcount));
        bullet.at(bulletcount)->AddComponent(bullet_rectangle.at(bulletcount));
        bullet.at(bulletcount)->AddComponent(bullet_line.at(bulletcount));
        bullet.at(bulletcount)->Init();
        bullet_sprite.at(bulletcount)->SetTexture(T(Picture::Bullet_Past));
        bullet_transform.at(bulletcount)->SetScale({ 10,10 });
        player = obj;
        SetBulletPosition();
        bulletcount = static_cast<unsigned>(bullet.size());

    }
    void PastBulletController::ReplayInit(Object obj, glm::vec2 mousePos, glm::vec3 playerPos, glm::vec2 cameraPos)
    {
        bullet.push_back(OBJECT_FACTORY->CreateEmptyObject());
        bullet_transform.push_back(new Transform());
        bullet_sprite.push_back(new Sprite());
        bullet_collision.push_back(new Collision());
        bullet_rectangle.push_back(new Rectangle());
        bullet_line.push_back(new Line2D());
        lifetime.push_back(0);
        bullet.at(bulletcount)->SetName("PastBullet");
        bullet.at(bulletcount)->AddComponent(bullet_transform.at(bulletcount));
        bullet.at(bulletcount)->AddComponent(bullet_sprite.at(bulletcount));
        bullet.at(bulletcount)->AddComponent(bullet_collision.at(bulletcount));
        bullet.at(bulletcount)->AddComponent(bullet_rectangle.at(bulletcount));
        bullet.at(bulletcount)->AddComponent(bullet_line.at(bulletcount));
        bullet.at(bulletcount)->Init();
        bullet_sprite.at(bulletcount)->SetTexture(T(Picture::Bullet_Past));
        bullet_transform.at(bulletcount)->SetScale({ 10,10 });
        player = obj;
        ReplaySetBulletPosition(mousePos, playerPos, cameraPos);
        bulletcount = static_cast<unsigned>(bullet.size());
    }
}
