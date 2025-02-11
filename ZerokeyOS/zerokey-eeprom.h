#ifndef _ZAMEK_EEPROM_H
#define _ZAMEK_EEPROM_H

#include "zerokey-globals.h"  // Ahora ya se conoce KeyboardLayoutOption

class ZerokeyEeprom {
  public:
    void readEntry( byte *entry );
    void writeEntry( byte *entry );
    void eraseMemory();
    void writeKeyboardLayout(KeyboardLayoutOption layout);
    KeyboardLayoutOption readKeyboardLayout();

  private:
    uint8_t present();
};

#endif /* _ZAMEK_EEPROM_H */
