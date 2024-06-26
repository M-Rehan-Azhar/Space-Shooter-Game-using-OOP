#pragma once

#include "invader.h"

class Gamma : public Invader {
public:
    Gamma(Texture& texture, float h, string bomb_path, float mS)
        : Invader(texture, h, bomb_path, 150.0f, 2.0f, 3, mS) {}
};

