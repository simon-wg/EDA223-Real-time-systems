#include "Background.h"
#include "print.h"

#define LOAD_INCREMENT 500
#define BACKGROUND_PERIOD USEC(1300)

int loop(Background *self, int unused) {
  if (self->deadlineEnabled) {
    SEND(BACKGROUND_PERIOD, BACKGROUND_PERIOD, self, loop, 0);
  } else {
    AFTER(BACKGROUND_PERIOD, self, loop, 0);
  }
  for (int i = 0; i < self->background_loop_range; i++) {
  };
  return 0;
}

int toggleBackgroundDeadline(Background *self, int unused) {
  self->deadlineEnabled ^= 1;
  print("Toggling background deadline to: %d\n", self->deadlineEnabled);
  return 0;
}

int increaseLoad(Background *self, int unused) {
  self->background_loop_range += LOAD_INCREMENT;
  print("Increasing background load to: %d\n", self->background_loop_range);
  return 0;
}

int decreaseLoad(Background *self, int unused) {
  self->background_loop_range -= LOAD_INCREMENT;
  print("Decreasing background load to: %d\n", self->background_loop_range);
  return 0;
}

// BELOW THIS IS ONLY FOR MEASUREMENT PURPOSES
int backgroundLoop(int range) {
  Time start = CURRENT_OFFSET();
  for (int i = 0; i < range; i++) {
  };
  return CURRENT_OFFSET() - start;
}

int measureBackgroundLoop(Background *self, int unused) {
  Time totalTime = 0;
  Time maxTime = 0;
  for (int i = 0; i < 500; i++) {
    Time time = backgroundLoop(1000);
    totalTime += time;
    if (time > maxTime) {
      maxTime = time;
    }
  };
  print("Background avg measurement: %d us\n", USEC_OF(totalTime) / 500);
  print("Background max measurement: %d us\n", USEC_OF(maxTime));
  return 0;
}
