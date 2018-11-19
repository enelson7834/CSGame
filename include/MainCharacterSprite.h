#pragma once

#include "Sprite.h"
#include "CollisionDirection.h"
#include "Rectangle.h"
#include <algorithm>

#define TERMINAL_VELOCITY 1
#define MAIN_CHARACTER_SPRITE_FRAME_COUNT 1
class MainCharacterSprite : public Sprite
{
    public:
        MainCharacterSprite(    OamState* oam, 
                                Position<double> p, 
                                SpriteSize size, 
                                SpriteColorFormat format);
        ~MainCharacterSprite();

    void MoveSprite(int keys, u8* collisionMap, int mapWidth, Position<int> scroll);

    private:
        void Jump();
        void Crouch();
        void MoveLeft();
        void MoveRight();
        void Idle(); 
        void Animate();
        void KillSprite();
        void Allocate(const u8* gfx_mem);
        CollisionDirection DetectCollisionWithBackground(u8* collsionMap, int mapWidth, Position<int> scroll);

        const int tileWidth = 8;
        const int tileHeight = 8;

		SpriteState     state = W_UP;

        u16*            sprite_gfx_mem[MAIN_CHARACTER_SPRITE_FRAME_COUNT];

        Rectangle<Position<int>>   collisionRectangle = {
                        {2, 1}, // top left
                        {5, 1}, // top right
                        {5, 15}, // bottom right
                        {2, 15} // bottom left
        };

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