#include "PlayerProjectile.h"

PlayerProjectile::PlayerProjectile(     Position<double> p, 
                                        SpriteSize size, 
                                        SpriteColorFormat format) :
    Sprite(NULL, p, size, format)
{
    this->pos = p;
	this->size = size;
	this->format = format;
	this->oam = &oamSub;

    // Set acceleration and speed
    dX = dY = 0;
    maxSpeedX = 6;
    maxSpeedY = 6;

    charging = false;
    moving = false;

    SetSpriteWidthAndHeight(size);
}

PlayerProjectile::~PlayerProjectile()
{

}

void PlayerProjectile::MoveSprite(const Sprite* enemies)
{
    if(!moving)
    {
        return;
    }

    if(dX > maxSpeedX) dX = maxSpeedX;
    if(dX < -maxSpeedX) dX = -maxSpeedX;
    if(dY < -maxSpeedY) dY = -maxSpeedY;
    if(dY > maxSpeedY) dY = maxSpeedY;
    
    this->pos.y += dY;
    this->pos.x += dX;

    if(this->oam == &oamSub && this->pos.y <= SCREEN_TOP)
    {
        this->alive = false;
        this->SetOam();

        this->oam = &oamMain;
        this->alive = true;
        this->pos.y = 192 + this->pos.y;
    }
    if(moving && (this->pos.x >= SCREEN_RIGHT || this->pos.x <= SCREEN_LEFT - spriteWidth || this->pos.y <= SCREEN_TOP - spriteHeight || 
        (this->oam == &oamSub && this->pos.y >= SCREEN_BOTTOM)))
    {
        moving = false;
        this->alive = false;
        this->SetOam();

        this->alive = true;
        this->oam = &oamSub;
        this->pos.x = this->pos.y = 0;
        this->dX = this->dY = 0;
        chargeLevel = 0;
        gfx_frame = 0;
    }
}

void PlayerProjectile::DetectCollisionWithEnemies(const Sprite *enemies)
{
    
}

void PlayerProjectile::ChargeProjectile(Position<double> touchPosition)
{
    if(moving)
    {
        return;
    }

    chargingTime++;
    if(chargingTime >= 0)
    {
        gfx_frame = chargeLevel = 0;
    }
    if(chargingTime >= 100)
    {
        gfx_frame = chargeLevel = 1;
    }
    if(chargingTime >= 200)
    {
        gfx_frame = chargeLevel = 2;
        chargingTime--;
    }

    this->oam = &oamSub;
    this->alive = true;
    charging = true;
    // Determine the charge level
    
    touchPosition.x -= 8;
    touchPosition.y -= 8;

    // Set the dy, dx for the projectile
    dX = touchPosition.x - this->pos.x;
    dY = touchPosition.y - this->pos.y;
    this->pos = touchPosition;
}

void PlayerProjectile::ReleaseProjectile()
{
    chargingTime = 0;
    charging = false;
    moving = true;
    if(dY == 0 && dX == 0)
    {
        moving = false;
        charging = false;
    }
}

void PlayerProjectile::Animate()
{
    if(this->oam == &oamMain)
    {
        this->currentGfxFrame = this->sprite_gfx_mem_main[gfx_frame];
    }
    if(this->oam == &oamSub)
    {
        this->currentGfxFrame = this->sprite_gfx_mem_sub[gfx_frame];    
    }
    this->SetOam();
}

void PlayerProjectile::KillSprite()
{
    for (int i = 0; i < 3; i++)
    {
        oamFreeGfx(&oamMain, this->sprite_gfx_mem_main[i]);
        oamFreeGfx(&oamSub, this->sprite_gfx_mem_sub[i]);
    }
}

void PlayerProjectile::Allocate(const u8* gfx_mem)
{
    gfx_mem += 16*32*12; // skip main character sprite
    for(int i = 0; i < 3; i++)
    {
        {
            sprite_gfx_mem_main[i] = oamAllocateGfx(&oamMain, this->size, this->format);
            sprite_gfx_mem_sub[i] = oamAllocateGfx(&oamSub, this->size, this->format);
            dmaCopy(gfx_mem, sprite_gfx_mem_main[i], 16*16);
            dmaCopy(gfx_mem, sprite_gfx_mem_sub[i], 16*16);
            gfx_mem += 16*32;
        }
    }
}