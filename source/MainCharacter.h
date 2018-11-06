#ifndef MAIN_CHARACTER_SPRITE
#define MAIN_CHARACTER_SPRITE

#include "sprite.h"

class MainCharacterSprite : public Sprite
{
    public:
        using Sprite::Sprite;
        ~MainCharacterSprite();
        void KillSprite();
        void Allocate(const u8* gfx_mem);

        void MoveUp();
        void MoveDown();
        void MoveLeft();
        void MoveRight();
        void Idle();
    private: 
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
    int offset = 0;
    switch (this->size) {
        case SpriteSize_8x8:
            offset = 8*8;
            break;
        case SpriteSize_8x16:
        case SpriteSize_16x8:
            offset = 16*8;
            break;
        case SpriteSize_8x32:
        case SpriteSize_16x16:
        case SpriteSize_32x8:
            offset = 32*8;
            break;
        case SpriteSize_16x32:
        case SpriteSize_32x16:
            offset = 32*16;
            break;
        case SpriteSize_32x32:
            offset = 32*32;
            break;
        case SpriteSize_32x64:
        case SpriteSize_64x32:
            offset = 64*32;
            break;
        case SpriteSize_64x64:
            offset = 64*64;
            break;
        default:
			offset = 0;
	}

    int id = this->FindFreeAllocationCount();
    if (id == -1)
    {
        return;
    }

    // allocate memory
	for(int i = 0; i < 12; i++)
	{
		this->sprite_gfx_mem[i] = oamAllocateGfx(this->oam, this->size, this->format);
		dmaCopy(gfx_mem, this->sprite_gfx_mem[i], offset);
		gfx_mem += offset;
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

    this->currentGfxFrame = this->sprite_gfx_mem[this->gfx_frame];
    this->SetOam(0, 0);
}
void MainCharacterSprite::MoveUp() {
    if (position.y >= SCREEN_TOP) position.y--;
    state = W_UP;
}
void MainCharacterSprite::MoveDown() {
    if (position.y <= SCREEN_BOTTOM) position.y++;
    state = W_DOWN;
}
void MainCharacterSprite::MoveLeft() {
    if (position.x >= SCREEN_LEFT) position.x--;
    state = W_LEFT;
}
void MainCharacterSprite::MoveRight() {
    if (position.x <= SCREEN_RIGHT) position.x++;
    state = W_RIGHT;
}
void MainCharacterSprite::Idle() {
    anim_frame--;
}
// End memory allocation/movement


void MainCharacterSprite::KillSprite() {
    sprites[this->id] = NULL;
    allocationCount--;
}

#endif