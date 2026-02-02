#include "App.h"
#include "sciTinyTimber.h"

App app = initApp();
Serial sci0 = initSerial(SCI_PORT0, &app, reader);
