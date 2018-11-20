
//{{BLOCK(Background)

//======================================================================
//
//	Background, 256x256@8, 
//	Transparent color : 00,00,00
//	+ palette 256 entries, not compressed
//	+ 19 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 1216 + 2048 = 3776
//
//	Time-stamp: 2018-11-20, 09:51:30
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKGROUND_H
#define GRIT_BACKGROUND_H

#define BackgroundTilesLen 1216
extern const unsigned int BackgroundTiles[304];

#define BackgroundMapLen 2048
extern const unsigned short BackgroundMap[1024];

#define BackgroundPalLen 512
extern const unsigned short BackgroundPal[256];

#endif // GRIT_BACKGROUND_H

//}}BLOCK(Background)
