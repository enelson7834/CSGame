
//{{BLOCK(Background)

//======================================================================
//
//	Background, 512x256@8, 
//	+ palette 256 entries, not compressed
//	+ 31 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 1984 + 4096 = 6592
//
//	Time-stamp: 2018-11-10, 12:54:09
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BACKGROUND_H
#define GRIT_BACKGROUND_H

#define BackgroundTilesLen 1984
extern const unsigned int BackgroundTiles[496];

#define BackgroundMapLen 4096
extern const unsigned short BackgroundMap[2048];

#define BackgroundPalLen 512
extern const unsigned short BackgroundPal[256];

#endif // GRIT_BACKGROUND_H

//}}BLOCK(Background)
