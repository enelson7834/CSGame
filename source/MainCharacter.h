#ifndef MAIN_CHARACTER_SPRITE
#define MAIN_CHARACTER_SPRITE

#ifndef SCREEN_BOUNDARIES
#define SCREEN_BOUNDARIES
    enum {SCREEN_TOP = 0, SCREEN_BOTTOM = 192, SCREEN_LEFT = 0, SCREEN_RIGHT = 256};
#endif

enum SpriteState {W_UP = 0, W_RIGHT = 1, W_DOWN = 2, W_LEFT = 3, IDLE = 4};

#include "sprite.h"

class MainCharacterSprite : public Sprite
{
    public:
        using Sprite::Sprite;
        ~MainCharacterSprite();
        void KillSprite();
        void Allocate(const u8* gfx_mem);

        void MoveSprite(int keys);

    private:
        void IdleJump();
        void RightJump();
        void LeftJump();
        void Crouch();
        void MoveLeft();
        void MoveRight();
        void Idle(); 
        void Animate();

        u16* sprite_gfx_mem[12];
};

//-----------------------------------------------------------------------------
//  Constructor/Destructor
//-----------------------------------------------------------------------------
MainCharacterSprite::~MainCharacterSprite() {
    KillSprite();
}
//  End Constructor/Destructor

//-----------------------------------------------------------------------------
//  Memory allocation and sprite animation
//-----------------------------------------------------------------------------
void MainCharacterSprite::Allocate(const u8 *gfx_mem) {

    int id = this->FindFreeAllocationCount();
    if (id == -1)
    {
        return;
    }

    // allocate memory
	for(int i = 0; i < 12; i++)
	{
		this->sprite_gfx_mem[i] = oamAllocateGfx(this->oam, this->size, this->format);
		dmaCopy(gfx_mem, this->sprite_gfx_mem[i], 32*32);
		gfx_mem += 32*32;
	}

    this->id = id;
    sprites[id] = this;
    allocationCount++;
}

void MainCharacterSprite::Animate() {
    this->anim_frame++;
    if( this->anim_frame >= 3 ) {
        this->anim_frame = 0;
    }
	this->gfx_frame = this->anim_frame + this->state * 3;
    this->y += this->dy;
    this->x += this->dx;

    if (this->x >= SCREEN_RIGHT) {
        this->x = SCREEN_RIGHT ; 
    }
    if (this->x <= SCREEN_LEFT) { 
        this->x = SCREEN_LEFT;
    }

    if (this->y <= SCREEN_TOP) {
        this->y = SCREEN_TOP;
    }
    if (this->y >= SCREEN_BOTTOM) {
        this->y = SCREEN_BOTTOM;
    }

    this->currentGfxFrame = this->sprite_gfx_mem[this->gfx_frame];
    this->SetOam(0, 0);
}

void MainCharacterSprite::MoveSprite(int keys) {
    if(keys & KEY_UP){
        IdleJump();
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
void MainCharacterSprite::IdleJump() {
    this->dy++;
    this->state = W_UP;
}
void MainCharacterSprite::RightJump() {

}
void MainCharacterSprite::LeftJump() {

}
void MainCharacterSprite::Crouch() {
    this->dy--;
}
void MainCharacterSprite::MoveLeft() {
    this->dx--;
    this->state = W_LEFT;
}
void MainCharacterSprite::MoveRight() {
    this->dx++;
    state = W_RIGHT;
}
void MainCharacterSprite::Idle() {
    this->dx = this->dy = 0;
    anim_frame--;
}
// End memory allocation/movement


void MainCharacterSprite::KillSprite() {
    sprites[this->id] = NULL;
    allocationCount--;
}

#endif