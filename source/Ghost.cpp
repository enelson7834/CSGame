#include "Ghost.h"
#include <stdio.h>

//---- Constructor/Destructor -------------------------------------------------
//  
//-----------------------------------------------------------------------------
Ghost::Ghost(   OamState* oam, 
                Position<double> p, 
                SpriteSize size, 
                SpriteColorFormat format) : 
    Sprite(oam, p, size, format),
    projectile({p.x,p.y}, SpriteSize_16x32, SpriteColorFormat_256Color)
{
    srand(time(NULL)); // initialize the random seed for movement

	this->pos = p;
	this->size = size;
	this->format = format;
	this->oam = oam;

    this->alive = false;

    // Set acceleration and speed
    dX = dY = 0;
    maxSpeedX = 3;
    maxSpeedY = 3;

    accX = 0.1;
    accY = 0.05;

    SetSpriteWidthAndHeight(size);
}

Ghost::~Ghost() 
{
    KillSprite();
}
//  End Constructor/Destructor

//---- Memory allocation and sprite animation ---------------------------------
//  
//-----------------------------------------------------------------------------
void Ghost::Allocate(const u8 *gfx_mem) 
{
    gfx_mem += 16*32*15;
    // allocate memory for a number of frames
	for(int i = 0; i < 7; i++)
	{
		this->sprite_gfx_mem[i] = oamAllocateGfx(this->oam, this->size, this->format);
		dmaCopy(gfx_mem, this->sprite_gfx_mem[i], spriteWidth*spriteHeight);
		gfx_mem += spriteWidth*spriteHeight;
	}
}

void Ghost::Animate() 
{
    anim_frame++;
    if( anim_frame >= 84 ) 
    {
        anim_frame = 0;
    }
    gfx_frame = anim_frame / 12;

    this->currentGfxFrame = sprite_gfx_mem[gfx_frame];
    this->SetOam();
}

void Ghost::MoveSprite(PlayerProjectile *projectile, Position<double> playerPosition) 
{
    if(!this->alive)
    {
        return;
    }

    // Move the sprite
    int moveDirection = rand() % 8;
    switch (moveDirection)
    {
        case 0: // up
            dY -= accY;
            break;
        case 1: // up-right
            dY -= accY;
            dX += accX;
            break;
        case 2: // right
            dX += accX;
            break;
        case 3: // down-right
            dY += accY;
            dX += accX;
            break;
        case 4: // down
            dY += accY;
            break;
        case 5: // down-left
            dY += accY;
            dX -= accX;
            break;
        case 6: // left
            dX -= accX;
            break;
        case 7: // up-left
            dY -= accY;
            dX -= accX;
            break;
    }

    if(dX > maxSpeedX) dX = maxSpeedX;
    if(dX < -maxSpeedX) dX = -maxSpeedX;
    if(dY < -maxSpeedY) dY = -maxSpeedY;
    if(dY > maxSpeedY) dY = maxSpeedY;
    
    //DetectCollisionWithBackground(collisionMap, mapWidth, scroll);
    this->pos.y += dY;
    this->pos.x += dX;

    if (this->pos.x >= SCREEN_RIGHT - spriteWidth) {
        this->pos.x = SCREEN_RIGHT - spriteWidth; 
        dX = -accX;
    }
    if (this->pos.x <= SCREEN_LEFT) { 
        this->pos.x = SCREEN_LEFT;
        dX = accX;
    }

    if (this->pos.y <= SCREEN_TOP) {
        this->pos.y = SCREEN_TOP;
        dY = accY;
    }
    if (this->pos.y >= SCREEN_BOTTOM/2 - 32) {
        this->pos.y = SCREEN_BOTTOM/2 - 32;
        dY = -accY;
    }
    
    // determine if the sprite needs to fire 
    shootCount++;
    if(shootCount >= 100)
    {       
        shootCount = 0;
        FireProjectile(playerPosition);
    }
}

void Ghost::Spawn()
{
    this->alive = true;
}

void Ghost::FireProjectile(Position<double> PlayerPosition)
{
    double x = PlayerPosition.x - this->pos.x;
    double y = PlayerPosition.y - this->pos.y;
    double h = sqrt(pow(x, 2) + pow(y, 2));
    double dx = 3 * x/h;
    double dy = 3 * y/h;

    projectile.alive = true;
    projectile.moving = true;
    projectile.dX = dx;
    projectile.dY = dy;
    projectile.SetPosition({this->pos.x + spriteWidth/2, this->pos.y + spriteHeight});
}

//---- Main character sprite movement -----------------------------------------
//  
//-----------------------------------------------------------------------------
// End memory allocation/movement

float Ghost::GetVelocityX()
{
    return dX;
}
float Ghost::GetVelocityY()
{
    return dY;
}

void Ghost::KillSprite() 
{
    for (int i = 0; i < 7; i++)
    {
        oamFreeGfx(this->oam, this->sprite_gfx_mem[i]);
    }
}