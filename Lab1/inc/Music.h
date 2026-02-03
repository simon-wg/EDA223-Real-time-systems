#ifndef _MUSIC_H
#define _MUSIC_H

#include "TinyTimber.h"

extern const int MELODY[32];
extern const int PERIOD[];

typedef struct {
  Object super;
  unsigned char volume;
} MusicPlayer;

#define initMusicPlayer(v) {initObject(), v};

int getPeriod(int);
int play(MusicPlayer *, int);

#endif
