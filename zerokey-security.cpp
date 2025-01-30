#include "zerokey-security.h"

GLOBAL_VARIABLES

#include <AESLib.h>
AESLib aesLib;
byte data[ 64 ];
byte key[ 16 ];
byte iv[ 16 ];
uint64_t entropy = 0x123456789ABCDEF0; // Valor fijo (no seguro para producción)
ZerokeySecurity::ZerokeySecurity() {
  // Aquí va el código inicial del objeto, si procede
}

void ZerokeySecurity::lock() {      //encrypt currently selected account and store in EEPROM
 
 for ( int i = 0; i < 16; i++ ) {
    iv[ i ] = entropy >> (( 8 * i ) % 64 ); // increase entropy to 128 bits?
    key[ i ] = pinArray[ i ];
    data[ i ] = currentSite[ i ];
    data[ i + 16 ] = currentUser[ i ];
    data[ i + 32 ] = currentPass[ i ];
  }

aesLib.encrypt(
  (const byte*) data,  // casteamos a const byte*
  48,
  data,                // salida (asegúrate de que también sea byte[] o similar)
  key,
  128,
  iv
);

  for ( int i = 0; i < 16; i++ ) data[ 48 + i ] = iv[ i ];
  zerokeyEeprom.writeEntry( data );

   zerokeyDisplay.wipeScreen();
    display.setTextSize( 3 );
    display.print( "DONE" );
    zerokeyDisplay.zerokeydisplay();
    delay( 2000 );
    programPosition = MAIN_INDEX;
  
}

void ZerokeySecurity::unlock() {
  // Leer la entrada cifrada de EEPROM
  zerokeyEeprom.readEntry(data);

  // Copiar los 16 bytes del IV y 16 bytes de la clave desde pinArray
  for (int i = 0; i < 16; i++) {
    iv[i] = data[i + 48];
    key[i] = pinArray[i];
  }

  // Descifrar (48 bytes) usando la función con la firma correcta
  aesLib.decrypt64(
    (char*)data,
    48,
    data,
    key,
    128,
    iv
  );

  // Almacenar cada parte descifrada
  for (int i = 0; i < 16; i++) {
    currentSite[i] = data[i];
    currentUser[i] = data[i + 16];
    currentPass[i] = data[i + 32];
  }
}
