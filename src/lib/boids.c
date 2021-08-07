#include <stdlib.h>
#include <math.h>

#include "boids.h"
#include "geometry.h"

void steer_boids(Boid_flock* flock) {
  for (int i = 0; i < flock->n; i++) {

  }
}


void move_boids(Boid_flock* flock) {
  for (int i = 0; i < flock->n; i++) {
    Boid* boid = &flock->boids[i];

    //Remember last position
    boid->last_position.x = boid->position.x;
    boid->last_position.y = boid->position.y;

    //Calc new position
    double x = boid->position.x + boid->speed * cos(boid->direction);
    double y = boid->position.y + boid->speed * sin(boid->direction);
    //Enforce torus rules
    if (x > GBA_SCREEN_WIDTH)
      x -= GBA_SCREEN_WIDTH;
    else if (x < 0)
      x += GBA_SCREEN_WIDTH;

    if (y > GBA_SCREEN_HEIGHT)
      y -= GBA_SCREEN_HEIGHT;
    else if (y < 0)
      y += GBA_SCREEN_HEIGHT;

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
  boid->position.y = boid->last_position.y = (double) (rand()%180);

  boid->direction = ((double) (rand()%360)) * RADS_PER_DEGREE;
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