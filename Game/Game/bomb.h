#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Bomb {
public:
    Sprite sprite;
    float speed;
    Vector2f direction;

    Bomb(Texture& texture, float x, float y, float speed, float scaleX, float scaleY, Vector2f direction = Vector2f(0, 1))
        : speed(speed), direction(direction) {
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        sprite.setScale(scaleX, scaleY);
    }

    void update(float deltaTime) {
        sprite.move(direction * speed * deltaTime);
    }
};
