#include "EnemyProjectile.h"
#include "stdio.h"

EnemyProjectile::EnemyProjectile(       Position<double> p, 
                                        SpriteSize size, 
                                        SpriteColorFormat format) :
    Sprite(&oamMain, p, size, format)
{
    this->pos = p;
	this->size = size;
	this->format = format;
	this->oam = &oamMain;
    this->alive = false;

    // Set acceleration and speed
    dX = dY = 0;
    maxSpeedX = 3;
    maxSpeedY = 3;

    moving = false;

    SetSpriteWidthAndHeight(size);
}

EnemyProjectile::~EnemyProjectile()
{

}

void EnemyProjectile::SetPosition(Position<double> p)
{
    this->pos = p;
}

void EnemyProjectile::MoveSprite(const Sprite* Player)
{
    if(!moving)
    {
        return;
    }

    chargingTime++;
    if(chargingTime >= 0)
    {
        gfx_frame = 0;
    }
    if(chargingTime >= 10)
    {
        gfx_frame = 1;
    }
    if(chargingTime >= 20)
    {
        gfx_frame = 2;
    }
    if(chargingTime >= 30)
    {
        chargingTime = 0;
    }

    if(dX > maxSpeedX) dX = maxSpeedX;
    if(dX < -maxSpeedX) dX = -maxSpeedX;
    if(dY < -maxSpeedY) dY = -maxSpeedY;
    if(dY > maxSpeedY) dY = maxSpeedY;
    
    this->pos.y += dY;
    this->pos.x += dX;

    if(moving && (this->pos.x >= SCREEN_RIGHT || this->pos.x <= SCREEN_LEFT - spriteWidth || this->pos.y <= SCREEN_TOP - spriteHeight || this->pos.y >= SCREEN_BOTTOM))
    {
        // reset sprite when it goes off screen
        moving = false;
        this->alive = false;
        this->SetOam();
        this->dX = this->dY = 0;
        chargingTime = 0;
        gfx_frame = 0;
    }
}

void EnemyProjectile::Animate()
{
    this->currentGfxFrame = this->sprite_gfx_mem[gfx_frame];
    this->SetOam();
}

void EnemyProjectile::KillSprite()
{
    for (int i = 0; i < 3; i++)
    {
        oamFreeGfx(&oamMain, this->sprite_gfx_mem[i]);
    }
}

void EnemyProjectile::Allocate(const u8* gfx_mem)
{
    gfx_mem += 16*32*22; // skip main character sprite
    for(int i = 0; i < 3; i++)
    {
        {
            sprite_gfx_mem[i] = oamAllocateGfx(&oamMain, this->size, this->format);
            dmaCopy(gfx_mem, sprite_gfx_mem[i], 16*16);
            gfx_mem += 16*32;
        }
    }
}