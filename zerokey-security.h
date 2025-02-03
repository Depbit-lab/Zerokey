#include "zerokey-globals.h"

#ifndef ZEROKEY_SECURITY_H
#define ZEROKEY_SECURITY_H



class ZerokeySecurity {
  public:
    void lock();
    void unlock();
    void eraseAll();
    void storeSignature();
    bool verifySignature();
    //void sanitize(byte* s);

  
};

#endif
