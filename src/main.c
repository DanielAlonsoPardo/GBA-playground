#include <stdlib.h>

#include "lib/hardware_consts/gba_memory_map.h"
#include "lib/hardware_consts/gba_io_registers.h"
#include "lib/boids.h"
#include "lib/geometry.h"

#define MAX_BOIDS 10

int main(void) {
  //Init
  Boid boids[MAX_BOIDS];
  Boid_flock flock;
  flock.boids = boids;
  flock.n = MAX_BOIDS;
  for (int i = 0; i < MAX_BOIDS; i++) {
    init_boid(&flock.boids[i]);
  }

  //Set video mode
  SET_VIDEO_MODE_3();

  const Mem_ptr VRAM = (unsigned short*)VRAM_ADDR;
  srand(0);


  draw_around_pixel(240/2, 180/2, 0xFFFF, VRAM);
  //Enter game loop
  while(1) {


    VCOUNT_WAIT_FOR_NEXT_FRAME();
    boids_phys_tick(&flock, VRAM);
  }

  return 0;
}
