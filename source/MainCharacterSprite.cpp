#include "MainCharacterSprite.h"

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
    this->maxSpeedX = 3;
    this->maxSpeedY = 10;

    this->accX = 0.2;
    this->decX = 0.3; // should stop faster than it starts.

    // Set jump and gravity force
    this->jumpStartSpeedY = 8;
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
    // anim_frame++;
    // if( anim_frame >= 9 ) {
    //     anim_frame = 0;
    // }
	gfx_frame = (int)anim_frame;// + this->state * 3;

    this->currentGfxFrame = this->sprite_gfx_mem[gfx_frame];
    this->SetOam();
}

void MainCharacterSprite::MoveSprite(int keys, u8* collisionMap, int mapWidth, Position<int> scroll) 
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
    state = W_UP;
}
void MainCharacterSprite::Crouch() 
{
    state = W_DOWN;
}
void MainCharacterSprite::MoveLeft() 
{
    dX -= accX;

    state = W_LEFT;
    this->hflip = true;
}
void MainCharacterSprite::MoveRight() 
{
    dX += accX;

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

    //anim_frame--;
}
// End memory allocation/movement

CollisionDirection MainCharacterSprite::DetectCollisionWithBackground(u8* collsionMap, int mapWidth, Position<int> scroll)
{
    CollisionDirection returnVal;

                        // {2, 1}, // top left
                        // {5, 1}, // top right
                        // {5, 15}, // bottom right
                        // {2, 15} // bottom left

    int topLeftTileX = (collisionRectangle.topLeft.x + this->pos.x) / tileWidth;
    int topRightTileX = (collisionRectangle.topRight.x + this->pos.x) / tileWidth;

    int topLeftTileY = (collisionRectangle.topLeft.y + this->pos.y) / tileHeight;
    int topRightTileY = (collisionRectangle.topRight.y + this->pos.y) / tileHeight;

    int bottomLeftTileX = (collisionRectangle.bottomLeft.x + this->pos.x) / tileWidth;
    int bottomRightTileX = (collisionRectangle.bottomRight.x + this->pos.x) / tileWidth;

    int bottomLeftTileY = (collisionRectangle.bottomLeft.y + this->pos.y) / tileHeight;
    int bottomRightTileY = (collisionRectangle.bottomRight.y + this->pos.y) / tileHeight;
        
    // send a ray out from the points on the top of the player
    // and see if they collide with a tile.
    if(dY < 0) // sprite moving upward need to check top collision
    {
        //stretch top to make sure sprite doesn't pass through objects because of move
        for(int i = topLeftTileX; i <= topRightTileX; i++)
        {
            for(int j = topLeftTileY + (dY/tileHeight); j <= topLeftTileY; j++)
            {
                if(collsionMap[i + (j * mapWidth)] != 0)
                {
                    returnVal.up = true;
                    this->pos.y = i * tileHeight;
                    dY = 0;
                }
            }
        }
    } 
    if(dY > 0) // sprite moving down check collision
    {
        for(int i = bottomLeftTileX; i <= bottomRightTileX; i++)
        {
            for(int j = bottomLeftTileY; j <= bottomLeftTileY + (dY/tileHeight); j++)
            {
                if(collsionMap[i + (j * mapWidth)] != 0)
                {
                    returnVal.down = true;
                    this->pos.y = j * tileHeight;
                    jumping = false;
                    dY = 0;
                }
            }
        }
    }
    if(dX > 0) // sprite moving right
    {
        // check right side along all y coordinates (top is smaller than bottom)
        for(int i = topRightTileY; i <= bottomRightTileY; i++)
        {
            for(int j = topRightTileX - (dX / tileWidth); j <= topRightTileX; j++)
            {
                if(collsionMap[j + (i * mapWidth)] != 0)
                {
                    returnVal.right = true;
                    this->pos.x = j * tileWidth;
                    dX = 0;
                }
            }
        }
    }
    if(dX < 0) // sprite moving left
    {
        for(int i = topLeftTileY; i <= bottomLeftTileY; i++)
        {
            for(int j = topLeftTileX; j <= topLeftTileX - (dX / tileWidth); j++)
            {    
                if(collsionMap[j + (i * mapWidth)] != 0)
                {
                    returnVal.left = true;
                    this->pos.x = j * tileWidth;
                    dX = 0;
                }
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