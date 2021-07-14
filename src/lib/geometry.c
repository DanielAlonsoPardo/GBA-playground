#include <stdlib.h>
#include "geometry.h"

void draw_pixel(short x, short y, short color, volatile unsigned short* screen) {
  if (x >= 0 && x < 240 && y >= 0 && y < 180) //must be inside screen
    screen[pos(x, y)] = color;
}

void draw_around_pixel(short x, short y, short color, volatile unsigned short* screen) {
  for (int i = -1; i < 2; i++)
    for (int j = -1; j < 2; j++)
      if (j != 0 || i != 0)
        draw_pixel(x + i, y + j, color, screen);
}

void draw_line(short x1, short y1, short x2, short y2, short color, volatile unsigned short* screen) {

  draw_pixel(x1, y1, color, screen);

  // Choose what directions to nudge the brush in
  short diff_x = x2 - x1;
  short diff_y = y2 - y1;

  short more_x;
  short more_y;
  short less_x;
  short less_y;

  if (diff_x > 0 && diff_y >= 0) {
    more_x = 0;
    more_y = 1;
    less_x = 1;
    less_y = 0;
  } else if (diff_x <= 0 && diff_y > 0) {
    more_x = -1;
    more_y = 0;
    less_x = 0;
    less_y = 1;
  } else if (diff_x < 0 && diff_y <= 0) {
    more_x = 0;
    more_y = -1;
    less_x = -1;
    less_y = 0;
  } else {
    more_x = 1;
    more_y = 0;
    less_x = 0;
    less_y = -1;
  }

  // Draw the line pixel by pixel
  short brush_x = x1;
  short brush_y = y1;

  short brush_angle = 0;
  short true_angle = 0;
  short brush_angle_increase = more_y * diff_x;
  short brush_angle_decrease = less_y * diff_x;
  short true_angle_increase = more_x * diff_y;
  short true_angle_decrease = less_x * diff_y;

  while(!(brush_x == x2 && brush_y == y2)) {
    if (brush_angle >= true_angle) {
      //move brush so as to decrease angle
      brush_x += less_x;
      brush_y += less_y;
      //recalc angles
      brush_angle += brush_angle_decrease;
      true_angle += true_angle_decrease;
    } else {
      //move brush so as to increase angle
      brush_x += more_x;
      brush_y += more_y;
      //recalc angles
      brush_angle += brush_angle_increase;
      true_angle += true_angle_increase;
    }
    draw_pixel(brush_x, brush_y, color, screen);
  }

}