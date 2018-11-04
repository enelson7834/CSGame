#ifndef SPRITEUTIL_H_
#define SPRITEUTIL_H_

#define ARM9
#include <nds.h>

//our very simple sprite engine...
#define  SPRITE_MAX 128

enum SpriteState {W_UP = 0, W_RIGHT = 1, W_DOWN = 2, W_LEFT = 3, IDLE = 4};

struct Position{
	int x, y, z;
	int dx, dy, dz;
};

//this is our game entity. Notice it has a bit more info than
//would fit into OAM.  This method is a lot more flexible than trying
//to treat oam as a game object directly.
class Sprite
{
	public:
		Sprite(Position p, SpriteSize size, SpriteColorFormat format, OamState* oam);
		~Sprite();

		Position GetPosition() const;
		void SetPosition(const Position p);

		void KillSprite();
		void SetOam();

		virtual void Animate() = 0;
		virtual void Allocate(const u8* gfx) = 0;

		friend void animateSprites();

	protected:
		Position position;
		DynamicArray sprite_gfx_mem;
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

u32 spriteMemoryUsage = 0;

u32 oomCount = 0;
u32 allocationCount = 0;
u32 spriteMemSize = 128 * 1024;

bool oom = false;

//a sprite constructor
Sprite::Sprite(Position position, SpriteSize size, SpriteColorFormat format, OamState* oam) {
	this->position = position;
	this->size = size;
	this->format = format;
	this->oam = oam;
}

Sprite::~Sprite()
{
	this->KillSprite();
}

void Sprite::KillSprite()
{
	DynamicArrayDelete(&(this->sprite_gfx_mem));

	sprites[this->id] = NULL;
	allocationCount--;
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

// //a qsort function which sorts on z order
// int zsort(const void* a, const void* b) {
// 	mySprite *first = (mySprite*)a;
// 	mySprite *second = (mySprite*)b;

// 	//the trivial case 
// 	if(first == second) return 0;

// 	//handle nulls
// 	if(!first && second) return -1;
// 	if(first && !second) return 1;

// 	//a dead sprite is always after a living one in the sort
// 	if(!first->alive && second->alive) return -1;
// 	if(first->alive && !second->alive) return 1;
// 	if(!first->alive && !second->alive) return 0;

// 	//finally if both are alive and not null sort them by depth
// 	if(first->z == second->z) return 0;
// 	if(first->z < second->z ) return -1;
// 	if(first->z > second->z) return 1;

// 	return 0; 
// }  

void animateSprites()
{
	//sort our sprites on z
	//a more efficient way would be to keep a sorted list of sprites
	//qsort(sprites, SPRITE_MAX, sizeof(mySprite), zsort);


	//set oam to values required by my sprite
	for(u32 i = 0; i < allocationCount; i++) {
		// sprites[i]->anim_frame++;
		// if( sprites[i]->anim_frame >= sprites[i]->framesPerAnimation )
		// 	sprites[i]->anim_frame = 0;
		// sprites[i]->gfx_frame = sprites[i]->anim_frame 	+
		// 						sprites[i]->state		* 
		// 						sprites[i]->framesPerAnimation;

		//an api function: void oamSet(OamState* oam, int id,  int x, int y, int priority, int palette_alpha, SpriteSize size, SpriteColorFormat format, const void* gfxOffset, int affineIndex, bool sizeDouble, bool hide);
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
