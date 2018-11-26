#include "SpriteAnimator.h"
#include <stdio.h>

void SpriteAnimator::KillSprite(Sprite* s)
{
    sprites[s->oamId] = NULL;
    s->KillSprite();
    allocationCount--;
}

void SpriteAnimator::Allocate(Sprite* s, const u8* gfx)
{
    int id = this->FindFreeSpriteIndex();
    if (id == -1)
    {
        return;
    }

    s->Allocate(gfx);

    s->oamId = id;
    this->sprites[id] = s;
    this->allocationCount++;
}

int SpriteAnimator::FindFreeSpriteIndex()
{
	for(uint i = 0; i < SPRITE_MAX; i++)
	{
		if(sprites[i] == NULL)
			return i;
	}
	return -1;
}

void SpriteAnimator::AnimateSprites()
{
	//set oam to values required by my sprite
	for(u32 i = 0; i < allocationCount; i++) 
    {
        if(sprites[i] != NULL)
        {
		    sprites[i]->Animate();
        }
    }
}