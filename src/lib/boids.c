#include <stdlib.h>
#include <math.h>

#include "boids.h"
#include "geometry_MODE3.h"
#include "sine_cosine_lookup.h"

#define BOID_RNG_SEED 0

void steer_boids(Boid_flock* flock) {
  for (int i = 0; i < flock->n; i++) {

  }
}

void init_boid_all(Boid_flock* flock) {
  //seed the rng
  srand(BOID_RNG_SEED);

  //initialize all boids
  for (int i = 0; i < flock->n; i++) {
    init_boid(&flock->boids[i]);
  }

  init_lookup_tables();
}

void move_boids(Boid_flock* flock) {
  for (int i = 0; i < flock->n; i++) {
    Boid* boid = &flock->boids[i];

    //Remember last position
    boid->last_position.x = boid->position.x;
    boid->last_position.y = boid->position.y;

    //Calc new position
    double x = boid->position.x + boid->speed * cos_lt(boid->direction);
    double y = boid->position.y + boid->speed * sin_lt(boid->direction);
    //Enforce torus rules
    if (x > MODE3_SCREENWIDTH)
      x -= MODE3_SCREENWIDTH;
    else if (x < 0)
      x += MODE3_SCREENWIDTH;

    if (y > MODE3_SCREENHEIGHT)
      y -= MODE3_SCREENHEIGHT;
    else if (y < 0)
      y += MODE3_SCREENHEIGHT;

    //Set new position
    boid->position.x = x;
    boid->position.y = y;
  }
}

void paint_boids(Boid_flock* flock, Mem_ptr screen) {
  for (int i = 0; i < flock->n; i++) {
    Boid* boid = &flock->boids[i];
    draw_pixel((short)boid->position.x, (short)boid->position.y, boid->color, screen);
  }
}

void erase_boids(Boid_flock* flock, Mem_ptr screen) {
  for (int i = 0; i < flock->n; i++) {
    Boid* boid = &flock->boids[i];
    draw_pixel((short)boid->last_position.x, (short)boid->last_position.y, 0, screen);
  }
}

void init_boid(Boid* boid) {
  boid->position.x = boid->last_position.x = (double) (rand()%240);
  boid->position.y = boid->last_position.y = (double) (rand()%160);
  //choose an angle whose sine/cosine has already been precalculated
  //See sine_cosine_lookup.h
  boid->direction = (rand()%LOOKUP_TABLE_SIZE);
  boid->speed = DEFAULT_BOID_SPEED;
  boid->color = 0xFFFF;
}

/*** phys_tick
 * Performs one tick of the "physics" engine
 */
void boids_phys_tick(Boid_flock* flock) {
  steer_boids(flock);
  move_boids(flock);
}

void boids_paint_frame(Boid_flock* flock, Mem_ptr screen) {
  erase_boids(flock, screen); 
  paint_boids(flock, screen);
}