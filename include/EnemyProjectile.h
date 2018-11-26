#pragma once

#include "Sprite.h"
#include "CollisionDirection.h"

class EnemyProjectile : public Sprite
{
    public:
        EnemyProjectile(    Position<double> p, 
                            SpriteSize size, 
                            SpriteColorFormat format);
        ~EnemyProjectile();

        void MoveSprite(const Sprite* Player);
        void SetPosition(Position<double> p);

        void Animate();
        void KillSprite();
        void Allocate(const u8* gfx_mem);
        CollisionDirection DetectCollisionWithEnemies(const Sprite *enemies);

        u16             *sprite_gfx_mem[3];

        float           dX, dY, 
                        maxSpeedX,
                        maxSpeedY;

		int             anim_frame  = 0,
                        gfx_frame   = 0,
                        chargingTime = 0;

        bool            moving = false;

        friend class Ghost;
};