#include <stdlib.h>

#include "lib/hardware_consts/gba_memory_map.h"
#include "lib/hardware_consts/gba_io_registers.h"
#include "lib/boids.h"
#include "lib/geometry_MODE3.h"

#define MAX_BOIDS 100

int main(void) {
  const Mem_ptr VRAM = (unsigned short*)VRAM_ADDR;
  //Set video mode
  SET_VIDEO_MODE_3();

  //Init boids
  Boid boids[MAX_BOIDS];
  Boid_flock flock;
  flock.boids = boids;
  flock.n = MAX_BOIDS;
  init_boid_all(&flock);

  //Enter game loop
  while(1) {
    VCOUNT_WAIT_FOR_NEXT_FRAME();
    boids_phys_tick(&flock);
    boids_paint_frame(&flock, VRAM);
  }

  return 0;
}
