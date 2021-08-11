#ifndef UTILS_HEADER_GUARD
#define UTILS_HEADER_GUARD

//Enforce torus rules
#define wraparound(x, max) ( \
  ((x) > (max)) ? ((x) - (max)) : (((x) < 0) ? (x) + (max) : (x)) \
)

#endif