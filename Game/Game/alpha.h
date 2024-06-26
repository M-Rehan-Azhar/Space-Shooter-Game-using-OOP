#pragma once

#include "invader.h"

class Alpha : public Invader {
public:
    Alpha(Texture& texture, float h, string bomb_path, float mS)
        : Invader(texture, h, bomb_path, 150.0f, 10.0f, 1, mS) {}
};

