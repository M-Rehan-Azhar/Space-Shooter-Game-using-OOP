#pragma once
#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "enemy.h"
#include<string.h>
#include <vector>

using namespace std;

class Player {
public:
    Texture tex;
    Sprite sprite;
    Texture bulletTex;
    Texture bulletFireTex;
    vector<Bullet> bullets;
    float speed = 0.1;
    float bulletSpeed = 500.0f;  
    float fireCooldown = 0.32f;
    float timeSinceLastShot = 0.0f;
    int x, y;
    float pHealth;
    float pLives;
    bool isPowerUpMode = false;
    bool isFireMode = false;
    float timer = 0.0f;
    float bulletDamage;
    int pScore = 0;
    string pName;
    Player(string png_path, string bullet_path)
    {   
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x = 340; y = 700;
        sprite.setPosition(x, y);
        sprite.setScale(0.75, 0.75);
        bulletTex.loadFromFile(bullet_path);
        bulletFireTex.loadFromFile("img/PNG/Effects/fire00.png");
        pHealth = 100.0f;
        pLives = 3;
    }
    // Firing bullets function
    void fire(float deltaTime) {
        timeSinceLastShot += deltaTime;
        if (timeSinceLastShot >= fireCooldown) {
            if (isPowerUpMode) {
                bulletDamage = 5.f;
                bulletSpeed = 500.0f;
                // Define angles in degrees for the spread
                float angles[] = { -45.0f, -30.0f, -15.0f, 0.0f, 15.0f, 30.0f, 45.0f };

                for (int i = 0; i < 7; ++i) {
                    float angle = angles[i];
                    float radian = angle * (3.14159265 / 180.0f);
                    float speedX = bulletSpeed * sin(radian);
                    float speedY = -bulletSpeed * cos(radian); // Negative because we want to shoot upwards

                    bullets.push_back(Bullet(bulletTex, sprite.getPosition().x + (sprite.getGlobalBounds().width / 2), sprite.getPosition().y + 20, speedX, speedY, bulletDamage));
                }
            }
            else if (isFireMode) {
                bulletDamage = 999.0f;
                bulletSpeed = 2500.0f;
                bullets.push_back(Bullet(bulletFireTex, sprite.getPosition().x + (sprite.getGlobalBounds().width / 2) - 8, sprite.getPosition().y, 0.0f, -bulletSpeed, bulletDamage));
            }
            else {
                bulletSpeed = 500.0f;
                bulletDamage = 20.f;
                bullets.push_back(Bullet(bulletTex, sprite.getPosition().x + (sprite.getGlobalBounds().width / 2) - 8, sprite.getPosition().y, 0.0f, -bulletSpeed, bulletDamage));
            }

            timeSinceLastShot = 0.0f;
        }

        for (auto it = bullets.begin(); it != bullets.end();) {
            it->update(deltaTime);
            if (it->sprite.getPosition().y < 0 || it->sprite.getPosition().x < 0 || it->sprite.getPosition().x > 780) {
                it = bullets.erase(it);
            }
            else {
                ++it;
            }
        }
    }



    void move(string s) {
        //Updating X and Y cordinates of player
        x = sprite.getPosition().x;
        y = sprite.getPosition().y;

        float delta_x = 0, delta_y = 0;

        if (s == "l")
            delta_x = -2;
        else if (s == "r")
            delta_x = 2;
        else if (s == "u")
            delta_y = -2;
        else if (s == "d")
            delta_y = 2;

        delta_x *= speed;
        delta_y *= speed;

        //cout << "X=" << x << "//Y=" << y;
     
        //Boundries of the Spaceship
        //Y Axis
        if (y > 750) {
            sprite.setPosition(x, -50);
        }
        else if (y < -50) {
            sprite.setPosition(x, 750);
        }
        //X Axis
        if (x < -50) {
            sprite.setPosition(750, y);
        }else if (x > 750) {
            sprite.setPosition(-50, y);
        }
        sprite.move(delta_x, delta_y);
    }

    bool isHit(FloatRect bombBound) {
        return sprite.getGlobalBounds().intersects(bombBound);
    }
    void setUpPowerMode(bool x) {
        if (x) {
            isPowerUpMode = true;
        }
        else {
            isPowerUpMode = false;
        }
    }
    void setUpFireMode(bool x) {
        if (x) {
            isFireMode = true;
        }
        else {
            isFireMode = false;
        }
    }

};
