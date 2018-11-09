#include "Sprite.h"

//an array of sprites
Sprite* sprites[SPRITE_MAX] = {NULL};
u32 spriteIndex = 0;

//a sprite constructor
Sprite::Sprite(	OamState* oam, 
				Position<float> p 	= {0,0,0}, 
				SpriteSize size, 
				SpriteColorFormat format) {
	this->pos = p;
	this->size = size;
	this->format = format;
	this->oam = oam;
}

Position<float> Sprite::GetPosition()
{
	return this->pos;
}

int Sprite::FindFreeSpriteIndex()
{
	for(int i = 0; i < SPRITE_MAX; i++)
	{
		if(sprites[i] == NULL)
			return i;
	}
	return -1;
}

void Sprite::SetOam()
{
    //void oamSet(OamState *oam, int id, int x, int y, int priority, int palette_alpha, SpriteSize size, SpriteColorFormat format, const void *gfxOffset, int affineIndex, bool sizeDouble, bool hide, bool hflip, bool vflip, bool mosaic)	
    oamSet(		this->oam, 
				this->oamId, 
				this->pos.x, this->pos.y, 
				this->priority, 
				this->palette_alpha,
				this->size,
				this->format, 
				this->currentGfxFrame, 
				this->affineIndex, 
				this->sizeDouble, 
				!this->alive,
				this->hflip,
				this->vflip, 
				this->mosaic);
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