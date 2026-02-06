#ifndef _MUSIC_H
#define _MUSIC_H

#include "TinyTimber.h"

#define MAX_VOLUME 8
#define MIN_VOLUME 1

extern const int MELODY[32];
extern const int PERIOD[];

typedef struct {
  Object super;
  unsigned char volume;
  unsigned char muted;
  unsigned char deadlineEnabled;
} Music;

#define initMusic(v) {initObject(), v, 0, 1};

int getPeriod(int);
int toggleMute(Music *, int);
int toggleMusicDeadline(Music *, int);
int increaseVolume(Music *, int);
int decreaseVolume(Music *, int);
int play(Music *, int);

#endif
