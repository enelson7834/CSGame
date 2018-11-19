#define ARM9
#include <nds.h>
#include <stdio.h>

#include "Sprite.h"
#include "SpriteAnimator.h"
#include "MainCharacterSprite.h"
#define FRAMES_PER_ANIMATION 3

// git adds a nice header we can include to access the data
// this has the same name as the image
#include "untitled.h"
#include "BlueMan.h"
#include "Background.h"
#include "man.h"
#include "detective.h"

int main(void)
{
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
    MainCharacterSprite MainCharacter(&oamMain, {0,0}, SpriteSize_8x16, SpriteColorFormat_256Color);
    animator.Allocate(&MainCharacter, (u8*) BlueManTiles);

    dmaCopy(BlueManPal, SPRITE_PALETTE, BlueManPalLen);

    // set the mode for 2 text layers and two extended background layers

    // vramSetBankB(VRAM_B_MAIN_BG);
    // vramSetBankC(VRAM_C_MAIN_BG);
    // vramSetBankD(VRAM_D_MAIN_BG);
    // vramSetBankG(VRAM_G_MAIN_SPRITE);

    //dmaCopy(detectivePal, SPRITE_PALETTE, detectivePalLen);

    int bg0 = bgInit(2, BgType_Text8bpp, BgSize_T_256x256, 0, 1);

    dmaCopy(BackgroundTiles, bgGetGfxPtr(bg0), BackgroundTilesLen);
    dmaCopy(BackgroundMap, bgGetMapPtr(bg0), BackgroundMapLen);
    dmaCopy(BackgroundPal, BG_PALETTE, BackgroundPalLen);

//    scroll(bg3, 256, 256);

    consoleDemoInit();

    int keys = 0;
    int sx = 0;
    int sy = 0;
    int width = 256;
    int height = 256;

    int j = 0;

    while(!(keys & KEY_B))
    { 
        j++;
        j %= BackgroundTilesLen;
        scanKeys();

        keys = keysHeld();

        Position<int> scroll = {0, 0};
        MainCharacter.MoveSprite(keys, (u8*) BackgroundMap, 32, scroll);
        double SpriteX = MainCharacter.GetPosition().x;
        double SpriteY = MainCharacter.GetPosition().y;
        sx = (int) SpriteX;
        sy = (int) SpriteY;


        // ManSprite.anim_frame++;
        // if (ManSprite.anim_frame >= FRAMES_PER_ANIMATION) ManSprite.anim_frame = 0;
        // animateMan(&ManSprite);
        //animateSprites();
    
        if(sx < 0) sx = 0;
        if(sx >= width - 256) sx = width - 256;
        if(sy < 0) sy = 0;
        if(sy >= height - 192) sy = height - 192;

        bgScroll(bg0, sx, sy);

        //bgUpdate();

        
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


        unsigned short backgroundTileIndex = 0;
        backgroundTileIndex = BackgroundMap[(int)(SpriteX/8) + ((int)(SpriteY/8) * 32)];

        consoleClear();
        animator.AnimateSprites();
        iprintf("X, Y = %d, %d\n", sx, sy);
        iprintf("Background Tile index @ x, y: %d\n", backgroundTileIndex);
    }
    return 0;
}

void scroll(int id, int width, int height)
{
   int keys = 0;
   int sx = 0;
   int sy = 0;

   while(!(keys & KEY_B))
   {
      scanKeys();

      keys = keysHeld();

      if(keys & KEY_UP) sy--;
      if(keys & KEY_DOWN) sy++;
      if(keys & KEY_LEFT) sx--;
      if(keys & KEY_RIGHT) sx++;

      if(sx < 0) sx = 0;
      if(sx >= width - 256) sx = width - 1 - 256;
      if(sy < 0) sy = 0;
      if(sy >= height - 192) sy = height - 1 - 192;

      swiWaitForVBlank();

      bgSetScroll(id, sx, sy);

	  bgUpdate();

      consoleClear();
      iprintf("Scroll x: %d Scroll y: %d\n", sx, sy);
      iprintf("Press 'B' to exit");
   }
}
