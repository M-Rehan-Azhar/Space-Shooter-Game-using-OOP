#pragma once
#include "enemy.h"
#include "bomb.h"
#include "player.h"
#include <cmath>

class Dragon : public Enemy {
public:
    Dragon(Texture& texture, float h, string bomb_path, float bulletSpeed, float fireCooldown)
        : Enemy(texture, h, bomb_path, bulletSpeed, fireCooldown, 1.5f, 1.5f, 5) {}

    virtual void fire(float deltaTime, Player* p) override {
        timeSinceLastShot += deltaTime;
        if (timeSinceLastShot >= fireCooldown) {

            Vector2f playerPos = p->sprite.getPosition();
            Vector2f bombPos1 = { sprite.getPosition().x + (sprite.getGlobalBounds().width / 2) - 10, sprite.getPosition().y + 200 };
            Vector2f bombPos2 = { sprite.getPosition().x + (sprite.getGlobalBounds().width / 2) - 120, sprite.getPosition().y + 200 };
            Vector2f bombPos3 = { sprite.getPosition().x + (sprite.getGlobalBounds().width / 2) + 110, sprite.getPosition().y + 200 };

            Vector2f direction1 = calculateDirection(bombPos1, playerPos);
            Vector2f direction2 = calculateDirection(bombPos2, playerPos);
            Vector2f direction3 = calculateDirection(bombPos3, playerPos);

            bombs.push_back(Bomb(bombTex, bombPos1.x, bombPos1.y, bulletSpeed, 0.3f, 0.3f, direction1));
            bombs.push_back(Bomb(bombTex, bombPos2.x, bombPos2.y, bulletSpeed, 0.3f, 0.3f, direction2));
            bombs.push_back(Bomb(bombTex, bombPos3.x, bombPos3.y, bulletSpeed, 0.3f, 0.3f, direction3));

            timeSinceLastShot = 0.0f;
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

private:
    Vector2f calculateDirection(Vector2f start, Vector2f target) {
        Vector2f direction = target - start;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        return direction / length; // Normalize the direction vector
    }
};
