#include <stdlib.h>

#include "lib/hardware_consts/gba_memory_map.h"
#include "lib/hardware_consts/gba_io_registers.h"
#include "lib/geometry.h"



int main(void) {
  //Set video mode
  SET_VIDEO_MODE_3();

  volatile unsigned short* const VRAM = (unsigned short*)VRAM_ADDR;

  #define MAX_LINES 30
  struct Lines {
    short x1[MAX_LINES];
    short y1[MAX_LINES];
    short x2[MAX_LINES];
    short y2[MAX_LINES];
    short color[MAX_LINES];
    short total;
  } lines;
  lines.total = 0;

  srand(0);

  //Enter game loop
  unsigned short frame_counter = 0;
  while(1) {
    short current_line = frame_counter % MAX_LINES;
    VCOUNT_WAIT_FOR_NEXT_FRAME();

    //Add a line to the lines structure
    //If it's full, replace an existing line instead.
    if (lines.total < MAX_LINES) {
      //add line
      lines.x1[lines.total] = rand() % 240;
      lines.y1[lines.total] = rand() % 160;
      lines.x2[lines.total] = rand() % 240;
      lines.y2[lines.total] = rand() % 160;
      lines.color[lines.total] = rand();

      lines.total++;
    } else {
      //replace preexisting line

      //erase it first
      draw_line(lines.x1[current_line], lines.y1[current_line], lines.x2[current_line], lines.y2[current_line], 0, VRAM);

      lines.x1[current_line] = rand() % 240;
      lines.y1[current_line] = rand() % 160;
      lines.x2[current_line] = rand() % 240;
      lines.y2[current_line] = rand() % 160;
      lines.color[current_line] = rand();
    }



    //Draw all lines
    for (short i = 0; i < lines.total; i++)
      draw_line(lines.x1[i], lines.y1[i], lines.x2[i], lines.y2[i], lines.color[i], VRAM);

    frame_counter++;
  }

  return 0;
}
