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
  for (int i = 9; i >= 0; i--) {
    zerokeyDisplay.wipeScreen();
    display.setTextSize(1);
    display.setCursor(0, 0);  
    display.setTextColor(BLACK, WHITE);
    display.println("Critical process");
        display.setTextColor(WHITE);
display.println("All database");
display.println("will be erased.");
  display.setTextColor(BLACK, WHITE);
display.println("Unplug to cancel");
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(110, 0);
    display.print(i);
    display.display();
    delay(1000);
  }
  // Itera sobre el número de entradas disponibles en la zona de datos de usuario
  for (int entryIndex = 0; entryIndex < MAXSITES; entryIndex++) {
    byte eraseBlock[BLOCK_SIZE];
    // Rellena el bloque con 0x20 (espacio)
    memset(eraseBlock, 0xFF, BLOCK_SIZE);
    
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
    // Pequeño retardo entre escrituras (ajustable)
    delay(10);
  }

  delay(2000);
  programPosition = MAIN_INDEX;
}


void ZerokeySecurity::lock() {

for (int i = 15; i >= 0; i--) {
    // Recorrer currentSite[]
    if (currentSite[i] == 0x20) {
      currentSite[i] = 0xFF;  // Reemplazar el espacio por 0xFF
    } else if (currentSite[i] != 0xFF) {
      // Si encontramos un valor distinto a 0x20 y 0xFF, terminamos de modificar
      break;
    }

    // Recorrer currentUser[]
    if (currentUser[i] == 0x20) {
      currentUser[i] = 0xFF;  // Reemplazar el espacio por 0xFF
    } else if (currentUser[i] != 0xFF) {
      // Si encontramos un valor distinto a 0x20 y 0xFF, terminamos de modificar
      break;
    }

    // Recorrer currentPass[]
    if (currentPass[i] == 0x20) {
      currentPass[i] = 0xFF;  // Reemplazar el espacio por 0xFF
    } else if (currentPass[i] != 0xFF) {
      // Si encontramos un valor distinto a 0x20 y 0xFF, terminamos de modificar
      break;
    }
  }

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

void ZerokeySecurity::storeSignature() {

char buffer[17];

    for (int i = 0; i < 16; i++) {
      // Convertimos int8_t a char explícitamente
        buffer[i] = (char)(pinArray[i] + '0');
    }
    // Agregamos el terminador de cadena
    buffer[16] = '\0';



  for (int i = 9; i >= 0; i--) {
    zerokeyDisplay.wipeScreen();
    display.setTextSize(1);
    display.setCursor(0, 0);  
    display.setTextColor(BLACK, WHITE);
    display.println("Critical process");
        display.setTextColor(WHITE);
display.println("New PIN: ");
display.println(buffer);
  display.setTextColor(BLACK, WHITE);
display.println("Unplug to cancel");
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(110, 0);
    display.print(i);
    display.display();
    delay(1000);
  }



  // Copia el bloque predefinido desde PROGMEM a un buffer en RAM.
  uint8_t block[16];
  for (int i = 0; i < 16; i++) {
    block[i] = pgm_read_byte(&constantEncryptedBlock[i]);
  }
  
  // Configura la clave a partir de pinArray.
  for (int i = 0; i < 16; i++) {
    key[i] = pinArray[i];
  }
  
  // Copia el IV genérico al buffer local 'iv'.
  memcpy(iv, genericIV, 16);
  
  // Encripta el bloque de 16 bytes con AES (clave de 128 bits).
  uint8_t encryptedBlock[16];
  int encryptedLength = aesLib.encrypt(block, 16, encryptedBlock, key, 128, iv);
  if (encryptedLength != 16) {
    SerialUSB.println("Error en el cifrado con bloque predefinido");
    return;
  }
  
  // Toma los 8 primeros bytes del bloque cifrado (Verification Signature).
  uint8_t signature[8];
  memcpy(signature, encryptedBlock, 8);
  
  // Escribe esos 8 bytes en la EEPROM (en la región 0x0005 a 0x000C).
  Wire.beginTransmission(eepromAddress);
  Wire.write((uint8_t)0x05);  // Dirección de inicio.
  for (int i = 0; i < 8; i++) {
    Wire.write(signature[i]);
  }
  byte error = Wire.endTransmission();
  if (error == 0) {
zerokeySetup.runConfigurationRoutine();
//zerokeySecurity.eraseAll();
  } else {
    SerialUSB.println("Error al almacenar la Verification Signature.");
  }
}
bool ZerokeySecurity::verifySignature() {
// Copia el bloque predefinido desde PROGMEM a un buffer en RAM.
  uint8_t block[16];
  for (int i = 0; i < 16; i++) {
    block[i] = pgm_read_byte(&constantEncryptedBlock[i]);
  }
  
  // 2. Configura la clave a partir de pinArray.
  for (int i = 0; i < 16; i++) {
    key[i] = pinArray[i];
  }
  
  // 3. Establece el IV utilizando el IV genérico.
  memcpy(iv, genericIV, 16);
  
  // 4. Encripta el bloque de 16 bytes con AES (clave de 128 bits).
  uint8_t encryptedBlock[16];
  int encryptedLength = aesLib.encrypt(block, 16, encryptedBlock, key, 128, iv);
  if (encryptedLength != 16) {
    SerialUSB.println("Error en el cifrado durante la verificación");
    return false;
  }
  
  // 5. Extrae los 8 primeros bytes del bloque encriptado como la firma calculada.
  uint8_t computedSignature[8];
  memcpy(computedSignature, encryptedBlock, 8);
  
  // 6. Lee los 8 bytes almacenados en la EEPROM (dirección 0x0005 - 0x000C).
  uint8_t storedSignature[8];
  Wire.beginTransmission(eepromAddress);
  Wire.write((uint8_t)0x05);      // Dirección de inicio
  Wire.endTransmission(false);    // Repeated start para la lectura.
  
  uint8_t bytesRead = Wire.requestFrom(eepromAddress, (uint8_t)8);
  if (bytesRead != 8) {
    SerialUSB.println("Error al leer la Verification Signature almacenada");
    return false;
  }
  
  for (int i = 0; i < 8; i++) {
    storedSignature[i] = Wire.read();
  }
  
  // 7. Compara las dos firmas.
  for (int i = 0; i < 8; i++) {
    if (computedSignature[i] != storedSignature[i]) {
      incrementFailedAttemptsCounter();
      SerialUSB.println("La Verification Signature no coincide");
      zerokeySecurity.waitFromEeprom();
      return false;
    }
  }
  
  //SerialUSB.println("La Verification Signature coincide");
  writeFailedAttemptsCounter(0);
  return true;
}




// Dirección interna de la EEPROM donde guardamos el contador
// (Si tu EEPROM requiere 2 bytes de dirección, hay que modificar el envío)
static const uint8_t FAILED_ATTEMPTS_ADDR = 0x02;

/**
 * @brief Lee 1 byte de la dirección 0x0002 (Failed Attempts Counter).
 * @return El valor leído [0..255].
 */
uint8_t ZerokeySecurity::readFailedAttemptsCounter()
{
    uint8_t value = 0;
delay(10);
    Wire.beginTransmission(eepromAddress);
    Wire.write((uint8_t)FAILED_ATTEMPTS_ADDR);
    byte error = Wire.endTransmission();
    if (error != 0) {
        SerialUSB.print("I2C Error setting address: ");
        SerialUSB.println(error);
        return 0; // o algún valor por defecto
    }

    // Pedimos 1 byte
    Wire.requestFrom((int)eepromAddress, 1);
    delay(10);
    if (Wire.available()) {
        value = Wire.read();
    } else {
        SerialUSB.println("No data returned from EEPROM!");
    }

    return value;
}

/**
 * @brief Escribe un byte en la dirección 0x0002. 
 * @param value Valor a guardar [0..255].
 */
void ZerokeySecurity::writeFailedAttemptsCounter(uint8_t value)
{
  delay(10);
    Wire.beginTransmission(eepromAddress);
    Wire.write((uint8_t)FAILED_ATTEMPTS_ADDR);
    Wire.write(value);
    byte error = Wire.endTransmission();
delay(10);
    if (error == 0) {
        SerialUSB.print("FailedAttemptsCounter stored: ");
        SerialUSB.println(value);
    } else {
        SerialUSB.print("Error writing to EEPROM! Code: ");
        SerialUSB.println(error);
    }
}

/**
 * @brief Incrementa en 1 el contador de fallos (0..255), lo almacena de nuevo.
 */
void ZerokeySecurity::incrementFailedAttemptsCounter()
{
    uint8_t currentVal = readFailedAttemptsCounter();
    // Evita overflow: si ya está en 255, mantén 255, o haz wrap si prefieres
    if (currentVal < 255) {
        currentVal++;
    } else {
        // currentVal = 0; // wrap-around, o
        currentVal = 255;  // saturado
    }

    writeFailedAttemptsCounter(currentVal);
}

/**
 * @brief Lee el valor guardado en 0x0002 y hace un delay(...) interpretándolo como segundos.
 */
void ZerokeySecurity::waitFromEeprom()
{
    uint8_t waitTime = readFailedAttemptsCounter();
    waitTime = waitTime * 10000;
      for (int i = waitTime; i >= 1; i--) {
    zerokeyDisplay.wipeScreen();
    display.setTextSize(1);
    display.setCursor(0, 0);  
    display.setTextColor(BLACK, WHITE);
    display.println("Wrong PIN");
        display.setTextColor(WHITE);
display.println("Wait time: ");
display.println(waitTime);
  display.setTextColor(BLACK, WHITE);
display.println("16s x Error");
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(90, 0);
    display.print(i);
    display.display();
    delay(1000);
  }
    SerialUSB.print("Waiting ");
    SerialUSB.print(waitTime);
    SerialUSB.println(" second(s)...");

    // Interpreta waitTime como segundos:
    delay((unsigned long)waitTime);

    SerialUSB.println("Done waiting.");
}

void ZerokeySecurity::backupAllCredentials()
{
  // Imprime cuántos registros se van a leer
  SerialUSB.println(MAXSITES);

  // Luego imprime cada registro en formato CSV
  for (int i = 0; i < MAXSITES; i++) {
    siteIndex = i;
    unlock(); // desencripta -> currentSite[], currentUser[], currentPass[]

    String siteStr = bufferToString(currentSite);
    String userStr = bufferToString(currentUser);
    String passStr = bufferToString(currentPass);

    // CSV: "site,user,pass"
    SerialUSB.print(siteStr);  SerialUSB.print(",");
    SerialUSB.print(userStr);  SerialUSB.print(",");
    SerialUSB.println(passStr);
  }
}
void ZerokeySecurity::loadAllbackupCredentials()
{
    zerokeyDisplay.wipeScreen();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.setTextColor(BLACK, WHITE);
    display.println("Import Credentials");
    display.setTextColor(WHITE);
    display.println("Press Save Changes ");
    display.println("at the web manager");
    display.setTextColor(BLACK, WHITE);
    display.println("Unplug to cancel");
    display.display();

    // 1) Esperar a que haya datos en SerialUSB
    while (!SerialUSB.available()) {
      // Espera activa (puedes agregar timeout si lo deseas)
    }

    // Leer la primera línea y descartar líneas inválidas (por ejemplo, "R" o mensajes de debug)
    String firstLine = SerialUSB.readStringUntil('\n');
    firstLine.trim();
    // Mientras la línea recibida no sea un número válido (number > 0), la descartamos
    while (firstLine.equalsIgnoreCase("R") || firstLine.toInt() <= 0) {
      SerialUSB.print("Valor invalido: ");
      SerialUSB.println(firstLine);
      // Espera a que llegue la siguiente línea
      while (!SerialUSB.available()) {
        // Espera activa
      }
      firstLine = SerialUSB.readStringUntil('\n');
      firstLine.trim();
    }

    int numberOfRecords = firstLine.toInt();
    SerialUSB.print(numberOfRecords);

    // 2) Recorrer las 'numberOfRecords' líneas recibidas
    for (int i = 0; i < numberOfRecords; i++) {
      // Espera a que llegue la siguiente línea CSV
      while (!SerialUSB.available()) {
        // Espera activa
      }
      String line = SerialUSB.readStringUntil('\n');
      line.trim();
      if (line.length() == 0) {
        SerialUSB.println("Linea vacia. Saliendo...");
        break;
      }

      // Se espera que la línea tenga el formato: "index,site,user,pass"
      int firstComma = line.indexOf(',');
      if (firstComma < 0) {
        SerialUSB.print("Error: faltan comas en: ");
        SerialUSB.println(line);
        continue;
      }
      String idxStr = line.substring(0, firstComma);
      int index = idxStr.toInt();

      // Toma el resto: "site,user,pass"
      String rest = line.substring(firstComma + 1);
      int secondComma = rest.indexOf(',');
      if (secondComma < 0) {
        SerialUSB.print("Error: faltan comas en: ");
        SerialUSB.println(line);
        continue;
      }
      String siteStr = rest.substring(0, secondComma);

      String rest2 = rest.substring(secondComma + 1);
      int thirdComma = rest2.indexOf(',');
      if (thirdComma < 0) {
        SerialUSB.print("Error: faltan comas en: ");
        SerialUSB.println(line);
        continue;
      }
      String userStr = rest2.substring(0, thirdComma);
      String passStr = rest2.substring(thirdComma + 1);

      // 3) Verificar que el índice es válido
      if (index < 0 || index >= MAXSITES) {
        SerialUSB.print("Index fuera de rango: ");
        SerialUSB.println(index);
        continue;
      }

      // 4) Rellenar currentSite[], currentUser[] y currentPass[] con 0xFF
      for (int k = 0; k < 16; k++) {
        currentSite[k] = 0xFF;
        currentUser[k] = 0xFF;
        currentPass[k] = 0xFF;
      }
      // Copiar los datos recibidos a cada buffer (hasta 16 caracteres)
      for (int k = 0; k < 16 && k < siteStr.length(); k++) {
        currentSite[k] = (uint8_t)siteStr[k];
      }
      for (int k = 0; k < 16 && k < userStr.length(); k++) {
        currentUser[k] = (uint8_t)userStr[k];
      }
      for (int k = 0; k < 16 && k < passStr.length(); k++) {
        currentPass[k] = (uint8_t)passStr[k];
      }

      // 5) Ajustar siteIndex y llamar a lock() para guardar el registro
      siteIndex = index;
      lock();  // lock() cifra data[] (0..47) y escribe en EEPROM

      SerialUSB.print("Registro ");
      SerialUSB.print(index);
      SerialUSB.println(" almacenado correctamente.");
    }
}


String ZerokeySecurity::bufferToString(const char *buf) {
  String s;
  for (int i = 0; i < 16; i++) {
    if (buf[i] == (char)0xFF) {
      // Ignora 0xFF (espacio "vacío")
      continue;
    }
    if (buf[i] == '\0') {
      break;
    }
    s += buf[i];
  }
  return s;
}


