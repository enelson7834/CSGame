#pragma once

#include "Sprite.h"
#include <algorithm>

#define TERMINAL_VELOCITY 1

class MainCharacterSprite : public Sprite
{
    public:
        using Sprite::Sprite;
        ~MainCharacterSprite();

        void MoveSprite(int keys);

    private:
        void Jump();
        void RightJump();
        void LeftJump();
        void Crouch();
        void MoveLeft();
        void MoveRight();
        void Idle(); 
        void Animate();
        void KillSprite();
        void Allocate(const u8* gfx_mem);
        bool DetectCollision(u8* collsionMap, int mapWidth, u16* collsionTiles, u8* collsionPal, Position<int> scroll, Direction dir);

		SpriteState     state = W_UP;
        u16*            sprite_gfx_mem[12];
        float           dx, dy;
		int             anim_frame  = 0,
                        gfx_frame   = 0,
                        width       = 32,
                        height      = 32;
};