
@{{BLOCK(detective)

@=======================================================================
@
@	detective, 48x32@8, 
@	+ palette 256 entries, not compressed
@	+ 24 tiles Metatiled by 2x4 not compressed
@	Total size: 512 + 1536 = 2048
@
@	Time-stamp: 2018-11-18, 20:49:50
@	Exported by Cearn's GBA Image Transmogrifier, v0.8.15
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global detectiveTiles		@ 1536 unsigned chars
	.hidden detectiveTiles
detectiveTiles:
	.word 0xB61C1C1C,0xEC1CB6B6,0x1C1C1C1C,0x94EC1C1C,0x1C1C1C1C,0x00441C1C,0x1C1C1C1C,0x2699D81C
	.word 0x1C1C1C1C,0x169DEE44,0x201C1C1C,0x5DDCA4B9,0x0BF8071C,0xA024E24F,0x69D67A1C,0xC9CAD086
	.word 0x44DA4407,0x1C1C1C1C,0x5900A106,0x1C1C1C53,0x1136E5FC,0x1C1C1C42,0x1A3689A8,0x1C1C1C1C
	.word 0x7AA6A840,0x1C1C1C07,0xCE400D5C,0x1C1C1CB3,0xC4E0FA12,0x1C1CECF7,0x95A39FD4,0x1C1CEC9B
	.word 0xD972EE53,0xF5393925,0xF44EF253,0x96C695CA,0xA4A4F253,0x73D9E3D5,0xC3A4F253,0x6872BFBF
	.word 0x30A4F220,0x15C3A4A4,0x37877F01,0xABC3A471,0xDCCBEBDD,0x5FBFA4A4,0x24D946DD,0x19BFA4A4
	.word 0x86F1D24A,0x1C1CECBD,0xDCBC8B0D,0x1C1CEC6F,0x275E8B28,0x1C1C5387,0xABA3D2C9,0x1C1C2082
	.word 0x5985AA0F,0x1C1CD848,0xDA852B28,0x1C07B01B,0x274A9173,0x1CEC354E,0x5930967D,0x1C53C187

	.word 0xDCCB3C93,0x7EE7BFA4,0x089FD720,0xF54FD5BF,0x26B1581A,0x19DCCB4E,0x9D8E031C,0xDADCD94E
	.word 0xA447201C,0x84E1D94E,0xBF47531C,0x8468D9D5,0x4EC1531C,0xDA7E39E2,0xA447531C,0x7D5A3939
	.word 0x595F7D5F,0x1C1A5802,0x595F597D,0x1C1CF9BD,0x595F7DDA,0x1C1C203E,0x7D5F7D19,0x1C1C7CAD
	.word 0xD15F5919,0x1C071DAD,0xD17E5984,0x1C0701AD,0x98B4595F,0x1C0701E4,0xFB147D7D,0x1C074C72
	.word 0xE4AE531C,0x595A39E2,0xED43531C,0x595ACB39,0xFD441C1C,0x7D5FC674,0xBB1C1C1C,0x5F5FB444
	.word 0x1C1C1C1C,0x5F846353,0x1C1C1C1C,0x5F5FA553,0x1C1C1C1C,0xB5E33B53,0x1C1C1C1C,0x93BED842
	.word 0xC8D8A55F,0x1C1CC077,0x1C532F59,0x1C1C1CE9,0x1C0749A5,0x1C1C1C1C,0x1CC0B259,0x1C1C1C1C
	.word 0x1C7C4D7D,0x1C1C1C1C,0x42E9B20A,0x1C1C1C1C,0x1C42441D,0x1C1C1C1C,0x1C1C1C53,0x1C1C1C1C

	.word 0x1C1C1C1C,0x1CB6B61C,0x1C1C1C1C,0x071C1C1C,0x1C1C1C1C,0xE9421C1C,0x1C1C1C1C,0xD3C01C1C
	.word 0x1C1C1C1C,0x8EC2201C,0x1C1C1C1C,0x1EF293BB,0xEC1C1C1C,0x73C4E6B3,0xDE1A1C1C,0x618624D6
	.word 0x5307421C,0x1C1C1C42,0xF38C2CD8,0x1C1C42E9,0x04DB1252,0x1C1C42E9,0x18B8E500,0x1C1C1C54
	.word 0x66CC6417,0x1C1C1C1A,0xA2A86216,0x1C1C1C7A,0x6B06EA6F,0x1C1C1A0B,0x356612A0,0x1C1C9287
	.word 0x6F55071C,0x6E958969,0x4EB9BB1C,0xE2956EC6,0xBFAE531C,0x3971D9E4,0xA4AE531C,0xCBE4F04E
	.word 0x3CB9BB1C,0xA49D4EA4,0x7FAF071C,0xC3A4A44E,0x3C01071C,0xC3A424CA,0x8780071C,0x24A4DCC6
	.word 0x67D425A0,0x1C07AFAD,0xFCA6BCCD,0x1CEC9BC3,0x3F501096,0x1C072CC1,0x8A292A15,0x1C07B015
	.word 0x7622C937,0x1CB61D15,0x854AA037,0x1CB61DAB,0x292AA05A,0x1C07BE4D,0x15C521F5,0x1C537959

	.word 0x9C311C1C,0xC3A4C3CB,0x32531C1C,0x71A4E1CA,0x561A1C1C,0x714EA7AC,0xEF1A1C1C,0x13CA38A7
	.word 0xAEC01C1C,0xDCCB249D,0x741D071C,0x7DD9E4BF,0x7493071C,0x7D39E24E,0x7893071C,0x5A39394E
	.word 0x59AB27F5,0x1C53EB7E,0x5F5F7D59,0x1C5378AB,0x5F597D7D,0x1C5346AB,0x5F59AB84,0x1C7C3E37
	.word 0x5F5F59DA,0x071DBD37,0x5F5F597D,0x078075AB,0x5F5F7E30,0x0780ED59,0x7D7D7D30,0x07016B0A
	.word 0x7F93071C,0xAB39E2F0,0x3C1D071C,0x41C6E2D0,0xEB201C1C,0x20BDC6D9,0xB4531C1C,0x53456B7D
	.word 0x48531C1C,0x1C443B59,0xB7531C1C,0x1C532F48,0x531C1C1C,0x1C1C5353,0x1C1C1C1C,0x1C1C1C1C
	.word 0x705F59C1,0x0701942F,0xA55FA583,0x07E8BA83,0x655FA553,0x1C075353,0x655FA553,0x1C1C1CC0
	.word 0x707D6AC0,0x1C1C4231,0x7D7D3BC0,0x1C1C532F,0xE1656A53,0x1C1C53A5,0x9344531C,0x1C1C0793

	.word 0x1C1C1C1C,0x1C1C1C1C,0x1C1C1C1C,0x1C1C1C1C,0x1C1C1C1C,0xC01C1C1C,0x1C1C1C1C,0xF8BB1C1C
	.word 0x1C1C1C1C,0x8DB0BB1C,0x1C1C1C1C,0x4E46D807,0xEC1C1C1C,0xC6DF2EB3,0xAF071C1C,0xCAE7D00B
	.word 0xF8201A1C,0x1C1C1C44,0x6A1F81F8,0x1C1C53B7,0x7BBC3F00,0x1C1CBBC7,0xB86C3A00,0x1C1C0780
	.word 0xB164510C,0x1C1C072D,0x90184056,0x1C1C5379,0xE3165DE0,0x1C1C7C3E,0x23F010DF,0x1C539795
	.word 0xEE531C1C,0x39C7D0A4,0xF2531C1C,0xE2F0C64E,0xF2531C1C,0x89D0A4A4,0xF2531C1C,0x24E3BFA4
	.word 0xEE531C1C,0x873071A4,0xDD071C1C,0xA459877F,0xE8071C1C,0xA471CB7F,0xF81C1C1C,0x4ED0CB1B
	.word 0x5B5B60C4,0x07A98873,0x34C96D09,0x1CF93EE0,0x34102A09,0x1C53E6E0,0x344B969C,0x1C5347CD
	.word 0x0EC99630,0x1C538273,0xAAC53DDC,0x1C53432A,0x0C91674E,0x1CC01B5F,0x15CF1587,0x071D78AB

	.word 0x93071C1C,0xD139CB74,0xB9BB1C1C,0x81F69E13,0x47531C1C,0x38185CD1,0x47531C1C,0x6E5B8F71
	.word 0x47C01C1C,0x86D9A4A4,0x74FE071C,0xE1CBCA4E,0xEBD81C1C,0x7D39E24E,0xF27A1C1C,0x7D39C689
	.word 0x5F7D594E,0x07937859,0x5F597D30,0x07933237,0x5F597D37,0x07B0CA7D,0x5F5F5968,0xEC33897D
	.word 0x5F7D597D,0x1AE6897D,0x5F59E168,0xECD66368,0x7D30E17D,0xECBD375F,0x5F0A13A5,0xEC6F275F
	.word 0x78A9071C,0xFFC6E2D0,0x577C1C1C,0x0557E2CB,0xB2C01C1C,0x204675E3,0xB4531C1C,0x536A7D7D
	.word 0x48531C1C,0xB6D34D84,0xB2531C1C,0x1CF9705F,0x9A531C1C,0x42E96AB2,0x531C1C1C,0x1C425353
	.word 0x70B0B0B0,0x532E5A5F,0xA5440753,0x1CF8595F,0xA5531C1C,0x1CC8A55F,0xA5531C1C,0xB605305F
	.word 0x6AC01C1C,0x532F5959,0x6AC01C1C,0x44B45FAB,0xF5531C1C,0x054D4DB2,0x531C1C1C,0x53939344

	.section .rodata
	.align	2
	.global detectivePal		@ 512 unsigned chars
	.hidden detectivePal
detectivePal:
	.hword 0x0000,0x464E,0x194A,0x6AF1,0x0447,0x3DCA,0x4657,0x7B93
	.hword 0x1488,0x29D0,0x0C84,0x1D6F,0x14CB,0x6B9F,0x0C8D,0x5EFA
	.hword 0x6B7D,0x5EAE,0x35F3,0x10C6,0x2D68,0x0841,0x14AC,0x2571
	.hword 0x429C,0x1CE7,0x7FB3,0x0CC7,0x7773,0x41EB,0x0CA5,0x254D
	.hword 0x7FD4,0x35D0,0x2D6F,0x31F6,0x1508,0x210A,0x18EE,0x0C62
	.hword 0x675C,0x3191,0x56B8,0x0829,0x5270,0x45EE,0x10EA,0x2527
	.hword 0x10A5,0x62F0,0x1D4D,0x2DCD,0x0492,0x2DAE,0x4EBA,0x1083
	.hword 0x190C,0x2DF1,0x2DB9,0x0002,0x150A,0x294C,0x218F,0x4215

	.hword 0x52FE,0x1CE5,0x7B73,0x0044,0x7FF5,0x0CC9,0x150B,0x08A7
	.hword 0x0864,0x524E,0x3190,0x5276,0x420C,0x14A6,0x1509,0x14C7
	.hword 0x39D3,0x4EDD,0x1CE9,0x7FB4,0x7F92,0x422D,0x0CA9,0x214D
	.hword 0x10D1,0x1084,0x14A4,0x1CEC,0x2573,0x1D2F,0x4239,0x18C6
	.hword 0x4A54,0x294B,0x5B5F,0x18C7,0x77FF,0x0443,0x2550,0x252B
	.hword 0x18A5,0x298F,0x0001,0x214B,0x3E11,0x39CE,0x258D,0x2590
	.hword 0x1085,0x1909,0x190A,0x2D6C,0x10C8,0x2DF2,0x31B4,0x0025
	.hword 0x110A,0x04A7,0x6711,0x31D1,0x62CF,0x14A5,0x1484,0x10E9

	.hword 0x462E,0x2990,0x0485,0x7FF7,0x2529,0x39F4,0x216C,0x192B
	.hword 0x29D1,0x1D2B,0x31F9,0x046E,0x568F,0x08C8,0x0888,0x14E9
	.hword 0x39F6,0x4A97,0x62F1,0x460C,0x1D2C,0x298E,0x318D,0x29AC
	.hword 0x18E6,0x256A,0x2107,0x194E,0x216E,0x1529,0x29B2,0x3614
	.hword 0x5AD9,0x0421,0x088B,0x39B2,0x192A,0x0C64,0x14EF,0x2974
	.hword 0x4EDC,0x420D,0x0C69,0x0C63,0x4EFF,0x1D4C,0x08A6,0x4A4F
	.hword 0x462D,0x46BD,0x0422,0x6B12,0x0843,0x18E8,0x7B94,0x20E6
	.hword 0x677F,0x296A,0x0488,0x7F94,0x3DF3,0x25B0,0x4A2C,0x152A

	.hword 0x7FD5,0x0885,0x2549,0x1908,0x258F,0x5F1B,0x2DD1,0x212A
	.hword 0x7FF6,0x5297,0x258E,0x31F1,0x4678,0x3DF0,0x110B,0x6B7F
	.hword 0x29AF,0x14C6,0x0890,0x45EB,0x3E12,0x216D,0x1D4E,0x1D50
	.hword 0x66F0,0x31F2,0x2108,0x2570,0x14E7,0x4E6F,0x52B2,0x256C
	.hword 0x3DEF,0x18E7,0x2DD0,0x1D09,0x214C,0x4ADE,0x152C,0x1929
	.hword 0x460D,0x5EAF,0x1D30,0x0CC8,0x7F93,0x29B0,0x04A8,0x10CB
	.hword 0x256D,0x2575,0x0CE9,0x0844,0x2DAF,0x1CE6,0x3E36,0x2D6B
	.hword 0x6B11,0x66F1,0x0C6B,0x0865,0x2972,0x2128,0x3DEB,0x0822

@}}BLOCK(detective)
