
//{{BLOCK(ForestBackground)

//======================================================================
//
//	ForestBackground, 512x256@8, 
//	+ palette 256 entries, not compressed
//	+ 645 tiles (t|f reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 41280 + 4096 = 45888
//
//	Time-stamp: 2018-11-23, 12:54:02
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FORESTBACKGROUND_H
#define GRIT_FORESTBACKGROUND_H

#define ForestBackgroundTilesLen 41280
extern const unsigned int ForestBackgroundTiles[10320];

#define ForestBackgroundMapLen 4096
extern const unsigned short ForestBackgroundMap[2048];

#define ForestBackgroundPalLen 512
extern const unsigned short ForestBackgroundPal[256];

#endif // GRIT_FORESTBACKGROUND_H

//}}BLOCK(ForestBackground)
