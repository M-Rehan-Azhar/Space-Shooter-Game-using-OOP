#pragma once
#include "SFML/Graphics.hpp"

using namespace sf;

class Addons
{
public:
	Sprite sprite;
	float speed;
	int type;
	Addons(Texture& texture, float startX, float startY, float speed, int t)
		: speed(speed), type(t) {
		sprite.setTexture(texture);
		sprite.setPosition(startX, startY);
		sprite.setScale(1.0f, 1.0f);
		cout << "Addon Generated:: TYPE:: " << type << endl;
	}

	virtual void update(float deltaTime) {
		sprite.move(0, speed * deltaTime);
	}
	virtual void activate(Player* player) {
		//Active Implementation
	}
};

