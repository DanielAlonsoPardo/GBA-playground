#ifndef SINE_COSINE_LOOKUP_HEADER_GUARD
#define SINE_COSINE_LOOKUP_HEADER_GUARD

#define FINE 1
#define MEDIUM 6
#define COARSE 18
#define CARDINAL_DIRECTIONS 90
#define LOOKUP_GRANULARITY FINE

#define LOOKUP_TABLE_SIZE 360/LOOKUP_GRANULARITY

/***
 * turn_amount must be between 0 and LOOKUP_TABLE_SIZE.
 *   Conversion from turn_amount to degrees is simply turn_amount*LOOKUP_GRANULARITY
 */
void init_lookup_tables();
double sin_lt(short turn_amount);
double cos_lt(short turn_amount);

#endif