#ifndef _MUSICPLAYER_H
#define _MUSICPLAYER_H

#include "TinyTimber.h"
#include <stdint.h>

extern const int MELODY[32];
extern const int PERIOD[];

//START MUSIC PLAYER CLASS

typedef struct {
  Object super;
  uint16_t tempo;
  int8_t key;
} MusicPlayer;

#define initMusicPlayer() {initObject(), 120, 0}

int playTone(MusicPlayer *,int);
int setTempo(MusicPlayer *,int);
int setKey(MusicPlayer *, int);

//END MUSIC PLAYER CLASS

int durationToUsec(int, int);
int getPeriod(int);

#endif
