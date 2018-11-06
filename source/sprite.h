#ifndef SPRITEUTIL_H_
#define SPRITEUTIL_H_

#define ARM9
#include <nds.h>

//our very simple sprite engine...
#define  SPRITE_MAX 128

enum SpriteState {W_UP = 0, W_RIGHT = 1, W_DOWN = 2, W_LEFT = 3, IDLE = 4};

struct Position{
	int x, y;
	int dx, dy;
};

//this is our game entity. Notice it has a bit more info than
//would fit into OAM.  This method is a lot more flexible than trying
//to treat oam as a game object directly.
class Sprite
{
	public:
		Sprite(Position p, SpriteSize size, SpriteColorFormat format, OamState* oam);

		virtual void SetOam(int priority, int palette_alpha);

        virtual void KillSprite() = 0;
		virtual void Animate() = 0;
		virtual void Allocate(const u8* gfx) = 0;

		friend void animateSprites();

	protected:
		Position position;
        u16* currentGfxFrame;
		SpriteColorFormat format;
		SpriteSize size;
		OamState* oam;

		SpriteState state = W_UP;
		int anim_frame = 0;
		bool alive = false;
		int gfx_frame = 0;
		int id = 0;

		int FindFreeAllocationCount();
};

//an array of sprites
Sprite* sprites[SPRITE_MAX] = {NULL};
u32 allocationCount = 0;

//a sprite constructor
Sprite::Sprite(Position position, SpriteSize size, SpriteColorFormat format, OamState* oam) {
	this->position = position;
	this->size = size;
	this->format = format;
	this->oam = oam;
}

int Sprite::FindFreeAllocationCount()
{
	for(int i = 0; i < SPRITE_MAX; i++)
	{
		if(sprites[i] == NULL)
			return i;
	}
	return -1;
}

void Sprite::SetOam(int priority, int palette_alpha)
{
    //void oamSet(OamState *oam, int id, int x, int y, int priority, int palette_alpha, SpriteSize size, SpriteColorFormat format, const void *gfxOffset, int affineIndex, bool sizeDouble, bool hide, bool hflip, bool vflip, bool mosaic)	
    oamSet(this->oam, 
        this->id, 
        this->position.x, this->position.y, 
        priority, 
        palette_alpha,
        this->size,
        this->format, 
        this->currentGfxFrame, 
        -1, 
        false, 
        false,
        false,
        false, 
        false);
}

void animateSprites()
{
	//set oam to values required by my sprite
	for(u32 i = 0; i < allocationCount; i++) {
		sprites[i]->Animate();
	}
}

// //sprite deconstructor
// void killSprite(mySprite& s) {
// 	s.alive = false;  
 
// 	//api: free the graphics
// 	if(s.sprite_gfx_mem) {	
// 		oamFreeGfx(s.oam, s.sprite_gfx_mem);
// 		spriteMemoryUsage -= (s.size & 0xFFF) << 5;
// 	}

// 	s.sprite_gfx_mem = 0;
//     if (s.sprite_gfx_mem != NULL)
//     {
//         delete s.sprite_gfx_mem;
//     }
// }

#endif /* SPRITEUTIL_H_ */
