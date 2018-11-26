#pragma once

#include "Sprite.h"
#include "CollisionDirection.h"

class PlayerProjectile : public Sprite
{
    public:
        PlayerProjectile(   Position<double> p, 
                            SpriteSize size, 
                            SpriteColorFormat format);
        ~PlayerProjectile();

        void MoveSprite(const Sprite* enemies);
        void ChargeProjectile(Position<double> touchPosition);
        void ReleaseProjectile();
        float GetVelocityY();
        float GetVelocityX();

    private:
        void Animate();
        void KillSprite();
        void Allocate(const u8* gfx_mem);
        void DetectCollisionWithEnemies(const Sprite *enemies);

        u16             *sprite_gfx_mem_main[3],
                        *sprite_gfx_mem_sub[3];

        float           dX, dY, 
                        maxSpeedX,
                        maxSpeedY;

		int             anim_frame  = 0,
                        gfx_frame   = 0,
                        chargingTime = 0,
                        chargeLevel = 0;

        bool            charging = false,
                        moving = false;
};