#ifndef GBA_IO_REGISTERS
#define GBA_IO_REGISTERS

//DISPCNT masks defined in gba_video_modes.h
#define IO_REGISTERS_DISPCNT_ADDR  IO_REGISTERS_ADDR + 0x0
#define IO_REGISTERS_VCOUNT_ADDR   IO_REGISTERS_ADDR + 0x6
#define IO_REGISTERS_KEYINPUT_ADDR IO_REGISTERS_ADDR + 0x130


// DISPCNT Masks/Utils
#define DISPCNT_BG_MODE     0x7
#define DISPCNT_DISPLAY_BG0 (1 << 8)
#define DISPCNT_DISPLAY_BG1 (1 << 9)
#define DISPCNT_DISPLAY_BG2 (1 << 10)
#define DISPCNT_DISPLAY_BG3 (1 << 11)
#define DISPCNT_DISPLAY_OBJ (1 << 12)
#define DISPCNT_WINDOW_0    (1 << 13)
#define DISPCNT_WINDOW_1    (1 << 14)

#define DISPCNT_BG_MODE_3 0x3

#define SET_VIDEO_MODE_3() (*((volatile unsigned short *)(IO_REGISTERS_DISPCNT_ADDR))) = (DISPCNT_BG_MODE_3 | DISPCNT_DISPLAY_BG2)


// KEYINPUT Masks/Utils
// 0 means pressed, 1 means released
#define KEYINPUT_A        0x0001
#define KEYINPUT_B        0x0002
#define KEYINPUT_SELECT   0x0004
#define KEYINPUT_START    0x0008
#define KEYINPUT_RIGHT    0x0010
#define KEYINPUT_LEFT     0x0020
#define KEYINPUT_UP       0x0040
#define KEYINPUT_DOWN     0x0080
#define KEYINPUT_R        0x0100
#define KEYINPUT_L        0x0200

#define KEYINPUT_ANY      0x03FF



#endif