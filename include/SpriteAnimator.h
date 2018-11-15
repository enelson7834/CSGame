#pragma once
#include "Sprite.h"

#define  SPRITE_MAX 128

class SpriteAnimator
{
    public:
        void KillSprite(Sprite* s);
 		void Allocate(Sprite* s, const u8* gfx);
        void AnimateSprites();
    private:
        //an array of sprites
        Sprite* sprites[SPRITE_MAX] = {NULL};
        u32 allocationCount = 0;

        int FindFreeSpriteIndex();
};