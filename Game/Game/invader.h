#pragma once

#include "enemy.h"


class Invader : public Enemy {
public:
    float moveTimer = 0.0f;
    float moveDuration = 0.7f; // Total time to move left and right
    float moveDirection = -1.0f;
    float moveSpeed = 0.0f;
    Invader(Texture& texture, float h, string bomb_path, float bulletSpeed, float fireCooldown, int type, float mS = 0.0f) 
        : Enemy(texture, h, bomb_path, bulletSpeed, fireCooldown, 0.6f, 0.6f, type) {
        moveSpeed = mS;
    }

    void move(float deltaTime) {
        moveTimer += deltaTime;

        // Switch direction every 5 seconds
        if (moveTimer >= moveDuration) {
            moveDirection *= -1.0f;
            moveTimer = 0.0f;
        }

        // Move the enemy left or right
        sprite.move(moveDirection * moveSpeed * deltaTime, 0); // Adjust 100.0f to control speed
    }

};
