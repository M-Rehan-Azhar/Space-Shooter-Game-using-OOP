#pragma once
#include "enemy.h"

class Monster : public Enemy {
public:
    float moveTimer = 0.0f;
    float moveDuration = 3.4f; 
    float moveDirection = -1.0f;
    float fireTimer = 0.0f;    
    bool isFiring = true;    

    Monster(Texture& texture, float h, string bomb_path, float bulletSpeed, float fireCooldown)
        : Enemy(texture, h, bomb_path, bulletSpeed, fireCooldown, 0.5f, 0.5f, 4) {}

    void move(float deltaTime) {
        moveTimer += deltaTime;


        if (moveTimer >= moveDuration) {
            moveDirection *= -1.0f;
            moveTimer = 0.0f;
        }


        sprite.move(moveDirection * 100.0f * deltaTime, 0);
    }

    virtual void fire(float deltaTime, Player* p) {
        fireTimer += deltaTime;


        if (fireTimer >= 2.0f) {
            isFiring = !isFiring;
            fireTimer = 0.0f;
        }

        if (isFiring) {
            timeSinceLastShot += deltaTime;
            if (timeSinceLastShot >= fireCooldown) {
                bombs.push_back(Bomb(bombTex, sprite.getPosition().x + (sprite.getGlobalBounds().width / 2) - 8, sprite.getPosition().y + 200, bulletSpeed, 0.3f, 0.3f));
                timeSinceLastShot = 0.0f;
            }
        }

        for (auto it = bombs.begin(); it != bombs.end();) {
            it->update(deltaTime);
            if (it->sprite.getPosition().y > 780) {
                it = bombs.erase(it);
            }
            else {
                ++it;
            }
        }
    }
};
