/*
*  File Name : EnemyController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Control enemies. This is for just engine proof. Deprecated
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include <SDL.h>
#include <iostream>
#include "EnemyController.h"
#include "Archiver.h"


namespace BLUE
{
    extern EnemyController* ENEMY_CONTROLLER = nullptr;
    EnemyController::EnemyController()
    {
        ENEMY_CONTROLLER = this;
        enemy.clear();
        enemy_rectangle.clear();
        enemy_collision.clear();
        enemy_line.clear();
        enemy_sprite.clear();
        enemy_transform.clear();
        enemycount = 0;
        mouseX = 0;
        mouseY = 0;
    }

    void EnemyController::Init(float x, float y, float z)
    {
        std::string str("Enemy");
        enemy.push_back(OBJECT_FACTORY->CreateEmptyObject());
        enemy_transform.push_back(new Transform());
        enemy_rectangle.push_back(new Rectangle());
        enemy_sprite.push_back(new Sprite());
        enemy_collision.push_back(new Collision());
        enemy_line.push_back(new Line2D());
        enemy.at(enemycount)->SetName(str);
        enemy.at(enemycount)->AddComponent(enemy_transform.at(enemycount));
        enemy.at(enemycount)->AddComponent(enemy_rectangle.at(enemycount));
        enemy.at(enemycount)->AddComponent(enemy_sprite.at(enemycount));
        enemy.at(enemycount)->AddComponent(enemy_collision.at(enemycount));
        enemy.at(enemycount)->AddComponent(enemy_line.at(enemycount));
        enemy.at(enemycount)->Init();
       // (dynamic_cast<Sprite*>(enemy.at(enemycount)->GetComponent(ComponentType_SPRITE)))->SetTexture("texture/enemy.png");

        enemy_transform.at(enemycount)->SetTranslation({ x,y,z });
        GRAPHICS->AddSprite(enemy_sprite.at(enemycount));

        enemycount = static_cast<unsigned>(enemy.size());
    }

    void EnemyController::update()
    {

        unsigned count = 0;
        for (count = 0; count < enemycount; count++)
        {
            enemy_rectangle.at(count)->update();
        }
    }

    void EnemyController::check_collision_with(Object* obj)
    {
        unsigned count = 0;
        for (count = 0; count<enemycount; count++)
        {
            enemy_rectangle.at(count)->update();
            (obj->rectangle)->update();
            enemy_collision.at(count)->update(*enemy_rectangle.at(count), *(obj->rectangle));
            if (enemy_collision.at(count)->GetCollisionState())
            {
                enemy_sprite.at(count)->SetColor({ 0, 0, 0,255 });
                auto a = obj->rigidbody;
                a->transform->SetTranslation({ a->oldpos, 0 });
            }

        }
    }

    void EnemyController::EnemyControllerReset()
    {
        for (auto obj : enemy)
        {
            obj->Destroy(obj);
        }
        for (auto mesh : enemy_sprite)
        {
            GRAPHICS->DeleteSprite(mesh);
        }
        enemy.clear();
        enemy_rectangle.clear();
        enemy_collision.clear();
        enemy_line.clear();
        enemy_sprite.clear();
        enemy_transform.clear();
        enemycount = 0;
    }


}
