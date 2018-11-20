#define ARM9
#include <nds.h>
#include <stdio.h>

#include "Sprite.h"
#include "SpriteAnimator.h"
#include "MainCharacterSprite.h"

// git adds a nice header we can include to access the data
// this has the same name as the image
#include "knight.h"
#include "Background.h"
#include "ForestBackground.h"

int main(void)
{
    touchPosition touch;
	//-----------------------------------------------------------------
	// Initialize the graphics engines
	//-----------------------------------------------------------------
    videoSetMode(MODE_0_2D | DISPLAY_BG0_ACTIVE);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankG(VRAM_G_MAIN_SPRITE);

    oamInit(&oamMain, SpriteMapping_1D_128, false);
    oamInit(&oamSub, SpriteMapping_1D_128, false);

	//-----------------------------------------------------------------
	// Initialize sprites
	//-----------------------------------------------------------------
    SpriteAnimator animator;
    MainCharacterSprite MainCharacter(&oamMain, {0,0}, SpriteSize_16x32, SpriteColorFormat_256Color);
    animator.Allocate(&MainCharacter, (u8*) knightTiles);

    dmaCopy(knightPal, SPRITE_PALETTE, knightPalLen);

    // set the mode for 2 text layers and two extended background layers

    // vramSetBankB(VRAM_B_MAIN_BG);
    // vramSetBankC(VRAM_C_MAIN_BG);
    // vramSetBankD(VRAM_D_MAIN_BG);
    // vramSetBankG(VRAM_G_MAIN_SPRITE);

    //dmaCopy(detectivePal, SPRITE_PALETTE, detectivePalLen);

	//make sure the floor is on the bottom (by default hardware layer 0 will be rendered last)
    int bg0 = bgInit(2, BgType_Text8bpp, BgSize_T_256x256, 0, 1); // collision layer
    //int bg1 = bgInit(1, BgType_Text8bpp, BgSize_T_256x256, 1, 2);

    //bgSetPriority(bg1, 1);

    dmaCopy(BackgroundTiles, bgGetGfxPtr(bg0), BackgroundTilesLen);
    dmaCopy(BackgroundMap, bgGetMapPtr(bg0), BackgroundMapLen);
    dmaCopy(BackgroundPal, BG_PALETTE, BackgroundPalLen);

    //dmaCopy(ForestBackgroundTiles, bgGetGfxPtr(bg1), ForestBackgroundTilesLen);
    //dmaCopy(ForestBackgroundMap, bgGetMapPtr(bg1), ForestBackgroundMapLen);

//    scroll(bg3, 256, 256);

    consoleDemoInit();

    int keys = 0;
    int sx = 0;
    int sy = 0;
    int width = 256;
    int height = 256;

    while(!(keys & KEY_B))
    { 
        scanKeys();

        keys = keysHeld();

        if(keys & KEY_TOUCH) 
        {
            touchRead(&touch);
        }

        Position<int> scroll = {sx, sy};
        double SpriteX = MainCharacter.GetPosition().x;
        double SpriteY = MainCharacter.GetPosition().y;
        sx = (int) SpriteX + 16;
        sy = (int) SpriteY;


        // ManSprite.anim_frame++;
        // if (ManSprite.anim_frame >= FRAMES_PER_ANIMATION) ManSprite.anim_frame = 0;
        // animateMan(&ManSprite);
        //animateSprites();
    
        if(sx < 0) sx = 0;
        if(sx >= width - 256) sx = width - 256 - 1;
        if(sy < 0) sy = 0;
        if(sy >= height - 192) sy = height - 192 - 1;

        bgSetScroll(bg0, sx, sy);

        bgUpdate();

        
		// oamSet(&oamMain, 
		// 	0, 
		// 	ManSprite.x, ManSprite.y, 
		// 	0, 
		// 	0,
		// 	SpriteSize_32x32,
		// 	SpriteColorFormat_256Color, 
		// 	ManSprite.sprite_gfx_mem[ManSprite.gfx_frame], 
		// 	-1, 
		// 	false, 
		// 	false,
		// 	false,
		// 	false, 
		// 	false);

        swiWaitForVBlank();
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);


        //unsigned short backgroundTileIndex = 0;
        //backgroundTileIndex = BackgroundMap[(int)(SpriteX/8) + ((int)(SpriteY/8) * 32)];

        consoleClear();
        iprintf("Scroll : %d, %d\n", sx, sy);
        iprintf("Touch x, y = %d, %d", touch.px, touch.py);
        MainCharacter.MoveSprite(keys, BackgroundMap, 32, scroll);

        animator.AnimateSprites();
    }
    return 0;
}