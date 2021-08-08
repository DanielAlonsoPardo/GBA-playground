#include <stdlib.h>

#include "lib/hardware_consts/gba_memory_map.h"
#include "lib/hardware_consts/gba_io_registers.h"
#include "lib/boids.h"
#include "lib/geometry_MODE4.h"

#define MAX_BOIDS 100

int main(void) {
  const Mem_ptr PAGE1 = (unsigned short*)VRAM_MODE4_PAGE1;
  const Mem_ptr PAGE2 = (unsigned short*)VRAM_MODE4_PAGE2;
  const Mem_ptr PALETTE = (unsigned short*)OBJ_PALETTE_ADDR;
  //Set video mode
  SET_VIDEO_MODE_4();
  {//Set palette
    short i = 0;
    for (unsigned short b = 0; b < 6; b++)
      for (unsigned short g = 0; g < 6; g++)
        for (unsigned short r = 0; r < 6; r++)
          PALETTE[i++] = ((b*6) << 10) + ((g*6) << 5) + r*6;

    for (; i < 256; i++)
      PALETTE[i] = 0xFFFF;
  }

  //Palette test
  for (unsigned char i = 0; i < 240; i++) {
    draw_line(i, 0, i, 159, i, VRAM);
  }

  //Init boids
  Boid boids[MAX_BOIDS];
  Boid_flock flock;
  flock.boids = boids;
  flock.n = MAX_BOIDS;
  init_boid_all(&flock);

  //Enter game loop
  char page = 0;
  while(1) {
    VCOUNT_WAIT_FOR_NEXT_FRAME();

    boids_phys_tick(&flock);
//    page = !page;
    boids_paint_frame(&flock, page ? PAGE2 : PAGE1);
/*
    short a = (*((Mem_ptr)(IO_REGISTERS_DISPCNT_ADDR)));
    if (page)
      a = a | DISPCNT_DISPLAY_FRAME_SELECT;
    else
      a = a & ~DISPCNT_DISPLAY_FRAME_SELECT;
    (*((Mem_ptr)(IO_REGISTERS_DISPCNT_ADDR))) = a;
*/
  }

  return 0;
}
