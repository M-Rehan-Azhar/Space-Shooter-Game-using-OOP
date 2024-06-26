#pragma once

#include "addons.h"
#include "player.h"

class Danger : public Addons {
public:
    Danger(Texture& texture, int x, int y, float speed)
        : Addons(texture, x, y, speed, 4) {
        sprite.setScale(0.5f, 0.5f); // Adjust the size if needed
    }

    void activate(Player* player) {
        player->pLives = 0;
    }
};
