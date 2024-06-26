#pragma once

#include "addons.h"
#include "player.h"

class Fire : public Addons {
public:
    Fire(Texture& texture, int x, int y, float speed)
        : Addons(texture, x, y, speed, 2) {
        sprite.setScale(0.5f, 0.5f); // Adjust the size if needed
    }

    void activate(Player* player) {
        player->setUpFireMode(true);
    }
};
