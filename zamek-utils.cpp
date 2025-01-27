  
  #include "zamek-utils.h"

GLOBAL_VARIABLES





uint8_t ZamekUtils::waitForPress() {              //freeze program until button is pressed
/*  while ( analogRead( BUTTON_CENTER_PIN ));
  delay( DEBOUNCEDELAY );
  if ( !analogRead( BUTTON_CENTER_PIN )) return 1;
  else return 0;*/
}

void ZamekUtils::typePassword() {             //type password when connected to USB port
  Keyboard.begin();
    delay(1000);
    switch ( programPosition ) {
    case PIN_SCREEN:
         break; 
    case MAIN_INDEX:
        //Keyboard.press(KEY_TAB);
      for ( int i = 0; i < 16; i++ ) {  
        Keyboard.print( currentUser[ i ] );
      }
      delay(1000);
        Keyboard.print( "\t" );
        delay(1000);
      for ( int i = 0; i < 16; i++ ) {
        Keyboard.print( currentPass[ i ] );
      }
       Keyboard.println( "" );
      //Keyboard.press(KEY_INSERT);
      break;
    case MAIN_SITE:
      for ( int i = 0; i < 16; i++ ) {Keyboard.print( currentSite[ i ] );}
      break;
    case MAIN_USER:
      for ( int i = 0; i < 16; i++ ) {Keyboard.print( currentUser[ i ] );}
      break;
    case MAIN_PASS:
      for ( int i = 0; i < 16; i++ ) {Keyboard.print( currentPass[ i ] );}
      break;
    case EDIT_LEFT_CURSOR:
    case EDIT_RIGHT_CURSOR:
    case EDIT_RAND:
    case EDIT_BACK:
    case EDIT_KB1:
    case EDIT_KB2:
    case EDIT_KB3:
      break;
    default:
      break;
  }
    delay(1000);
    Keyboard.end();
/* Keyboard.begin();
  int index = 16;
  while ( currentPass[ index - 1 ] == ' ') index--;
  for ( int i = 0; i < index; i++ ) {
    if ( Keyboard.write( currentPass[ i ] ) == 0 ) {
      zamekDisplay.wipeScreen();
      display.print("USB Not Connected");
      zamekDisplay.zamekdisplay();
      delay(5000);
      break;
    }
  }
  Keyboard.end();
*/
}

void ZamekUtils::throwErrorScreen() {         //default exception catcher
  display.print("Error: Invalid Program State");
  zamekDisplay.zamekdisplay();
  delay( 2000 );
  programPosition = MAIN_INDEX;
}

void ZamekUtils::randomEntry() {              //create a random entry
  zamekDisplay.wipeScreen();
  display.println("Generating random");
  switch ( typeIndex ) {
    case 0: display.println("site name."); break;
    case 1: display.println("user name."); break;
    case 2: display.println("password."); break;
  }
    display.print("Please wait");
  //TODO implement cancel method: zamekDisplay.println("Do something to cancel");
  zamekDisplay.zamekdisplay();
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
  zamekSecurity.lock();
}

void ZamekUtils::clearAccount() {             //clear the currently selected account

      for ( int i = 0; i < 16; i++ ) {
        currentSite[ i ] = ' ';
        currentUser[ i ] = ' ';
        currentPass[ i ] = ' ';
      }

  zamekSecurity.lock();
}



void ZamekUtils::reciveSerial() {
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
      zamekSecurity.unlock();
  
}
  //  SerialUSB.print("DATA,");              // start a data output line
  //  SerialUSB.println(value);              // output vale on that line then end it
   // display.setTextSize( 1 );
   // display.print(value);
   //   display.display();


void ZamekUtils::sendSerial() {             //handle Serial commands
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
      zamekSecurity.unlock();
 }
  /*
  //TODO implement crc-based error handling
  zamekDisplay.wipeScreen();
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
        //zamekDisplay.print("Connection\r\nVerification");
        Serial.write('@');
        if ( programPosition == PIN_SCREEN ) Serial.write('L');
        else Serial.write('U');
        Serial.flush();
        break;
      case 'r':
        //zamekDisplay.print("Read\r\nCredentials ");
        siteIndex = Serial.parseInt() - 1;
        //zamekDisplay.print( siteIndex );
        zamekSecurity.unlock();
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
        //zamekDisplay.print("Write\r\nCredentials ");
        siteIndex = Serial.parseInt() - 1;
        //zamekDisplay.print( siteIndex );
        toss = Serial.read();
        for ( int i = 0; i < 16; i++ ) currentSite[ i ] = Serial.read();
        for ( int i = 0; i < 16; i++ ) currentUser[ i ] = Serial.read();
        for ( int i = 0; i < 16; i++ ) currentPass[ i ] = Serial.read();
        zamekSecurity.lock();

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
        //zamekDisplay.println( "Dumping" );
        //zamekzamekDisplay.zamekdisplay();
        Serial.write( '@' );
        Serial.write( 'd' );
        for ( int i = 0; i < MAXSITES; i++ ) {
          zamekDisplay.wipeScreen();
          //zamekDisplay.println( "Dumping " + String( i ) );
          //zamekzamekDisplay.zamekdisplay();
          siteIndex = i;
          zamekEeprom.readEntry( entry );
          for ( int j = 0; j < 64; j++ ) Serial.write( entry[ j ] );
        }
        //zamekDisplay.print( "Finished Dumping" );
        break;
      case 'u':
        //zamekDisplay.println("Restore");
        //zamekzamekDisplay.zamekdisplay();
        for ( int i = 0; i < MAXSITES; i++ ) {
          zamekDisplay.wipeScreen();
          //zamekDisplay.println( "Restoring " + String( i ) );
          //zamekzamekDisplay.zamekdisplay();
          siteIndex = i;
          for ( int j = 0; j < 64; j++ ) entry[ j ] = Serial.read();
          zamekEeprom.writeEntry( entry );
        }
        break;
      default:
        //TODO throw error on invalid character?
        break;
    }
    Serial.println();
    Serial.flush();
    //zamekzamekDisplay.zamekdisplay();
    delay( 1000 );
    siteIndex = oldIndex;
    zamekSecurity.unlock();
    //zamekDisplay.drawScreen();
  }*/


unsigned long ZamekUtils::calculateCrc() {  //implementation from https://www.arduino.cc/en/Tutorial/EEPROMCrc
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
