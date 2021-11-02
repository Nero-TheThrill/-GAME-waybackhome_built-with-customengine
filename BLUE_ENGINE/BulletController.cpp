/*
*  File Name : BulletController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon
*  Brief: Basic functions for the bullet. Make, Shoot, Delete
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "BulletController.h"
#include "Graphics.h"
#include "PlayerController.h"
#include "ObjectController.h"

namespace BLUE
{
    BulletController::BulletController()
    {
        bullet.clear();
        bullet_rectangle.clear();
        bullet_collision.clear();
        bullet_line.clear();
        bullet_sprite.clear();
        bullet_transform.clear();
        bulletcount = 0;
        lifetime.clear();
        angle.clear();
        mouseX = 0;
        mouseY = 0;
    }

    void BulletController::Update()
    {
        int size = static_cast<int>(lifetime.size());
        for (int count = 0; count<size; count++)
        {
            lifetime.at(count) = lifetime.at(count) + 1;
            if (lifetime.at(count)>50)
            {
                GRAPHICS->DeleteSprite(bullet_sprite.at(count));
                bullet.at(count)->Destroy(bullet.at(count));
                bullet.erase(bullet.begin() + count);
                bullet_sprite.erase(bullet_sprite.begin() + count);
                bullet_collision.erase(bullet_collision.begin() + count);
                bullet_line.erase(bullet_line.begin() + count);
                bullet_rectangle.erase(bullet_rectangle.begin() + count);
                bullet_transform.erase(bullet_transform.begin() + count);
                angle.erase(angle.begin() + count);
                lifetime.erase(lifetime.begin() + count);

            }
            size = static_cast<int>(lifetime.size());
            bulletcount = static_cast<unsigned>(lifetime.size());
        }
        MoveBullet();
        OBJECT_CONTROLLER->UpdateBullet(bullet);
    }

	// move bullet to mouse directoin
    void BulletController::MoveBullet()
    {
        const int size = static_cast<int>(bullet_transform.size());
        static constexpr float speed = 10.f;

        for (int count = 0; count < size; count++)
        {
            const float x = bullet_transform.at(count)->GetTranslation().x + cosf(angle.at(count)) * speed;
            const float y = bullet_transform.at(count)->GetTranslation().y + sinf(angle.at(count)) * speed;
            const float z = bullet_transform.at(count)->GetTranslation().z;
            bullet_transform.at(count)->SetTranslation({ x,y,z });
        }
    }

	// set initial bullet position and angle to mouse
    void BulletController::SetBulletPosition()
    {
        mouseX = (WINDOW_INFORMATION::GetMousePos().x);
        mouseY = -(WINDOW_INFORMATION::GetMousePos().y );

        glm::vec3 translation = player.transform->GetTranslation();
        glm::vec2 bulletline = { translation.x, translation.y };

        mouseX += static_cast<int>(translation.x + GRAPHICS->GetCamera()->GetPosition().x - PLAYER_CONTROLLER->GetTransform()->GetTranslation().x);
        mouseY -= static_cast<int>(translation.y + GRAPHICS->GetCamera()->GetPosition().y - PLAYER_CONTROLLER->GetTransform()->GetTranslation().y);

        bullet_transform.at(bulletcount)->SetTranslation(translation);
        bullet_line.at(bulletcount)->SetStartPoint(bulletline);
        bullet_line.at(bulletcount)->SetEndPoint(glm::vec2(mouseX, -mouseY));
        angle.push_back(atan2((float)(bullet_line.at(bulletcount)->GetEndPoint().y - (bullet_line.at(bulletcount)->GetStartPoint().y)), (float)(bullet_line.at(bulletcount)->GetEndPoint().x - (bullet_line.at(bulletcount)->GetStartPoint().x))));
    }

    void BulletController::ReplaySetBulletPosition(glm::vec2 mousePos,glm::vec3 playerPos, glm::vec2 cameraPos)
    {
        mouseX = static_cast<int>(mousePos.x);
        mouseY = static_cast<int>(mousePos.y);

        glm::vec3 translation = playerPos;
        glm::vec2 bulletline = { translation.x, translation.y };

        mouseX += static_cast<int>(translation.x + cameraPos.x - playerPos.x);
        mouseY -= static_cast<int>(translation.y + cameraPos.y - playerPos.y);

        bullet_transform.at(bulletcount)->SetTranslation(translation);
        bullet_line.at(bulletcount)->SetStartPoint(bulletline);
        bullet_line.at(bulletcount)->SetEndPoint(glm::vec2(mouseX, -mouseY));
        angle.push_back(atan2((float)(bullet_line.at(bulletcount)->GetEndPoint().y - (bullet_line.at(bulletcount)->GetStartPoint().y)), (float)(bullet_line.at(bulletcount)->GetEndPoint().x - (bullet_line.at(bulletcount)->GetStartPoint().x))));
    }


    void BulletController::Reset()
    {
        for (auto obj : bullet)
        {
            obj->Destroy(obj);
        }
        for (auto mesh : bullet_sprite)
        {
            GRAPHICS->DeleteSprite(mesh);
        }
        bullet.clear();
        bullet_rectangle.clear();
        bullet_collision.clear();
        bullet_line.clear();
        bullet_sprite.clear();
        bullet_transform.clear();
        bulletcount = 0;
        lifetime.clear();
        angle.clear();
    }

    void BulletController::PoisonBulletPosition(glm::vec2 direction, Transform* plantTransform)
    {

        glm::vec3 translation = plantTransform->GetTranslation();
        glm::vec2 bulletline = { translation.x, translation.y };


        bullet_transform.at(bulletcount)->SetTranslation(translation);
        bullet_line.at(bulletcount)->SetStartPoint(bulletline);
        bullet_line.at(bulletcount)->SetEndPoint(glm::vec2(plantTransform->GetTranslation().x+direction.x, plantTransform->GetTranslation().y-direction.y));
        angle.push_back(atan2((float)(bullet_line.at(bulletcount)->GetEndPoint().y - (bullet_line.at(bulletcount)->GetStartPoint().y)), (float)(bullet_line.at(bulletcount)->GetEndPoint().x - (bullet_line.at(bulletcount)->GetStartPoint().x))));

    }

    void BulletController::DeleteWhenCollide(int count)
    {
        GRAPHICS->DeleteSprite(bullet_sprite.at(count));
        bullet.at(count)->Destroy(bullet.at(count));
        bullet.erase(bullet.begin() + count);
        bullet_sprite.erase(bullet_sprite.begin() + count);
        bullet_collision.erase(bullet_collision.begin() + count);
        bullet_line.erase(bullet_line.begin() + count);
        bullet_rectangle.erase(bullet_rectangle.begin() + count);
        bullet_transform.erase(bullet_transform.begin() + count);
        angle.erase(angle.begin() + count);
        lifetime.erase(lifetime.begin() + count);
        bulletcount = static_cast<unsigned>(lifetime.size());

    }

    //RemainBullet::RemainBullet()
    //{
    //    used_bullet_num = 0;
    //    size = 0;
    //    object = nullptr;
    //    transform = nullptr;
    //    sprite = nullptr;
    //}

    //void RemainBullet::Init()
    //{

    //    object = OBJECT_FACTORY->CreateEmptyObject();
    //    object->SetName("Remain Bullet");
    //    object->AddComponent(new Transform());
    //    object->AddComponent(new Sprite());
    //    object->Init();
    //    transform = (object->transform);
    //    sprite =(object->sprite);
    //    transform->SetScale({ 50, 50 });
    //    transform->SetTranslation({ -400, 270, 900 });
    //    sprite->SetTexture("texture/Number/hud_10.png");
    //    sprite->isHud = true;
    //    GRAPHICS->AddSprite(sprite);
    //    used_bullet_num = 0;
    //    SetBulletNum(0);
    //}

    //void RemainBullet::SetBulletNum(int use_num)
    //{
    //    const int remain = bullet_limit - use_num;
    //    const std::string texture_path = "texture/Number/hud_" + std::to_string(remain) + ".png";
    //    sprite->SetTexture(texture_path);
    //}
}
