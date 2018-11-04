#ifndef MAIN_CHARACTER_SPRITE
#define MAIN_CHARACTER_SPRITE

#include "sprite.h"

class MainCharacterSprite : public Sprite
{
    public:
        using Sprite::Sprite;

    private: 
        void Allocate(const u8* gfx_mem);
        void Animate();
};

void MainCharacterSprite::Allocate(const u8 *gfx_mem)
{
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

	DynamicArrayDelete(&(this->sprite_gfx_mem));
	DynamicArrayInit(&(this->sprite_gfx_mem), 12);

	u16* temp;

	for(int i = 0; i < 12; i++)
	{
		temp = oamAllocateGfx(this->oam, this->size, this->format);
		dmaCopy(gfx_mem, temp, offset);
		DynamicArraySet(&(this->sprite_gfx_mem), i, temp);
		gfx_mem += offset;
	}

    this->id = id;
    sprites[id] = this;
    allocationCount++;
	// if(s.sprite_gfx_mem) {
	// 	spriteMemoryUsage += (s.size & 0xFFF) << 5;
	// 	oom = false;
	// } else {
	// 	oom = true;
	// 	//only a failure of the allocator if there was enough room
	// 	if(spriteMemoryUsage + ((s.size & 0xFFF) << 5) < spriteMemSize)
	// 		oomCount++;
	// }
}

void MainCharacterSprite::Animate()
{

}


#endif