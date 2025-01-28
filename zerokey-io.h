#ifndef _ZAMEK_IO_H
#define _ZAMEK_IO_H

#include "zerokey-globals.h"

#define NUM_CHANNELS 6  // Número de canales táctiles

class ZerokeyIo {
public:
    void handleButtonChecker();
    uint8_t readRegister(uint8_t registerAddress);
    void handleChannelPress(uint8_t channel);

private:
    void rightButtonPressed();
    void leftButtonPressed();
    void upButtonPressed();
    void downButtonPressed();
    void centerButtonPressed();
    void customButtonPressed();
};

#endif // ZAMEK_IO_H
