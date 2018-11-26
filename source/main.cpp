#include <nds.h>
#include <stdio.h>

#include "Sprite.h"
#include "SpriteAnimator.h"
#include "MainCharacterSprite.h"
#include "PlayerProjectile.h"
#include "EnemyProjectile.h"
#include "Ghost.h"

// git adds a nice header we can include to access the data
// this has the same name as the image
#include "Untitled1.h"
#include "knight.h"
#include "Background.h"
#include "Projectile.h"

int main(void)
{
    Ghost *Enemies[3];
    touchPosition touch;
	//-----------------------------------------------------------------
	// Initialize the graphics engines
	//-----------------------------------------------------------------
    videoSetMode(MODE_0_2D | DISPLAY_BG0_ACTIVE);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankB(VRAM_B_MAIN_SPRITE);
    vramSetBankD(VRAM_D_SUB_SPRITE);

    oamInit(&oamMain, SpriteMapping_1D_128, false);
    oamInit(&oamSub, SpriteMapping_1D_128, false);

	//-----------------------------------------------------------------
	// Initialize sprites
	//-----------------------------------------------------------------
    SpriteAnimator animator;
    MainCharacterSprite MainCharacter1(&oamMain, {256/2,192-32}, SpriteSize_16x32, SpriteColorFormat_256Color);
    animator.Allocate(&MainCharacter1, (u8*) Untitled1Tiles);

    Ghost Enemy1(&oamMain, {0,0}, SpriteSize_16x32, SpriteColorFormat_256Color);
    Ghost Enemy2(&oamMain, {0,0}, SpriteSize_16x32, SpriteColorFormat_256Color);
    Ghost Enemy3(&oamMain, {0,0}, SpriteSize_16x32, SpriteColorFormat_256Color);

    animator.Allocate(&Enemy1, (u8*) Untitled1Tiles);
    animator.Allocate(&Enemy2, (u8*) Untitled1Tiles);
    animator.Allocate(&Enemy3, (u8*) Untitled1Tiles);
    
    animator.Allocate(&Enemy1.projectile, (u8*) Untitled1Tiles);
    animator.Allocate(&Enemy2.projectile, (u8*) Untitled1Tiles);
    animator.Allocate(&Enemy3.projectile, (u8*) Untitled1Tiles);

    Enemies[0] = &Enemy1;
    Enemies[1] = &Enemy2;
    Enemies[2] = &Enemy3;

    dmaCopy(Untitled1Pal, SPRITE_PALETTE, Untitled1PalLen);
    dmaCopy(Untitled1Pal, SPRITE_PALETTE_SUB, Untitled1PalLen);

    PlayerProjectile p1({0,0}, SpriteSize_16x16, SpriteColorFormat_256Color);
    animator.Allocate(&p1, (u8*) Untitled1Tiles);

    int keys = 0;
    int enemySpawnCount = 1000; 
    int enemyIndex = 0;
    int projectileCount = 0;
    bool PlayerProjectileCreated = false;

    while(true)
    { 
        enemySpawnCount++;
        if(enemySpawnCount >= 1000)
        {
            enemySpawnCount = 0;
            
            enemyIndex++;
            if(enemyIndex >= 4)
            {
                enemyIndex = 0;
            }

            Enemies[enemyIndex]->Spawn();
        }

        scanKeys();

        keys = keysHeld();

        if(keys & KEY_TOUCH) // on touch charge projectile
        {
            touchRead(&touch);
            if(!PlayerProjectileCreated)
            {
                // create PlayerProjectile
                PlayerProjectileCreated = true;
            }
            p1.ChargeProjectile({touch.px, touch.py});
        }
        else // on release fire projectile
        {
            p1.ReleaseProjectile();
        }

        MainCharacter1.MoveSprite(keys, BackgroundMap, 0, {0,0});
        Enemy1.MoveSprite(NULL, {MainCharacter1.GetPosition().x, MainCharacter1.GetPosition().y});
        Enemy2.MoveSprite(NULL, {MainCharacter1.GetPosition().x, MainCharacter1.GetPosition().y});
        Enemy3.MoveSprite(NULL, {MainCharacter1.GetPosition().x, MainCharacter1.GetPosition().y});

        Enemy1.projectile.MoveSprite(NULL);
        Enemy2.projectile.MoveSprite(NULL);
        Enemy3.projectile.MoveSprite(NULL);

        p1.MoveSprite(NULL);
        animator.AnimateSprites();

        swiWaitForVBlank();
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }
    return 0;
}