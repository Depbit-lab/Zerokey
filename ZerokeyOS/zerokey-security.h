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
    // Lee el valor (1 byte) guardado en dirección 0x0002 (Failed Attempts Counter)
    uint8_t readFailedAttemptsCounter();

    // Escribe un valor (0 a 255) en dirección 0x0002
    void writeFailedAttemptsCounter(uint8_t value);

    // Lee el contador de fallos y lo incrementa en 1, con tope en 255
    void incrementFailedAttemptsCounter();

    // Lee el valor guardado y hace un delay(...) interpretándolo como segundos (o ms)
    void waitFromEeprom();
    void backupAllCredentials();
  void loadAllbackupCredentials();
  String bufferToString(const char *buf);


};

#endif
