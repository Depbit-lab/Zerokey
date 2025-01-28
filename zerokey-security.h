#include "zerokey-globals.h"

#ifndef ZEROKEY_SECURITY_H
#define ZEROKEY_SECURITY_H



class ZerokeySecurity {
  public:
    ZerokeySecurity();
    void lock();
    void unlock();
    void sanitize(byte* s);

  private:
    byte pinArray[16];
    byte currentSite[16];
    byte currentUser[16];
    byte currentPass[16];
    byte iv[16];
};

#endif
