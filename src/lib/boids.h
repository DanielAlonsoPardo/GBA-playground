#ifndef BOIDS_HEADER_GUARD
#define BOIDS_HEADER_GUARD

#include "hardware_consts/gba_memory_map.h"

#define DEFAULT_BOID_SPEED 1.0

typedef struct VECTOR{
  double x;
  double y;
} Vector;

typedef struct BOID{
  Vector position; // Current position of this boid. Should always be within gameboy screen bounds.
  Vector last_position; // Position of the boid during the previous tick. Used for erasing boids.
  short direction; // In "turn amounts". See sine_cosine_lookup.h.
  double speed; // In pixels per tick
  char color;
} Boid;

typedef struct BOID_FLOCK{
  short n;
  Boid* boids; //Array of boids of length n
} Boid_flock;

/***
 * A boid has a cone of sight that is MAX_VIEW_CONE_ANGLE degrees wide at most,
 *   and is essentialy casting rays from the boid out within that angle.
 *   The rays are evenly spread within this cone, and the exact number of them
 *   depends on MAX_VIEW_CONE_ANGLE and the coarseness of view angles like so:
 *   RAYS_IN_VIEW_CONE = (round_down(MAX_VIEW_CONE_ANGLE/2)/LOOKUP_GRANULARITY) * 2 + 1
 */
#define MAX_VIEW_CONE_ANGLE 45
//in pixels
#define MAX_VIEW_DISTANCE 10
#define RAYS_IN_VIEW_CONE (((MAX_VIEW_CONE_ANGLE/2)/LOOKUP_GRANULARITY) * 2 + 1)


/*** init_boid_all
 * Initializes everything used by boid physics
 */
void init_boid_all(Boid_flock* flock);

/** boid_ai
  Takes an array of boids and changes the direction of each,
    according to its environment and ai.
 */
void boid_ai(Boid_flock* flock);

/*** moveBoids
 * Updates position of each boid according to its speed and direction
 */
void move_boids(Boid_flock* flock);

/*** paintBoids
 * Paints every boid onto VRAM
 */
void paint_boids(Boid_flock* flock, Mem_ptr screen);

/*** eraseBoids
 * Paints every boid black. Assumes black background.
 */
void erase_boids(Boid_flock* flock, Mem_ptr screen);

/*** initBoid
 * Initializes a Boid structure with random properties.
 */
void init_boid(Boid* boid);

/*** phys_tick
 * Performs one tick of the "physics" engine
 */
void boids_phys_tick(Boid_flock* flock);

/*** boids_paint_frame
 * Redraws screen
 */
void boids_paint_frame(Boid_flock* flock, Mem_ptr screen);

#endif