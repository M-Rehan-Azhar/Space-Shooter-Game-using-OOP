#pragma once

#include "invader.h"

class Beta : public Invader {
public:
    Beta(Texture& texture, float h, string bomb_path, float mS): Invader(texture, h, bomb_path, 150.0f, 3.0f, 2, mS) {}
};
