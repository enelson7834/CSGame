
//{{BLOCK(Background)

//======================================================================
//
//	Background, 512x512@8, 
//	Transparent color : 00,00,00
//	+ palette 256 entries, not compressed
//	+ 8 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 512 + 512 + 8192 = 9216
//
//	Time-stamp: 2018-11-24, 23:43:55
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKGROUND_H
#define GRIT_BACKGROUND_H

#define BackgroundTilesLen 512
extern const unsigned int BackgroundTiles[128];

#define BackgroundMapLen 8192
extern const unsigned short BackgroundMap[4096];

#define BackgroundPalLen 512
extern const unsigned short BackgroundPal[256];

#endif // GRIT_BACKGROUND_H

//}}BLOCK(Background)
