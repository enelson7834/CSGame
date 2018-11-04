#define ARM9
#include <nds.h>
#include <stdio.h>

enum {SCREEN_TOP = 0, SCREEN_BOTTOM = 192, SCREEN_LEFT = 0, SCREEN_RIGHT = 256};
#include "MainCharacter.h"
#define FRAMES_PER_ANIMATION 3

typedef struct
{
	int x;
	int y;

	u16* sprite_gfx_mem[12];
	int gfx_frame;

	int state;
	int anim_frame;

}Man;

void animateMan(Man *sprite)
{
	sprite->gfx_frame = sprite->anim_frame + sprite->state * FRAMES_PER_ANIMATION;
}

//---------------------------------------------------------------------
// Initializing a woman requires us to load all of her graphics frames 
// into memory
//---------------------------------------------------------------------
void initMan(Man *sprite, u8* gfx)
{
	int i;

	for(i = 0; i < 12; i++)
	{
		sprite->sprite_gfx_mem[i] = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
		dmaCopy(gfx, sprite->sprite_gfx_mem[i], 32*32);
		gfx += 32*32;
	}
}

// git adds a nice header we can include to access the data
// this has the same name as the image
//#include "LostVillage.h"
//#include "Background.h"
#include "man.h"
//#include "detective.h"

int main(void)
{
	//-----------------------------------------------------------------
	// Initialize the graphics engines
	//-----------------------------------------------------------------
    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_SPRITE);
    vramSetBankD(VRAM_D_SUB_SPRITE);

    oamInit(&oamMain, SpriteMapping_1D_128, false);
    oamInit(&oamSub, SpriteMapping_1D_128, false);

	//-----------------------------------------------------------------
	// Initialize sprites
	//-----------------------------------------------------------------
    Man ManSprite;
    MainCharacterSprite ManSprite2({0,0,0,0,0,0}, SpriteSize_32x32, SpriteColorFormat_256Color, &oamMain);
    //allocateSpriteMemory(ManSprite2, (u8*)manTiles, 3);
    initMan(&ManSprite, (u8*)manTiles);

    dmaCopy(manPal, SPRITE_PALETTE, 512);

    //mySprite detectiveSprite;
    //mySprite ManSprite;
    //createSprite(detectiveSprite, 11, 40, 0, SpriteSize_32x64, SpriteColorFormat_256Color, 0, 0, &oamMain);
    //createSprite(ManSprite, 0, 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 0, 0, &oamMain, FRAMES_PER_ANIMATION);
    //allocateSpriteMemory(detectiveSprite, (u8*)detectiveTiles, 12);
    //allocateSpriteMemory(ManSprite, (u8*)redspriteTiles, 12);

    // u8* gfx = (u8*)redspriteTiles;

    // //ManSprite.gfx = new u16*[12];
    // u16* tempGfx[12];

    // int i;

	// for(i = 0; i < 12; i++)
	// {
    //      = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
	// 	dmaCopy(gfxTiles, tempGfx[i], 32*32);
	// 	gfxTiles += 32*32;
	// }


    // set the mode for 2 text layers and two extended background layers

    // vramSetBankB(VRAM_B_MAIN_BG);
    // vramSetBankC(VRAM_C_MAIN_BG);
    // vramSetBankD(VRAM_D_MAIN_BG);
    // vramSetBankG(VRAM_G_MAIN_SPRITE);

    //dmaCopy(detectivePal, SPRITE_PALETTE, detectivePalLen);

    //int bg3 = bgInit(2, BgType_Bmp8, BgSize_B8_512x256, 0,0);

    // dmaCopy(BackgroundBitmap, bgGetGfxPtr(bg3), BackgroundBitmapLen);
    // dmaCopy(BackgroundPal, BG_PALETTE, BackgroundPalLen);

//    scroll(bg3, 256, 256);

    int keys = 0;
    int sx = 0;
    int sy = 0;
    int width = 512;
    int height = 256;

    int j = 0;

    while(!(keys & KEY_B))
    {
        if ( j >= manTilesLen ) 
            j = 0;
        scanKeys();

        keys = keysHeld();

        
        if(keys & KEY_UP){
            sy--;
            if (ManSprite.y >= SCREEN_TOP) ManSprite.y--;
            //if (ManSprite.y >= SCREEN_TOP) ManSprite2.y--;
            ManSprite.state = W_UP;
            //ManSprite2.state = W_UP;
        }
        else if(keys & KEY_DOWN){
            sy++;
            if (ManSprite.y <= SCREEN_BOTTOM) ManSprite.y++;
            //if (ManSprite2.y >= SCREEN_TOP) ManSprite2.y++;
            ManSprite.state = W_DOWN;
            //ManSprite2.state = W_DOWN;
        }
        else if(keys & KEY_LEFT){
            sx--;
            if (ManSprite.x >= SCREEN_LEFT) ManSprite.x--;
            //if (ManSprite2.x >= SCREEN_TOP) ManSprite2.x--;
            ManSprite.state = W_LEFT;
            //ManSprite2.state = W_LEFT;
        }
        else if(keys & KEY_RIGHT){
            sx++;
            if (ManSprite.x <= SCREEN_RIGHT) ManSprite.x++;
            //if (ManSprite2.x >= SCREEN_TOP) ManSprite2.x++;
            ManSprite.state = W_RIGHT;
            //ManSprite2.state = W_RIGHT;
        }
        else{
            //ManSprite.anim_frame--;
        }

        ManSprite.anim_frame++;
        if (ManSprite.anim_frame >= FRAMES_PER_ANIMATION) ManSprite.anim_frame = 0;
        animateMan(&ManSprite);
        //animateSprites();
    
        // if(sx < 0) sx = 0;
        // if(sx >= width - 256) sx = width - 1 - 256;
        // if(sy < 0) sy = 0;
        // if(sy >= height - 192) sy = height - 1 - 192;

        //bgSetScroll(bg3, sx, sy);

        //bgUpdate();

        //animateSprites();
        
		oamSet(&oamMain, 
			0, 
			ManSprite.x, ManSprite.y, 
			0, 
			0,
			SpriteSize_32x32,
			SpriteColorFormat_256Color, 
			ManSprite.sprite_gfx_mem[ManSprite.gfx_frame], 
			-1, 
			false, 
			false,
			false,
			false, 
			false);

        swiWaitForVBlank();
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);

        // consoleClear();
        // iprintf("j = %d\n", j);
        // iprintf("Tiles = %d\n", manTiles[j++]);
        // iprintf("Sprite OAM = %d\n", ManSprite.oam);
        // iprintf("Scroll x: %d Scroll y: %d\n", sx, sy);
        // iprintf("Press 'B' to exit");
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
