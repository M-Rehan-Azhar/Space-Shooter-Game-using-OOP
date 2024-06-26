#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include "bomb.h"
#include <vector>
class Player;

using namespace sf;
using namespace std;

class Enemy {
public:
    int x, y;
    float health;
    Sprite sprite;
    float bulletSpeed = 150.0f;
    float fireCooldown = 1.2f;
    float timeSinceLastShot = 0.0f;
    Texture bombTex;
    vector<Bomb> bombs;
    int type;
    RectangleShape healthBar;

    Enemy(Texture& texture, float h, string bomb_path, float bulletSpeed, float fireCooldown, float scaleX, float scaleY, int t)
        : health(h), bulletSpeed(bulletSpeed), fireCooldown(fireCooldown), timeSinceLastShot(0.0f), type(t) {
        sprite.setTexture(texture);
        sprite.setScale(scaleX, scaleY);
        bombTex.loadFromFile(bomb_path);
    }

    virtual void move(float deltaTime) {
        //float delta_x = 0, delta_y = 0;
        //sprite.move(-1, delta_y);
    }

    virtual void fire(float deltaTime, Player* p) {
        timeSinceLastShot += deltaTime;
        if (timeSinceLastShot >= fireCooldown) {
            bombs.push_back(Bomb(bombTex, sprite.getPosition().x + (sprite.getGlobalBounds().width / 2) - 8, sprite.getPosition().y, bulletSpeed, 1.3f, 1.3f));
            timeSinceLastShot = 0.0f;
        }

        for (auto it = bombs.begin(); it != bombs.end();) {
            it->update(deltaTime);
            if (it->sprite.getPosition().y > 780) {
                it = bombs.erase(it);
            } else {
                ++it;
            }
        }
    }
    virtual void displayHealth() {
        healthBar.setPosition(sprite.getPosition().x, sprite.getPosition().y - 15);
        healthBar.setFillColor(Color::Red);
        healthBar.setSize(Vector2f(60 * health / 100.f, 5)); 
    }
    bool isHit(FloatRect bulletBounds) {
        return sprite.getGlobalBounds().intersects(bulletBounds);
    }
    bool isHitWithPlayer(FloatRect playerBound) {
        return sprite.getGlobalBounds().intersects(playerBound);
    }
    void decreaseHealth(float amount) {
        health -= amount;
    }

    bool isDead() {
        return health <= 0;
    }
};
