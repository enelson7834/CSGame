#pragma once

#include <nds.h>
#include "Position.h"
#include "enums.h"

//this is our game entity. Notice it has a bit more info than
//would fit into OAM.  This method is a lot more flexible than trying
//to treat oam as a game object directly.
class Sprite
{
	public:
		Sprite(OamState* oam, Position<double> p, SpriteSize size, SpriteColorFormat format);

		Position<double> GetPosition();
		void SetPosition(Position<double> p);

	protected:
		int FindFreeSpriteIndex();
        virtual void SetSpriteWidthAndHeight(SpriteSize size);
    	virtual void SetOam();

        virtual void KillSprite() = 0;
		virtual void Animate() = 0;
		virtual void Allocate(const u8* gfx) = 0;

		//---- Oam Data -------------------------------------------------------
		//	All of the data necessary for setting the OAM is defined here.
		//	This data does not necessarily have to be used by inheriting 
		//	classes, but it is necessary for setting the oam.
		//--------------------------------------------------------------------
		OamState* 			oam;
		Position<double> 	pos;
		SpriteSize 			size;
		SpriteColorFormat 	format;
		u16* 				currentGfxFrame;
		
		int 				oamId,
							priority		= 0, 	
							palette_alpha	= 0,
							affineIndex		= -1,
                            spriteWidth     = 0,
                            spriteHeight    = 0;

		bool				sizeDouble	= false,
							alive		= true,	// alias for hide
							hflip		= false,
							vflip		= false,
							mosaic		= false;

		//---- Friend Class ---------------------------------------------------	
		//	Animator class is responsible for managing all of the active 
		//	sprites and animating them. Main loop is responsible for
		//	moving sprites.
		//--------------------------------------------------------------------
        friend class SpriteAnimator;
		
};