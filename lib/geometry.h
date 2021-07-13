#ifndef GEOMETRY_HEADER_GUARD
#define GEOMETRY_HEADER_GUARD
 
// To be used with video mode 3

#define pos(x, y) ((x) + (y)*240)

void draw_pixel(short x, short y, short color, volatile unsigned short* screen);
void draw_around_pixel(short x, short y, short color, volatile unsigned short* screen);
void draw_line(short x1, short y1, short x2, short y2, short color, volatile unsigned short* screen);
 
#endif