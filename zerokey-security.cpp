#include "zerokey-security.h"

GLOBAL_VARIABLES

#include <AESLib.h>
AESLib aesLib;
byte data[48];    // Buffer para una entrada (48 bytes)
byte key[16];
byte iv[16];
uint64_t entropy = 0x123856789ABCDEF0; // Valor fijo (no seguro para producción)
byte genericIV[16] = { 0x00, 0x01, 0x02, 0x03,
                       0x04, 0x05, 0x06, 0x07,
                       0x08, 0x09, 0x0A, 0x0B,
                       0x0C, 0x0D, 0x0E, 0x0F };

// Definiciones para la zona de usuario en EEPROM
#define BLOCK_SIZE 48          // Tamaño de cada entrada de usuario (48 bytes)
#define USER_DATA_START 0x0040 // Dirección de inicio de la zona de datos de usuario


void ZerokeySecurity::eraseAll() {
  SerialUSB.println("Borrando todas las entradas de usuario en EEPROM (0x20 en cada bloque)...");

  // Itera sobre el número de entradas disponibles en la zona de datos de usuario
  for (int entryIndex = 0; entryIndex < MAXSITES; entryIndex++) {
    byte eraseBlock[BLOCK_SIZE];
    // Rellena el bloque con 0x20 (espacio)
    memset(eraseBlock, 0x20, BLOCK_SIZE);
    
    // Establece el índice actual para la zona de usuario.
    // La función writeEntry() debe calcular la dirección base como:
    // USER_DATA_START + (siteIndex * BLOCK_SIZE)
    siteIndex = entryIndex;
      // Establece el IV genérico en el buffer local 'iv'
  memcpy(iv, genericIV, 16);

  // Encripta los 48 bytes usando aesLib.encrypt()
  byte temp[48];
  if (aesLib.encrypt(eraseBlock, 48, temp, key, 128, iv) != 48) {
    SerialUSB.println("Error en el cifrado durante lock");
    return;
  }
  memcpy(eraseBlock, temp, 48);
    // Escribe el bloque "borrado" en la EEPROM
    zerokeyEeprom.writeEntry(eraseBlock);
    
    SerialUSB.print("Entrada ");
    SerialUSB.print(entryIndex);
    SerialUSB.println(" borrada.");
    
    // Pequeño retardo entre escrituras (ajustable)
    delay(10);
  }

  SerialUSB.println("Borrado completo de la zona de datos de usuario.");
  delay(2000);
  programPosition = MAIN_INDEX;
}


void ZerokeySecurity::lock() {
  // Prepara el bloque de 48 bytes con los datos a encriptar.
  // Se dividen en 3 partes de 16 bytes: site, user y pass.
  for (int i = 0; i < 16; i++) {
    data[i]       = currentSite[i];    // bytes 0-15: site
    data[i + 16]  = currentUser[i];      // bytes 16-31: user
    data[i + 32]  = currentPass[i];      // bytes 32-47: pass
    key[i]        = pinArray[i];         // Clave derivada del PIN
  }

  // Establece el IV genérico en el buffer local 'iv'
  memcpy(iv, genericIV, 16);

  // Encripta los 48 bytes usando aesLib.encrypt()
  byte temp[48];
  if (aesLib.encrypt(data, 48, temp, key, 128, iv) != 48) {
    SerialUSB.println("Error en el cifrado durante lock");
    return;
  }
  memcpy(data, temp, 48);

  // Opcional: Si deseas almacenar el IV junto con los datos (por ejemplo, en data[48..63])
  // puedes copiar el IV genérico allí. Si no lo necesitas, omite esta parte.
 // memcpy(data + 48, genericIV, 16);

  // Escribe el bloque completo (64 bytes) en la EEPROM.
  zerokeyEeprom.writeEntry(data);
}

void ZerokeySecurity::unlock() {
  // Lee el bloque completo (64 bytes) desde la EEPROM.
  zerokeyEeprom.readEntry(data);

  // Establece el IV genérico para la desencriptación.
  memcpy(iv, genericIV, 16);

  // Configura la clave a partir de pinArray.
  for (int i = 0; i < 16; i++) {
    key[i] = pinArray[i];
  }

  // Desencripta los 48 bytes cifrados.
  byte temp[48];
  if (aesLib.decrypt(data, 48, temp, key, 128, iv) != 48) {
    SerialUSB.println("Error en el descifrado durante unlock");
    return;
  }
  memcpy(data, temp, 48);

  // Separa el bloque descifrado en currentSite, currentUser y currentPass.
  for (int i = 0; i < 16; i++) {
    currentSite[i] = data[i];
    currentUser[i] = data[i + 16];
    currentPass[i] = data[i + 32];
  }
}
