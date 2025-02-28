#include <Wire.h>

#define EEPROM_I2C_ADDRESS 0x57  // Ajusta esta dirección según tu EEPROM
#define EEPROM_SIZE 256          // Tamaño total de la EEPROM en bytes
#define PAGE_SIZE 8              // Tamaño de página para la escritura

/**
 * Función que borra (pone a 0) toda la EEPROM.
 */
void clearEEPROM() {
  byte buffer[PAGE_SIZE];
  // Rellenamos el buffer con 0's
  memset(buffer, 0, PAGE_SIZE);

  Serial.println("Borrando EEPROM...");
  // Recorremos la EEPROM en bloques del tamaño de la página
  for (int address = 0; address < EEPROM_SIZE; address += PAGE_SIZE) {
    Wire.beginTransmission(EEPROM_I2C_ADDRESS);
    Wire.write((byte)address); // Escribimos la dirección de inicio de la página
    // Escribimos PAGE_SIZE bytes (todos en 0)
    for (int i = 0; i < PAGE_SIZE; i++) {
      Wire.write(buffer[i]);
    }
    byte error = Wire.endTransmission();
    if (error != 0) {
      Serial.print("Error al escribir en la página en la dirección 0x");
      Serial.println(address, HEX);
    }
    // Espera para que la EEPROM complete el ciclo de escritura
    delay(10);
  }
  Serial.println("EEPROM borrada.");
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);  // Espera a la conexión del puerto serie, si es necesario

  // Llamamos a la función para borrar la EEPROM
  clearEEPROM();
}

void loop() {
  // El loop queda vacío ya que la acción se realiza en setup()
}

