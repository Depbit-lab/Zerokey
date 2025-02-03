#ifndef _ZAMEK_UTILS_H
#define _ZAMEK_UTILS_H

#include "zerokey-globals.h"

class ZerokeyUtils {
  public:
    void refreshBatteryLevel();
    void sendSerial();
    void reciveSerial();
    void typePassword();
    unsigned long calculateCrc();
    void clearAccount();
    void randomEntry();
    void throwErrorScreen();
    void toggleScreenOrientation();
    void initScreenOrientation();
};

#endif /* _ZAMEK_UTILS_H */
