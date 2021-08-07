#ifndef GEOMETRY_HEADER_GUARD
#define GEOMETRY_HEADER_GUARD

#include "hardware_consts/gba_memory_map.h"

// To be used with video mode 3

#define pos(x, y) ((x) + (y)*240)

void draw_pixel(short x, short y, short color, Mem_ptr screen);
void draw_around_pixel(short x, short y, short color, Mem_ptr screen);
void draw_line(short x1, short y1, short x2, short y2, short color, Mem_ptr screen);
 
#endif