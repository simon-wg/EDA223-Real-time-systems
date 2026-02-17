#include "App.h"
#include "MusicPlayer.h"
#include "ToneGenerator.h"
#include "canTinyTimber.h"
#include "sciTinyTimber.h"

App app = initApp();
MusicPlayer musicPlayer = initMusicPlayer();
ToneGenerator toneGenerator = initToneGenerator(4);
Can can0 = initCan(CAN_PORT0, &app, receiver);
Serial sci0 = initSerial(SCI_PORT0, &app, reader);
