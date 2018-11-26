#pragma once

#include "Sprite.h"
#include "SpriteAnimator.h"
#include "Rectangle.h"
#include "PlayerProjectile.h"
#include "EnemyProjectile.h"

#include <stdlib.h>
#include <time.h>
#include <cmath>

class Ghost : public Sprite
{
    public:
        Ghost(  OamState* oam, 
                Position<double> p, 
                SpriteSize size, 
                SpriteColorFormat format);
        ~Ghost();

        EnemyProjectile projectile;

        void MoveSprite(PlayerProjectile* projectiles, Position<double> PlayerPosition);
        void TakeDamage();
        void FireProjectile(Position<double> PlayerPosition);
        float GetVelocityY();
        float GetVelocityX();

        void Spawn();

    private:
        void Animate();
        void KillSprite();
        void Allocate(const u8* gfx_mem);

        const int tileWidth = 8;
        const int tileHeight = 8;


        u16*            sprite_gfx_mem[7];

        float           dX, dY, 
                        maxSpeedX,
                        maxSpeedY,
                        accX, accY;

		int             health      = 100,
                        shootCount  = 0,
                        anim_frame  = 0,
                        gfx_frame   = 0;
};