#include "zerokey-setup.h"

GLOBAL_VARIABLES

// Función auxiliar que lee y devuelve el flag de configuración almacenado en la EEPROM.
// Se asume que el flag se guarda en la dirección 0x0000 (parte de la zona de configuración).
uint8_t ZerokeySetup::readConfigurationFlag() {
  uint8_t flag = 0;
  
  Wire.beginTransmission(eepromAddress);
  // Enviar la dirección 0x0000
  Wire.write((uint8_t)0x00);
  Wire.endTransmission();
  
  // Solicitar 1 byte
  uint8_t bytesReceived = Wire.requestFrom(eepromAddress, (uint8_t)1);
  if (bytesReceived == 1) {
    flag = Wire.read();
  }
  return flag;
}

void ZerokeySetup::startup() {
  // ------------ Start Configuration ------------
  SerialUSB.begin(9600);        // Inicializa la comunicación USB Serial
  Wire.begin();                 // Inicializa el protocolo I2C
  programPosition = PIN_SCREEN; // Establece el estado inicial del programa a la "Pin Screen"

  // Configura los registros del sensor táctil TS06
  uint8_t registers[] = {0x05, 0x06}; // Registros a configurar: Ref_Rst y Ch_Hold.
  for (uint8_t i = 0; i < sizeof(registers); i++) {
    Wire.beginTransmission(TS06_ADDRESS); // Comienza la comunicación con el dispositivo TS06.
    Wire.write(registers[i]);             // Especifica la dirección del registro.
    Wire.write(0x00);                     // Escribe el valor 0 en el registro.
    Wire.endTransmission();               // Termina la transmisión I2C.
  }

  // Configuración del display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Inicializa la pantalla OLED en la dirección I2C 0x3C.
  
  // Limpia la pantalla y muestra el logo
  zerokeyDisplay.wipeScreen();                     // Función personalizada para limpiar el buffer.
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE); // Dibuja un recuadro en el borde.
  //display.drawBitmap(0, 0, logo, 128, 32, WHITE);  // Dibuja un logo (opcional).
  display.setTextSize(2);
  display.setCursor(4, 8);
  display.println("ZeroKeyUSB");
  zerokeyDisplay.zerokeydisplay();  // Actualiza la pantalla.
  delay(3000);                      // Espera 3 segundos para mostrar el logo.

  SerialUSB.println("Configuracion realizada");

  // Ahora leemos el flag de configuración y actuamos en consecuencia.
  uint8_t flag = readConfigurationFlag();
  SerialUSB.print("Configuration Flag = 0x");
  SerialUSB.println(flag, HEX);

  if (flag == 0x00) {
    // El dispositivo no está configurado; se ejecuta la secuencia de setup.
    zerokeyDisplay.renderHelloScreen();
    zerokeyDisplay.renderPinScreen();
    zerokeyDisplay.renderKeyCreationScreen();
    zerokeyDisplay.renderReadyScreen();
    runConfigurationRoutine();
  }
  else {
    SerialUSB.println("Device already configured.");
  }

}

void ZerokeySetup::runConfigurationRoutine() {
  SerialUSB.println("Running configuration routine...");
  // Aquí se implementa la configuración inicial (mostrar mensajes, configurar parámetros, etc.)
  
  // Una vez completada la configuración, actualizamos el flag en la EEPROM a 0x01.
  Wire.beginTransmission(eepromAddress);
  // Escribimos en la dirección 0x0000 el valor 0x01 para indicar que ya se configuró el dispositivo.
  Wire.write((uint8_t)0x00); // Dirección 0x0000
  Wire.write((uint8_t)0x01); // Nuevo valor del flag: 0x01 (configurado)
  byte error = Wire.endTransmission();
  
  if (error == 0) {
    SerialUSB.println("Configuration flag updated to 0x01.");
  } else {
    SerialUSB.println("Error updating configuration flag!");
  }
}


// Función para restablecer el flag de configuración a 0 (restablecer a fábrica)
void ZerokeySetup::resetConfigurationFlag() {
  Wire.beginTransmission(eepromAddress);
  // Escribe en la dirección 0x0000
  Wire.write((uint8_t)0x00); // Dirección 0x0000
  Wire.write((uint8_t)0x00); // Nuevo valor del flag: 0x00 (no configurado)
  byte error = Wire.endTransmission();
  
  if (error == 0) {
    SerialUSB.println("Configuration flag reset to 0x00.");
  } else {
    SerialUSB.println("Error resetting configuration flag!");
  }
}