#pragma once
#include "addons.h"
#include "player.h"

class Lives : public Addons {
public:
    Lives(Texture& texture, int x, int y, float speed)
        : Addons(texture, x, y, speed, 3) {
        sprite.setScale(0.5f, 0.5f); // Adjust the size if needed
    }

    void activate(Player* player) {
        player->pLives += 1;
        cout << "Lifeline added" << endl;
    }
};
