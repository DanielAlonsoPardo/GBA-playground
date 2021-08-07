#include <stdlib.h>

#include "lib/hardware_consts/gba_memory_map.h"
#include "lib/hardware_consts/gba_io_registers.h"
#include "lib/geometry.h"



int main(void) {
  //Set video mode
  SET_VIDEO_MODE_3();

  Mem_ptr const VRAM = (unsigned short*)VRAM_ADDR;

  #define MAX_LINES 30
  struct Line {
    short x1;
    short y1;
    short x2;
    short y2;
    short color;
  } lines[MAX_LINES];
  short total_lines = 0;
  
  srand(0);

  //Enter game loop
  unsigned short frame_counter = 0;
  while(1) {
    short current_line = frame_counter % MAX_LINES;
    VCOUNT_WAIT_FOR_NEXT_FRAME();
  
    //Add a line to the lines structure
    //If it's full, replace an existing line instead.
    if (total_lines < MAX_LINES) {
      //add line
      lines[total_lines].x1 = rand() % 240;
      lines[total_lines].y1 = rand() % 160;
      lines[total_lines].x2 = rand() % 240;
      lines[total_lines].y2 = rand() % 160;
      lines[total_lines].color = rand();

      total_lines++;
    } else {
      //replace preexisting line

      //erase it first
      draw_line(lines[current_line].x1, lines[current_line].y1, lines[current_line].x2, lines[current_line].y2, 0, VRAM);

      lines[current_line].x1 = rand() % 240;
      lines[current_line].y1 = rand() % 160;
      lines[current_line].x2 = rand() % 240;
      lines[current_line].y2 = rand() % 160;
      lines[current_line].color = rand();
      draw_line(lines[current_line].x1, lines[current_line].y1, lines[current_line].x2, lines[current_line].y2, lines[current_line].color, VRAM);
    }



    //Draw all lines
//    for (short i = 0; i < total_lines; i++)
//      draw_line(lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2, lines[i].color, VRAM);

    frame_counter++;
  }

  return 0;
}
