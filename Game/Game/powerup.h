#pragma once

#include "addons.h"
#include "player.h"

class PowerUp : public Addons {
public:
    bool active = false; 
    float duration = 5.0f; 
    float timer = 0.0f; 
    Player* p;
    PowerUp(Texture& texture, int x, int y, float speed)
        : Addons(texture, x, y, speed, 1) {
        sprite.setScale(0.5f, 0.5f); // Adjust the size if needed
    }

    void activate(Player* player) {
        p = player;
        active = true;
        timer = 0.0f;
        player->setUpPowerMode(true);
        cout << "Powerup Mode Activated" << endl;
    }
    void update(float deltaTime) {
        //cout << "Update::Powerup invoked" << endl;
        if (active) {
            timer += deltaTime;
            if (timer >= duration) {
                active = false;
                p->setUpPowerMode(false);
            }
        }

        // Update the position
        sprite.move(0, speed * deltaTime);
    }
};
