#include "MainCharacterSprite.h"
#include <stdio.h>

//---- Constructor/Destructor -------------------------------------------------
//  
//-----------------------------------------------------------------------------
MainCharacterSprite::MainCharacterSprite(   OamState* oam, 
                                            Position<double> p, 
                                            SpriteSize size, 
                                            SpriteColorFormat format) : 
    Sprite(oam, p, size, format)
{
	this->pos = p;
	this->size = size;
	this->format = format;
	this->oam = oam;

    // Set acceleration and speed
    this->dX = this->dY = 0;
    this->maxSpeedX = 2;
    this->maxSpeedY = 8;

    this->accX = 0.05;
    this->decX = 0.3; // should stop faster than it starts.

    // Set jump and gravity force
    this->jumpStartSpeedY = 7;
    accY = 0.5;

    this->jumping = false;
    this->jumpKeyDown = false;

    SetSpriteWidthAndHeight(size);
}

MainCharacterSprite::~MainCharacterSprite() 
{
    KillSprite();
}
//  End Constructor/Destructor

//---- Memory allocation and sprite animation ---------------------------------
//  
//-----------------------------------------------------------------------------
void MainCharacterSprite::Allocate(const u8 *gfx_mem) 
{
    // allocate memory for a number of frames
	for(int i = 0; i < MAIN_CHARACTER_SPRITE_FRAME_COUNT; i++)
	{
		this->sprite_gfx_mem[i] = oamAllocateGfx(this->oam, this->size, this->format);
		dmaCopy(gfx_mem, this->sprite_gfx_mem[i], spriteWidth*spriteHeight);
		gfx_mem += spriteWidth*spriteHeight;
	}
}

void MainCharacterSprite::Animate() 
{
    anim_frame++;
    switch (state)
    {
        case W_RIGHT:
        case W_LEFT:
            if( anim_frame >= 40 ) {
                anim_frame = 0;
            }
            gfx_frame = anim_frame/5 + 4;
            break;
        case IDLE:
        default:
            if( anim_frame >= 60 ) {
                anim_frame = 0;
            }
            gfx_frame = anim_frame / 15;
            break;
    }


    this->currentGfxFrame = this->sprite_gfx_mem[gfx_frame];
    this->SetOam();
}

void MainCharacterSprite::MoveSprite(int keys, const unsigned short * collisionMap, int mapWidth, Position<int> scroll) 
{
    moveKeyDown = false;

    // Jump
    if(keys & KEY_UP && !jumping && !jumpKeyDown)
    {
        Jump();
    }
    
    // update key pressed
    if(!(keys & KEY_UP))
    {
        jumpKeyDown = false;
    }

    if(keys & KEY_DOWN){
        Crouch();
    }
    if(keys & KEY_LEFT)
    {
        this->moveKeyDown = true;
        MoveLeft();
    }
    if(keys & KEY_RIGHT)
    {
        this->moveKeyDown = true;
        MoveRight();
    }

    if(dX > maxSpeedX) dX = maxSpeedX;
    if(dX < -maxSpeedX) dX = -maxSpeedX;
    if(dY < -maxSpeedY) dY = -maxSpeedY;

    dY += accY; // gravity
    
    DetectCollisionWithBackground(collisionMap, mapWidth, scroll);
    this->pos.y += dY;
    this->pos.x += dX;

    if(!moveKeyDown)
    {
        Idle();
    }

    if (this->pos.x >= SCREEN_RIGHT - spriteWidth) {
        this->pos.x = SCREEN_RIGHT - spriteWidth; 
    }
    if (this->pos.x <= SCREEN_LEFT) { 
        this->pos.x = SCREEN_LEFT;
    }

    if (this->pos.y <= SCREEN_TOP) {
        this->pos.y = SCREEN_TOP;
    }
    if (this->pos.y >= SCREEN_BOTTOM - spriteHeight) {
        this->pos.y = SCREEN_BOTTOM - spriteHeight;
        jumping = false;
    }

}

//---- Main character sprite movement -----------------------------------------
//  
//-----------------------------------------------------------------------------
void MainCharacterSprite::Jump() 
{
    jumping = true;
    jumpKeyDown = true;
    dY = -jumpStartSpeedY;

    //state = W_UP;
}
void MainCharacterSprite::Crouch() 
{
    //state = W_DOWN;
}
void MainCharacterSprite::MoveLeft() 
{
    if(dX > 0) // make turning faster
    {
        dX -= decX;
    }
    dX -= accX;

    if(state != W_LEFT)
    {
        anim_frame = 0;
    }

    state = W_LEFT;
    this->hflip = true;
}
void MainCharacterSprite::MoveRight() 
{
    if(dX < 0) // make turning faster
    {
        dX += decX;
    }
    dX += accX;

    if(state != W_RIGHT)
    {
        anim_frame = 0;
    }

    state = W_RIGHT;
    this->hflip = false;
}
void MainCharacterSprite::Idle() 
{
    if(dX < 0) dX += decX;
    if(dX > 0) dX -= decX;
    
    // The deceleration can make values that are almost zero but not quite, causing the sprite to continue moving
    // after key press has stopped
    if(dX > 0 && dX < decX) dX = 0;
    if(dX < 0 && dX > -decX) dX = 0;

    if(state != IDLE)
    {
        anim_frame = 0;
    }

    state = IDLE;
    //anim_frame--;
}
// End memory allocation/movement

CollisionDirection MainCharacterSprite::DetectCollisionWithBackground(const unsigned short *collsionMap, int mapWidth, Position<int> scroll)
{
    CollisionDirection returnVal;

                        // {2, 1}, // top left
                        // {5, 1}, // top right
                        // {5, 15}, // bottom right
                        // {2, 15} // bottom left

    int top = (2 + this->pos.y + scroll.y) / tileHeight;
    int bottom = (30 + this->pos.y + scroll.y) / tileHeight;
    int left = (2 + this->pos.x + scroll.x) / tileWidth;
    int right = (14 + this->pos.x + scroll.x) / tileWidth;

    int dIndexX = dX / tileWidth;
    int dIndexY = dY / tileHeight;
       
    // send a ray out from the points on the top of the player
    // and see if they collide with a tile.
    if(dY < 0) // sprite moving upward need to check top collision
    {
        int tempYPos = 0;
        // look along the entire width of the sprite and check all tiles that it overlaps horizontally
        // What if the sprite is between tiles and only half of it collides? We need to be able to detect this
        for(int horizontalIndex = left; horizontalIndex <= right; horizontalIndex++)
        {
            for(int verticalIndex = top; verticalIndex >= top + dIndexY - 1; verticalIndex--)
            {
                if(collsionMap[horizontalIndex + (verticalIndex * mapWidth)] != 0)
                {
                    returnVal.up = true;
                    tempYPos = std::max(tempYPos, (verticalIndex + 1) * tileHeight - scroll.y);
                    break;
                }
            }
        }

        if(returnVal.up == true)
        {
            if(this->pos.y + dY <= tempYPos)
            {
                this->pos.y = tempYPos + 1;
                dY = 0;
            }
        }
    } 
    if(dY > 0) // sprite moving down check collision
    {
        int tempYPos = 192;
        for(int horizontalIndex = left; horizontalIndex <= right; horizontalIndex++)
        {
            for(int verticalIndex = bottom; verticalIndex <= bottom + dIndexY + 1; verticalIndex++)
            {
                if(collsionMap[horizontalIndex + (verticalIndex * mapWidth)] != 0)
                {
                    returnVal.down = true;
                    tempYPos = std::min(tempYPos, (verticalIndex - 1) * tileHeight - scroll.y);
                    jumping = false;
                    break;
                }
            }
        }

        if(returnVal.down == true)
        {
            if(this->pos.y + dY >= tempYPos - spriteHeight + tileHeight)
            {
                this->pos.y = tempYPos - spriteHeight + tileHeight;
                dY = 0;
            }
        }
    }
    if(dX < 0) // sprite moving left
    {
        int tempXPos = 0;
        for(int verticalIndex = top; verticalIndex <= bottom; verticalIndex++)
        {
            for(int horizontalIndex = left; horizontalIndex >= left + dIndexX - 1; horizontalIndex--)
            {    
                if(collsionMap[horizontalIndex + (verticalIndex * mapWidth)] != 0)
                {
                    returnVal.left = true;
                    tempXPos = std::max(tempXPos, (horizontalIndex + 1) * tileWidth - scroll.x);
                    break;
                }
            }
        }

        if(returnVal.left == true)
        {
            if(this->pos.x + dX <= tempXPos)
            {
                this->pos.x = tempXPos;
                dX = 0;
            }
        }
    }
    if(dX > 0) // sprite moving right
    {
        int tempXPos = 256;
        // check right side along all y coordinates (top is smaller than bottom)
        for(int verticalIndex = top; verticalIndex <= bottom; verticalIndex++)
        {
            for(int horizontalIndex = right; horizontalIndex <= right + dIndexX + 1; horizontalIndex++)
            {
                if(collsionMap[horizontalIndex + (verticalIndex * mapWidth)] != 0)
                {
                    returnVal.right = true;
                    tempXPos = std::min(tempXPos, (horizontalIndex - 1) * tileWidth - scroll.x);
                    break;
                }
            }
        }

        if(returnVal.right == true)
        {
            if(this->pos.x + dX >= tempXPos - spriteWidth + tileWidth)
            {
                this->pos.x = tempXPos - spriteWidth + tileWidth;
                dX = 0;
            }
        }
    }
 
    return returnVal;
}


void MainCharacterSprite::KillSprite() 
{
    for (int i = 0; i < MAIN_CHARACTER_SPRITE_FRAME_COUNT; i++)
    {
        oamFreeGfx(this->oam, this->sprite_gfx_mem[i]);
    }
}