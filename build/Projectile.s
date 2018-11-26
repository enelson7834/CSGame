
@{{BLOCK(Projectile)

@=======================================================================
@
@	Projectile, 48x16@8, 
@	Transparent color : 00,00,00
@	+ palette 256 entries, not compressed
@	+ 12 tiles Metatiled by 2x2 not compressed
@	Total size: 512 + 768 = 1280
@
@	Time-stamp: 2018-11-24, 23:43:55
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global ProjectileTiles		@ 768 unsigned chars
	.hidden ProjectileTiles
ProjectileTiles:
	.word 0x09090909,0x09090909,0x09090909,0x09090909,0x09090909,0x13050909,0x09090909,0x1D032505
	.word 0x05090909,0x1F2D2F0D,0x25090909,0x242C1F1D,0x23050909,0x15040114,0x1D3D0909,0x0F15381F
	.word 0x09090909,0x09090909,0x09090909,0x09090909,0x091E0513,0x09090909,0x050D031D,0x09090909
	.word 0x3E0A3634,0x09090905,0x0A3B1824,0x0909050D,0x1F2B1A21,0x09090503,0x3410210F,0x0909251D
	.word 0x1D3D0909,0x0F15081F,0x03050909,0x15040114,0x25090909,0x242C1F1D,0x05090909,0x1F2D1D0D
	.word 0x09090909,0x1D032505,0x09090909,0x13050909,0x09090909,0x09090909,0x09090909,0x09090909
	.word 0x3B10210F,0x0909251D,0x1F181A21,0x09091303,0x0A3B1824,0x09091E0D,0x3E0A2D1F,0x09090905
	.word 0x050D031D,0x09090909,0x09090513,0x09090909,0x09090909,0x09090909,0x09090909,0x09090909

	.word 0x09090909,0x09090909,0x09090909,0x13050909,0x09090909,0x27162905,0x3D090909,0x153C2B2D
	.word 0x26050909,0x17070224,0x2C230909,0x3F3F1702,0x32060509,0x3F3F3F1C,0x350B0509,0x3F3F3F17
	.word 0x09090909,0x09090909,0x09090513,0x09090909,0x05123630,0x09090909,0x20180415,0x09090905
	.word 0x38211C17,0x09090520,0x15173F3F,0x09092531,0x0F3F3F3F,0x09092022,0x073F3F3F,0x09093632
	.word 0x351F0509,0x3F3F3F07,0x22201E09,0x3F3F3F0F,0x270D0909,0x3F0E0715,0x1D050909,0x391B0C01
	.word 0x05090909,0x0437191D,0x09090909,0x261D251E,0x09090909,0x051E0909,0x09090909,0x09090909
	.word 0x1C3F3F3F,0x09093604,0x1B0E3F3F,0x09092938,0x3C1C0E3F,0x0909131F,0x273C1B39,0x09090903
	.word 0x031F3804,0x09090909,0x09250326,0x09090909,0x09090905,0x09090909,0x09090909,0x09090909

	.word 0x1D0D0509,0x102B112D,0x3B1D2505,0x391B1524,0x042A1D25,0x3F0E171B,0x1B221F03,0x3F3F3F0E
	.word 0x1721182F,0x3F3F3F3F,0x3F1C042D,0x3F3F3F3F,0x3F17153B,0x3F3F3F3F,0x3F0E0227,0x3F3F3F3F
	.word 0x2A181022,0x0913032E,0x351B391C,0x1303162B,0x070E3F3F,0x3E362421,0x3F3F3F3F,0x0A180217
	.word 0x3F3F3F3F,0x3435073F,0x3F3F3F3F,0x381B0E3F,0x3F3F3F3F,0x04073F3F,0x3F3F3F3F,0x1A173F3F
	.word 0x3F0E0211,0x3F3F3F3F,0x3F0E212A,0x3F3F3F3F,0x3F07351F,0x3F3F3F3F,0x0E3A242E,0x3F3F3F3F
	.word 0x07352A03,0x3F3F3F3F,0x212C0A0D,0x3F3F0E07,0x18142805,0x0E170F35,0x2E030509,0x2135242A
	.word 0x3F3F3F3F,0x35173F3F,0x3F3F3F3F,0x1A173F3F,0x3F3F3F3F,0x10393F3F,0x3F3F3F3F,0x0121173F
	.word 0x3F3F3F3F,0x2D100F0E,0x0E3F3F3F,0x033B3C0F,0x3307170E,0x051D2704,0x2B321521,0x09131D1F

	.section .rodata
	.align	2
	.global ProjectilePal		@ 512 unsigned chars
	.hidden ProjectilePal
ProjectilePal:
	.hword 0x0000,0x6AD3,0x6229,0x779B,0x666E,0x7FDE,0x7317,0x5DE5
	.hword 0x6691,0x7FFF,0x7359,0x6AF6,0x624B,0x7BBC,0x5DE3,0x5E07
	.hword 0x668F,0x6AD4,0x7B5A,0x7BDD,0x7338,0x622B,0x6F17,0x5DE4
	.hword 0x6AB2,0x6AF5,0x624D,0x6208,0x5DE6,0x777A,0x7FFE,0x6F16
	.hword 0x7738,0x622A,0x666F,0x7B9B,0x6690,0x7BBD,0x7737,0x6AF4
	.hword 0x779C,0x7759,0x6EF4,0x6AB1,0x6AD2,0x7337,0x7358,0x7779
	.hword 0x6B14,0x6AF3,0x666D,0x6209,0x6F15,0x624C,0x6F37,0x66B0
	.hword 0x66B1,0x5E06,0x6207,0x6EF5,0x664D,0x7BDE,0x7B9C,0x5DE2

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(Projectile)