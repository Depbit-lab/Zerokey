#include "zerokey-eeprom.h"

GLOBAL_VARIABLES

/*
  +----------------+--------------+-----------------------------------------------------+
  | Address Range  | Size (bytes) | Description                                         |
  +----------------+--------------+-----------------------------------------------------+
  | 0x0000         | 1            | Configuration Flag(0: not configured, 1: configured)|
  | 0x0001         | 1            | Screen Indicator (0: normal, 1: inverted)           |
  | 0x0002         | 1            | Failed Attempts Counter                             |
  | 0x0003 - 0x0004| 2            | Reserved                                            |
  | 0x0005 - 0x000C| 8            | Verification Signature                              |
  | 0x000D - 0x001C| 16           | Global IV                                           |
  | 0x001D         | 1            | Free Space                                          |
  | 0x001E - 0x003D| 32           | Bitcoin Private Key                                 |
  | 0x003E         | 1            | Free Space                                          |
  | 0x003F         | 1            | Free Space                                          |
  +----------------+--------------+-----------------------------------------------------+
  | 0x0040 - 0x00FF| 192          | User Data (4 entries x 48 bytes each)               |
  +----------------+--------------+-----------------------------------------------------+
  | Total Memory   | 256 bytes    |                                                     |
  +----------------+--------------+-----------------------------------------------------+
*/

// Configuraciones



uint8_t ZerokeyEeprom::present() {
  Wire.beginTransmission(eepromAddress);
  if (Wire.endTransmission() == 0) return 1;
  return 0;
}

void ZerokeyEeprom::writeEntry(byte *entry) {
  // Calcula la dirección base en la zona de datos de usuario
  int baseAddress = USER_DATA_START + siteIndex * BLOCK_SIZE;  // Ej: 0x0040, 0x0040+48, etc.
  /*SerialUSB.print("Escribiendo en EEPROM. siteIndex: ");
  SerialUSB.print(siteIndex);
  SerialUSB.print(" | Dirección: ");
  SerialUSB.println(baseAddress, HEX);
*/
  if (!present()) {
    SerialUSB.println("Can't connect to memory chip");
    return;
  }
  
  // Escribir el bloque de 48 bytes en páginas de 8 bytes
  for (int offset = 0; offset < BLOCK_SIZE; offset += PAGE_SIZE) {
    Wire.beginTransmission(eepromAddress);
    // Enviar 1 byte de dirección: baseAddress + offset
    Wire.write((uint8_t)(baseAddress + offset));
    
    // Enviar PAGE_SIZE (8) bytes
    for (int i = 0; i < PAGE_SIZE; i++) {
      Wire.write(entry[offset + i]);
    }
    byte error = Wire.endTransmission();
    if (error != 0) {
      SerialUSB.print("Error al escribir en la página en dirección ");
      SerialUSB.println(baseAddress + offset, HEX);
      return;
    }
    // Dar tiempo para que la EEPROM complete su ciclo de escritura (ajusta según la hoja de datos)
    delay(10);
  }
  //SerialUSB.println("Escritura completada.");
}

void ZerokeyEeprom::readEntry(byte *entry) {
  // Calcula la dirección base en la zona de datos de usuario
  int baseAddress = USER_DATA_START + siteIndex * BLOCK_SIZE;
  /*SerialUSB.print("Leyendo desde EEPROM. siteIndex: ");
  SerialUSB.print(siteIndex);
  SerialUSB.print(" | Dirección: ");
  SerialUSB.println(baseAddress, HEX);
  */
  if (!present()) {
    SerialUSB.println("Can't connect to memory chip");
    return;
  }
  
  // (Opcional) Limpiar el buffer para notar cambios
  for (int i = 0; i < BLOCK_SIZE; i++) {
    entry[i] = 0;
  }
  
  // Leer el bloque en páginas de 8 bytes
  for (int offset = 0; offset < BLOCK_SIZE; offset += PAGE_SIZE) {
    Wire.beginTransmission(eepromAddress);
    Wire.write((uint8_t)(baseAddress + offset));
    Wire.endTransmission();
    
    int bytesToRead = PAGE_SIZE;
    int bytesRead = Wire.requestFrom(eepromAddress, bytesToRead);
    /*
    SerialUSB.print("Bytes recibidos en bloque (dir ");
    SerialUSB.print(baseAddress + offset, HEX);
    SerialUSB.print("): ");
    SerialUSB.println(bytesRead);
    */
    if (bytesRead != bytesToRead) {
      SerialUSB.print("Error: bytes recibidos insuficientes en bloque a dirección ");
      SerialUSB.println(baseAddress + offset, HEX);
    }
    for (int i = 0; i < bytesToRead && Wire.available(); i++) {
      entry[offset + i] = Wire.read();
    }
  }
  //SerialUSB.println("Lectura completada.");
}
