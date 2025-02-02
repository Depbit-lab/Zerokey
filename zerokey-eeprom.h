#ifndef _ZAMEK_EEPROM_H
#define _ZAMEK_EEPROM_H

#include "zerokey-globals.h"

class ZerokeyEeprom {
  public:
    void readEntry( byte *entry );
    void writeEntry( byte *entry );
    void eraseMemory();
  private:
    uint8_t present();
};

#endif /* _ZAMEK_EEPROM_H */
