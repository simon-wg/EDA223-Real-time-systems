#include "music.h"
#include <stdint.h>

const int MELODY[32] = {
  0,
  2,
  4,
  0,
  0,
  2,
  4,
  0,
  4,
  5,
  7,
  4,
  5,
  7,
  7,
  9,
  7,
  5,
  4,
  0,
  7,
  9,
  7,
  5,
  4,
  0,
  0,
  -5,
  0,
  0 ,
  -5,
  0
};

const int PERIOD[] = {
  2025, // -10
  1911, // -9
  1804, // -8
  1703, // -7
  1607, // -6
  1517, // -5
  1432, // -4
  1351, // -3
  1276, // -2
  1204, // -1
  1136, // 0
  1073, // 1
  1012,
  956,
  902,
  851,
  804,
  758,
  716,
  676,
  638,
  602,
  568,
  536,
  506
};

int getPeriod(int semitone) {
  if (semitone < -10 || semitone > 14) {
    return 0;
  }
  return PERIOD[semitone + 10];
}
