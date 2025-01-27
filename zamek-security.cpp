#include "zamek-security.h"

GLOBAL_VARIABLES

//AESLib aesLib;

byte data[ 64 ];
byte key[ 16 ];
byte iv[ 16 ];

void ZamekSecurity::sanitize( byte *s ) {

  for ( int i = 0; i < 48; i++ ) { //if an entry is decrypted with the wrong pin, it will contain unenderable characters
    //this attempts to pad them with renderable characters
    //TODO evaluate whether this impacts security at all
    if (( s[ i ] < 32 ) || ( s[ i ] > 126 )) {
      int r = random( 94 );
      s[ i ] = pgm_read_byte_near( randomValues + r );
    }
  }
 
}

void ZamekSecurity::lock() {      //encrypt currently selected account and store in EEPROM
 
 /* for ( int i = 0; i < 16; i++ ) {
    iv[ i ] = entropy >> (( 8 * i ) % 64 ); // increase entropy to 128 bits?
    key[ i ] = pinArray[ i ];
    data[ i ] = currentSite[ i ];
    data[ i + 16 ] = currentUser[ i ];
    data[ i + 32 ] = currentPass[ i ];
  }*/
    for ( int i = 0; i < 16; i++ ) {
    iv[ i ] = data[ i + 48 ];
    key[ i ] = pinArray[ i ];
    data[ i ] = currentSite[ i ];
    data[ i + 16 ] = currentUser[ i ];
    data[ i + 32 ] = currentPass[ i ];
  }
  //aesLib.encrypt64( key, iv, data, 48 );
  //for ( int i = 0; i < 16; i++ ) data[ 48 + i ] = iv[ i ];
  zamekEeprom.writeEntry( data );

   zamekDisplay.wipeScreen();
    display.setTextSize( 3 );
    display.print( "DONE" );
    zamekDisplay.zamekdisplay();
    delay( 2000 );
    programPosition = MAIN_INDEX;
  
}

void ZamekSecurity::unlock() {      //decrypt currently selected account and store in SRAM
  
  zamekEeprom.readEntry( data );
  for ( int i = 0; i < 16; i++ ) {
    iv[ i ] = data[ i + 48 ];
    key[ i ] = pinArray[ i ];
  }
  //aesLib.decrypt64( key, iv, data, 48 );
  //sanitize( data );
  for ( int i = 0; i < 16; i++ ) {
    currentSite[ i ] = data[ i ];
    currentUser[ i ] = data[ i + 16 ];
    currentPass[ i ] = data[ i + 32 ];
  }
       
}
