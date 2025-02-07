  
  #include "zerokey-utils.h"

GLOBAL_VARIABLES







void ZerokeyUtils::typePassword() {  // type password when connected to USB port
  Keyboard.begin();
  delay(10);

  // Escribimos los caracteres de currentUser[]
  for (int i = 0; i < 16; i++) {
    Keyboard.print(currentUser[i]);
    
    // Verificamos si el último carácter tecleado es "@"
    if (currentUser[i] == '@') {
      // Si encontramos "@", escribimos currentSite[] después
      for (int j = 0; j < 16; j++) {  // O el tamaño adecuado para currentSite[]
        Keyboard.print(currentSite[j]);
      }
    }
  }

  // Añadimos el tabulador
  Keyboard.print("\t");  // Tabulador

  // Escribimos los caracteres de currentPass[]
  for (int i = 0; i < 16; i++) {
    Keyboard.print(currentPass[i]);
  }

  delay(10);
  Keyboard.end();
}


void ZerokeyUtils::throwErrorScreen() {   
          SerialUSB.println(programPosition);      //default exception catcher
  display.print("Error: Invalid Program State");
  display.print(programPosition);
  zerokeyDisplay.zerokeydisplay();
  delay( 2000 );
 programPosition = PIN_SCREEN;

}

void ZerokeyUtils::randomEntry() {              //create a random entry
  zerokeyDisplay.wipeScreen();
  display.println("Generating random");
  switch ( typeIndex ) {
    case 0: display.println("site name."); break;
    case 1: display.println("user name."); break;
    case 2: display.println("password."); break;
  }
    display.print("Please wait");
  //TODO implement cancel method: zerokeyDisplay.println("Do something to cancel");
  zerokeyDisplay.zerokeydisplay();
  //TODO evaluate better methods of generating random seeds
  unsigned long entropy = micros();// + batteryLevel;
  //while ( OkButton == 1 );
  //OkButton = 0;
  //while ( !analogRead( BUTTON_CENTER_PIN ));
              delay(3000);
  entropy = entropy - micros();
  randomSeed(entropy);
  switch ( typeIndex ) {
    case 0:
      for ( int i = 0; i < 16; i++ ) {
        int r = random( 94 );
        currentSite[ i ] = pgm_read_byte_near( randomValues + r );
      }
      break;
    case 1:
      for ( int i = 0; i < 16; i++ ) {
        int r = random( 94 );
        currentUser[ i ] = pgm_read_byte_near( randomValues + r );
      }
      break;
    case 2:
      for ( int i = 0; i < 16; i++ ) {
        int r = random( 94 );
        currentPass[ i ] = pgm_read_byte_near( randomValues + r );
      }
      break;
  }
  zerokeySecurity.lock();
}

void ZerokeyUtils::clearAccount() {             //clear the currently selected account

      for ( int i = 0; i < 16; i++ ) {
        currentSite[ i ] = ' ';
        currentUser[ i ] = ' ';
        currentPass[ i ] = ' ';
      }

  zerokeySecurity.lock();
}



void ZerokeyUtils::reciveSerial() {
   SerialUSB.begin(9600);
  //while (!SerialUSB) {
    ; // wait for serial port to connect
 // }

    for ( int n = 0; n < 26; n++ ) {
    for ( int i = 0; i < 16; i++ ) {
    SerialUSB.print("CELL,GET,B");        // send the call to get the data from cell z2
    SerialUSB.print(n+2); 
    SerialUSB.println(","); 
    char value = SerialUSB.read();          // read the serial data into value
    

    int index = (n-1) * 64;
      Wire.beginTransmission( 0x50 );
      Wire.write((( index + i ) >> 8 ) & 0xFF );
      Wire.write(( index + i ) & 0xFF );
      Wire.write( value );
      delay( 5 );
      Wire.endTransmission( true );
           delay( 50 );
    }
          delay( 5 );
  }      
       programPosition = MAIN_INDEX;
       siteIndex = 0;
      zerokeySecurity.unlock();
  
}
  //  SerialUSB.print("DATA,");              // start a data output line
  //  SerialUSB.println(value);              // output vale on that line then end it
   // display.setTextSize( 1 );
   // display.print(value);
   //   display.display();


void ZerokeyUtils::sendSerial() {             //handle Serial commands
byte data[ 64 ];
byte key[ 16 ];
byte iv[ 16 ];
       int index;
       byte entry[64];
   SerialUSB.begin(9600);
  while (!SerialUSB) {
    ; // wait for serial port to connect
  }
  SerialUSB.println("CLEARSHEET");
  SerialUSB.println("LABEL,Index,Site,User,Password");
  SerialUSB.println("RESETTIMER");
  
 for ( int siteIndex = 0; siteIndex < 64; siteIndex++ ) {
  int index = siteIndex * 64;
    Wire.beginTransmission( 0x50 );
    Wire.write(( index >> 8 ) & 0xFF );
    Wire.write( index & 0xFF );
    Wire.endTransmission( true );
    for ( int i = 0; i < 64; i++ ) {
      Wire.requestFrom( 0x50, 1 );
      entry[ i ] = Wire.read();
    }
    Wire.endTransmission( true );

  for ( int i = 0; i < 16; i++ ) {
    iv[ i ] = entry[ i + 48 ];
    key[ i ] = pinArray[ i ];
  }
  //aesLib.decrypt64( key, iv, data, 48 );
  //sanitize( data );
  for ( int i = 0; i < 16; i++ ) {
    currentSite[ i ] = iv[ i + 16 ];
    currentUser[ i ] = iv[ i + 32 ];
    currentPass[ i ] = iv[ i + 48 ];
  }
    SerialUSB.print("DATA,");
    SerialUSB.print(siteIndex);
    SerialUSB.print(",");
        index = 16;
        while ( currentSite[ index - 1 ] == ' ' ) index--;
        for ( int i = 0; i < index; i++ ) SerialUSB.write( currentSite[ i ]);
        SerialUSB.print(",");
        index = 16;
        while ( currentUser[ index - 1 ] == ' ' ) index--;
        for ( int i = 0; i < index; i++ ) SerialUSB.write( currentUser[ i ]);
        SerialUSB.print(",");
        index = 16;
        while ( currentPass[ index - 1 ] == ' ' ) index--;
        for ( int i = 0; i < index; i++ ) SerialUSB.write( currentPass[ i ]);
        SerialUSB.println();
        }
       programPosition = MAIN_INDEX;
       siteIndex = 0;
      zerokeySecurity.unlock();
 }
  /*
  //TODO implement crc-based error handling
  zerokeyDisplay.wipeScreen();
  char firstCheck = Serial.read();
  if (firstCheck == '*') {
    display.print("Serial Request: ");
    //TODO only allow Serial access after physical button press
    char function = Serial.read();
    byte entry[ 64 ];
    char toss;
    int oldIndex = siteIndex;
    int index;
    int j = 0;
    switch (function) {
      case 'v':
        //zerokeyDisplay.print("Connection\r\nVerification");
        Serial.write('@');
        if ( programPosition == PIN_SCREEN ) Serial.write('L');
        else Serial.write('U');
        Serial.flush();
        break;
      case 'r':
        //zerokeyDisplay.print("Read\r\nCredentials ");
        siteIndex = Serial.parseInt() - 1;
        //zerokeyDisplay.print( siteIndex );
        zerokeySecurity.unlock();
        index = 16;
        Serial.write('@');
        Serial.write('r');
        while ( currentSite[ index - 1 ] == ' ' ) index--;
        for ( int i = 0; i < index; i++ ) Serial.write( currentSite[ i ]);
        Serial.println();

        index = 16;
        while ( currentUser[ index - 1 ] == ' ' ) index--;
        for ( int i = 0; i < index; i++ ) Serial.write( currentUser[ i ]);
        Serial.println();

        index = 16;
        while ( currentPass[ index - 1 ] == ' ' ) index--;
        for ( int i = 0; i < index; i++ ) Serial.write( currentPass[ i ]);
        break;
      case 'w':
        //zerokeyDisplay.print("Write\r\nCredentials ");
        siteIndex = Serial.parseInt() - 1;
        //zerokeyDisplay.print( siteIndex );
        toss = Serial.read();
        for ( int i = 0; i < 16; i++ ) currentSite[ i ] = Serial.read();
        for ( int i = 0; i < 16; i++ ) currentUser[ i ] = Serial.read();
        for ( int i = 0; i < 16; i++ ) currentPass[ i ] = Serial.read();
        zerokeySecurity.lock();

        Serial.write('@');
        Serial.write('w');
        index = 16;
        while ( currentSite[ index - 1 ] == ' ' ) index--;
        for ( int i = 0; i < index; i++ ) Serial.write( currentSite[ i ]);
        Serial.println();

        index = 16;
        while ( currentUser[ index - 1 ] == ' ' ) index--;
        for ( int i = 0; i < index; i++ ) Serial.write( currentUser[ i ]);
        Serial.println();

        index = 16;
        while ( currentPass[ index - 1 ] == ' ' ) index--;
        for ( int i = 0; i < index; i++ ) Serial.write( currentPass[ i ]);
        Serial.println();
        break;
      case 'd':
        //zerokeyDisplay.println( "Dumping" );
        //zerokeyzerokeyDisplay.zerokeydisplay();
        Serial.write( '@' );
        Serial.write( 'd' );
        for ( int i = 0; i < MAXSITES; i++ ) {
          zerokeyDisplay.wipeScreen();
          //zerokeyDisplay.println( "Dumping " + String( i ) );
          //zerokeyzerokeyDisplay.zerokeydisplay();
          siteIndex = i;
          zerokeyEeprom.readEntry( entry );
          for ( int j = 0; j < 64; j++ ) Serial.write( entry[ j ] );
        }
        //zerokeyDisplay.print( "Finished Dumping" );
        break;
      case 'u':
        //zerokeyDisplay.println("Restore");
        //zerokeyzerokeyDisplay.zerokeydisplay();
        for ( int i = 0; i < MAXSITES; i++ ) {
          zerokeyDisplay.wipeScreen();
          //zerokeyDisplay.println( "Restoring " + String( i ) );
          //zerokeyzerokeyDisplay.zerokeydisplay();
          siteIndex = i;
          for ( int j = 0; j < 64; j++ ) entry[ j ] = Serial.read();
          zerokeyEeprom.writeEntry( entry );
        }
        break;
      default:
        //TODO throw error on invalid character?
        break;
    }
    Serial.println();
    Serial.flush();
    //zerokeyzerokeyDisplay.zerokeydisplay();
    delay( 1000 );
    siteIndex = oldIndex;
    zerokeySecurity.unlock();
    //zerokeyDisplay.drawScreen();
  }*/


unsigned long ZerokeyUtils::calculateCrc() {  //implementation from https://www.arduino.cc/en/Tutorial/EEPROMCrc
  //TODO validate implementation by recreating it from source
  const unsigned long crc_table[16] = {
    0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
    0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
    0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
  };
  unsigned long crc = ~0L;
//  for (int index = 0 ; index < EEPROM.length()  ; ++index) {
 //   crc = crc_table[(crc ^ EEPROM[index]) & 0x0f] ^ (crc >> 4);
 //   crc = crc_table[(crc ^ (EEPROM[index] >> 4)) & 0x0f] ^ (crc >> 4);
 //   crc = ~crc;
 // }
 return crc;
}


// Función 1: Cambia el valor del indicador de pantalla a lo contrario.
void ZerokeyUtils::toggleScreenOrientation() {
  // Leer el indicador actual
  Wire.beginTransmission(eepromAddress);
  Wire.write((uint8_t)0x01);  // Dirección 0x0001.
  Wire.endTransmission(false);  // Usar repeated start.
  
  uint8_t bytesReceived = Wire.requestFrom(eepromAddress, (uint8_t)1);
  uint8_t currentIndicator = 0;
  if (bytesReceived == 1) {
    currentIndicator = Wire.read();
  } else {
    SerialUSB.println("Error al leer el indicador de pantalla.");
    return;
  }
  
  // Calcula el nuevo indicador (inversa lógica)
  uint8_t newIndicator = (currentIndicator == 0) ? 1 : 0;
  
  // Escribir el nuevo valor en la EEPROM
  Wire.beginTransmission(eepromAddress);
  Wire.write((uint8_t)0x01);  // Dirección 0x0001.
  Wire.write(newIndicator);
  byte error = Wire.endTransmission();
  
  if (error == 0) {
    SerialUSB.print("Indicador de pantalla cambiado de ");
    SerialUSB.print(currentIndicator);
    SerialUSB.print(" a ");
    SerialUSB.println(newIndicator);
  } else {
    SerialUSB.println("Error al cambiar el indicador de pantalla.");
  }
  delay(30);
}


// Función 2: Se ejecuta al inicio del dispositivo para aplicar la orientación de pantalla y controlar la inversión.
// Lee el indicador de pantalla en la dirección 0x0001 y, si es 1, rota la pantalla 180° e invierte los controles.
void ZerokeyUtils::initScreenOrientation() {
    //delay(30);
  uint8_t indicator = 0;
  
  Wire.beginTransmission(eepromAddress);
  Wire.write((uint8_t)0x01);  // Dirección 0x0001.
  Wire.endTransmission(false); // Usar repeated start.
  
  uint8_t bytesReceived = Wire.requestFrom(eepromAddress, (uint8_t)1);
  if (bytesReceived == 1) {
    indicator = Wire.read();
  } else {
    SerialUSB.println("Error al leer el indicador de pantalla durante la inicialización.");
    return;
  }
  
  if (indicator == 1) {
    display.setRotation(2);  // Rota la pantalla 180° (en Adafruit_SSD1306, 2 suele ser 180°).
    invertControls = true;   // Activa la inversión de controles.
    SerialUSB.println("Pantalla invertida y controles invertidos.");
  } else {
    display.setRotation(0);  // Orientación normal.
    invertControls = false;
    SerialUSB.println("Pantalla normal y controles normales.");
  }
  display.display();  // Actualiza la pantalla.
}
