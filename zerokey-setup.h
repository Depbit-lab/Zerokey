#ifndef ZEROKEY_SETUP_H
#define ZEROKEY_SETUP_H

#include "zerokey-globals.h"

class ZerokeySetup {
  public:
    void startup();
    void runConfigurationRoutine();
    // Modifica la declaración para que devuelva un uint8_t en lugar de void
    uint8_t readConfigurationFlag();
    void resetConfigurationFlag(); // Declaración de la nueva función
};

#endif // ZEROKEY_SETUP_H
