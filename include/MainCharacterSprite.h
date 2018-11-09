#pragma once
const static enum {SCREEN_TOP = 0, SCREEN_BOTTOM = 192, SCREEN_LEFT = 0, SCREEN_RIGHT = 256};
const static enum SpriteState {W_UP = 0, W_RIGHT = 1, W_DOWN = 2, W_LEFT = 3, IDLE = 4};

const static enum struct Direction {Up = 0, Right = 1, Down = 2, Left = 3};
inline Direction operator| (Direction a, Direction b) {
    return static_cast<Direction>(static_cast<int>(a) | static_cast<int>(b));
}

#include "Sprite.h"
#include <algorithm>

#define TERMINAL_VELOCITY 1

class MainCharacterSprite : public Sprite
{
    public:
        using Sprite::Sprite;
        ~MainCharacterSprite();

        void KillSprite();
        void Allocate(const u8* gfx_mem);

        void MoveSprite(int keys);

    private:
        void IdleJump();
        void RightJump();
        void LeftJump();
        void Crouch();
        void MoveLeft();
        void MoveRight();
        void Idle(); 
        void Animate();

		SpriteState     state = W_UP;
        u16*            sprite_gfx_mem[12];
        float           dx, dy;
		int             anim_frame  = 0,
                        gfx_frame   = 0,
                        width       = 32,
                        height      = 32;
};