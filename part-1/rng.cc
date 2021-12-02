
#include "rng.h"

// See the header file for documentation

// Secret global variable that is used by RandomDouble_01()
static RandomNumberGenerator rng_01{0, 1};

// Secret global variable that is used by RandomDouble_11()
static RandomNumberGenerator rng_11{-1, 1};

double RandomDouble(double min, double max) {
  RandomNumberGenerator rng(min, max);
  return rng.next();
}

double RandomDouble_01() { return rng_01.next(); }

double RandomDouble_11() { return rng_11.next(); }
