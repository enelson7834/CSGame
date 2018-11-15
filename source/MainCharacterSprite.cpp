#include "MainCharacterSprite.h"

//---- Constructor/Destructor -------------------------------------------------
//  
//-----------------------------------------------------------------------------
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
    // allocate memory for 12 frames
	for(int i = 0; i < 12; i++)
	{
		this->sprite_gfx_mem[i] = oamAllocateGfx(this->oam, this->size, this->format);
		dmaCopy(gfx_mem, this->sprite_gfx_mem[i], 32*32);
		gfx_mem += 32*32;
	}
}

void MainCharacterSprite::Animate() 
{
    this->anim_frame++;
    if( this->anim_frame >= 3 ) {
        this->anim_frame = 0;
    }
	this->gfx_frame = this->anim_frame + this->state * 3;
    this->pos.y += this->dy;
    this->pos.x += this->dx;

    if (this->pos.x >= SCREEN_RIGHT) {
        this->pos.x = SCREEN_RIGHT ; 
    }
    if (this->pos.x <= SCREEN_LEFT) { 
        this->pos.x = SCREEN_LEFT;
    }

    if (this->pos.y <= SCREEN_TOP) {
        this->pos.y = SCREEN_TOP;
    }
    if (this->pos.y >= SCREEN_BOTTOM) {
        this->pos.y = SCREEN_BOTTOM;
    }

    this->currentGfxFrame = this->sprite_gfx_mem[this->gfx_frame];
    this->SetOam();
}

void MainCharacterSprite::MoveSprite(int keys) 
{
    if(keys & KEY_UP){
        Jump();
    }
    else if(keys & KEY_DOWN){
        Crouch();
    }
    else if(keys & KEY_LEFT){
        MoveLeft();
    }
    else if(keys & KEY_RIGHT){
        MoveRight();
    }
    else{
        Idle();
    }
}

//---- Main character sprite movement -----------------------------------------
//  
//-----------------------------------------------------------------------------
void MainCharacterSprite::Jump() 
{
    this->dy = std::max(this->dy - 0.1, -1.0 * TERMINAL_VELOCITY);
    this->state = W_UP;
}
void MainCharacterSprite::RightJump() 
{

}
void MainCharacterSprite::LeftJump() 
{

}
void MainCharacterSprite::Crouch() 
{
    this->dy = std::min(this->dy + 0.1, (double) TERMINAL_VELOCITY);
    this->state = W_DOWN;
}
void MainCharacterSprite::MoveLeft() 
{
    this->dx = std::max(this->dx - 0.1, -1.0 * TERMINAL_VELOCITY);
    this->state = W_LEFT;
}
void MainCharacterSprite::MoveRight() 
{
    this->dx = std::min(this->dx + 0.1, (double) TERMINAL_VELOCITY);
    this->state = W_RIGHT;
}
void MainCharacterSprite::Idle() 
{
    this->dx = this->dy = 0;
    anim_frame--;
}
// End memory allocation/movement

bool MainCharacterSprite::DetectCollision(u8* collsionMap, int mapWidth, u16* collsionTiles, u8* collsionPal, Position<int> scroll, Direction dir)
{
    static const int tileWidth  = 8;
    static const int tileHeight = 8;

    int xpos, ypos;
    int mapx, mapy, tilex, tiley, palx, paly;

    mapx = this->pos.x / tileWidth;
    mapy = this->pos.y / tileHeight;
    int mapval = mapx + (mapy * mapWidth);

    return false;
}

void MainCharacterSprite::KillSprite() 
{
    for (int i = 0; i < 12; i++)
    {
        oamFreeGfx(this->oam, this->sprite_gfx_mem[i]);
    }
}