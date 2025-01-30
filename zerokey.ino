#include "zerokey-globals.h" // Include the global header file, which likely contains shared constants, definitions, and includes.

GLOBAL_VARIABLES // Declare global variables using a macro or pre-defined construct from the header.

void setup() {
    // ------------ Start Configuration ------------
    Wire.begin(); // Initialize the I2C communication protocol.
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize the OLED display at I2C address 0x3C.

    // Clear the screen and display the logo
    zerokeyDisplay.wipeScreen(); // Custom function to clear the display buffer.
    display.drawBitmap(0, 0, logo, 128, 32, WHITE); // Draw a logo bitmap (128x32) at the top-left corner.
    zerokeyDisplay.zerokeydisplay(); // Push the display buffer to the screen.
    delay(3000); // Wait for 3 seconds to show the logo.

    // Set the initial program state
    programPosition = PIN_SCREEN; // Set the program's starting state to the "Pin Screen."
    zerokeyDisplay.drawScreen(); // Update the screen to reflect the current state.

    // Configure TS06 touch sensor registers
    uint8_t registers[] = {0x05, 0x06}; // Registers to configure: Ref_Rst and Ch_Hold.

    // Set each register to 0
    for (uint8_t i = 0; i < sizeof(registers); i++) {
        Wire.beginTransmission(TS06_ADDRESS); // Start communication with the TS06 device.
        Wire.write(registers[i]); // Specify the register address.
        Wire.write(0x00); // Write the value 0 to the register.
        Wire.endTransmission(); // End the I2C transmission.
    }


  SerialUSB.begin(9600);        // Inicializa la comunicación USB Serial
  //while (!SerialUSB);           // Espera a que la conexión USB esté lista

  SerialUSB.println("Configuracion realizada");

}

void loop() {

    zerokeyIo.handleButtonChecker(); // Check the trackball and button for state changes.

    zerokeyDisplay.drawScreen(); // Update the screen to show the latest state.
}


