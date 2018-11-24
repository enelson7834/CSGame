#pragma once

#include "Sprite.h"
#include "CollisionDirection.h"
#include <algorithm>

#define MAIN_CHARACTER_SPRITE_FRAME_COUNT 12
class MainCharacterSprite : public Sprite
{
    public:
        MainCharacterSprite(    OamState* oam, 
                                Position<double> p, 
                                SpriteSize size, 
                                SpriteColorFormat format);
        ~MainCharacterSprite();

    void MoveSprite(int keys, const unsigned short * collisionMap, int mapWidth, Position<int> scroll);
    float GetVelocityY();
    float GetVelocityX();

    private:
        void Jump();
        void Crouch();
        void MoveLeft();
        void MoveRight();
        void Idle(); 
        void Animate();
        void KillSprite();
        void Allocate(const u8* gfx_mem);
        CollisionDirection DetectCollisionWithBackground(const unsigned short * collsionMap, int mapWidth, Position<int> scroll);

        const int tileWidth = 8;
        const int tileHeight = 8;

		SpriteState     state = W_UP;

        u16*            sprite_gfx_mem[MAIN_CHARACTER_SPRITE_FRAME_COUNT];

        float           dX, dY, 
                        maxSpeedX,
                        maxSpeedY,
                        accX, accY, 
                        decX,
                        jumpStartSpeedY;

		int             anim_frame  = 0,
                        gfx_frame   = 0;

        bool            jumping     = false,
                        moveKeyDown = false,
                        jumpKeyDown = false;
};