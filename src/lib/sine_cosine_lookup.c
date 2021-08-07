#include <math.h>
#include "sine_cosine_lookup.h"

#define RADS_PER_DEGREE 0.0174533

double Sine_lookup_table[LOOKUP_TABLE_SIZE];
double Cosine_lookup_table[LOOKUP_TABLE_SIZE];

void init_lookup_tables() {
  for (int i = 0, angle = 0; i < LOOKUP_TABLE_SIZE; i++, angle += LOOKUP_GRANULARITY) {
    Sine_lookup_table[i] = sin(angle * RADS_PER_DEGREE);
    Cosine_lookup_table[i] = cos(angle * RADS_PER_DEGREE);
  }
}


double sin_lt(short turn_amount) {
  return Sine_lookup_table[turn_amount];
}

double cos_lt(short turn_amount) {
  return Cosine_lookup_table[turn_amount];
}