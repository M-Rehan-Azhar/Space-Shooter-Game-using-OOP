#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;
using namespace std;

class Bullet {
public:
    Sprite sprite;
    float speedX;
    float speedY;
    float damage;

    Bullet(Texture& texture, float startX, float startY, float speedX, float speedY, float d)
        : speedX(speedX), speedY(speedY), damage(d) {
        sprite.setTexture(texture);
        sprite.setPosition(startX, startY);
        sprite.setScale(1.0f, 1.0f);
    
        float angle = atan2(speedY, speedX) * 180 / 3.14159265;
        sprite.setRotation(angle + 90);  
    }

    void update(float deltaTime) {
        sprite.move(speedX * deltaTime, speedY * deltaTime);
    }
};
