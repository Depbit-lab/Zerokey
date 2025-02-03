#include "zerokey-globals.h" // Include the global header file, which likely contains shared constants, definitions, and includes.

GLOBAL_VARIABLES // Declare global variables using a macro or pre-defined construct from the header.

void setup() {
zerokeySetup.startup();
zerokeySetup.readConfigurationFlag();
zerokeyUtils.initScreenOrientation();
  // Limpia la pantalla y muestra el logo
  zerokeyDisplay.wipeScreen();                     // Función personalizada para limpiar el buffer.
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE); // Dibuja un recuadro en el borde.
  //display.drawBitmap(0, 0, logo, 128, 32, WHITE);  // Dibuja un logo (opcional).
  display.setTextSize(2);
  display.setCursor(4, 8);
  display.println("ZeroKeyUSB");
  zerokeyDisplay.zerokeydisplay();  // Actualiza la pantalla.
  delay(3000);                      // Espera 3 segundos para mostrar el logo.

  programPosition = PIN_SCREEN;
  zerokeyDisplay.drawScreen(); // Actualiza la pantalla con el estado actual.
}

void loop() {

    zerokeyIo.handleButtonChecker(); // Check the trackball and button for state changes.
delay(30);
}


