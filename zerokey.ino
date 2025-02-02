#include "zerokey-globals.h" // Include the global header file, which likely contains shared constants, definitions, and includes.

GLOBAL_VARIABLES // Declare global variables using a macro or pre-defined construct from the header.

void setup() {
zerokeySetup.startup();
zerokeySetup.readConfigurationFlag();
}

void loop() {

    zerokeyIo.handleButtonChecker(); // Check the trackball and button for state changes.

}


