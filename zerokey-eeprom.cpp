#include "zerokey-eeprom.h"

GLOBAL_VARIABLES

uint8_t ZerokeyEeprom::present() {
  Wire.beginTransmission( 0x57 );
  if ( Wire.endTransmission() == 0 ) return 1;
  return 0;
}

void ZerokeyEeprom::writeEntry( byte *entry ) {
  int index = siteIndex * 64;
  if ( present() ) { //so far this has eluded my attempts to change to page write...
    for ( int i = 0; i < 64; i++ ) {
      Wire.beginTransmission( 0x50 );
      Wire.write((( index + i ) >> 8 ) & 0xFF );
      Wire.write(( index + i ) & 0xFF );
      Wire.write( entry[ i ] );
      Wire.endTransmission( true );
      delay( 5 );
    }
  }
  else {
    zerokeyDisplay.wipeScreen();
    display.print( "Can't connect to memory chip" );
    zerokeyDisplay.zerokeydisplay();
    delay( 2000 );
  }
}

void ZerokeyEeprom::readEntry( byte *entry ) {
  int index = siteIndex * 64;
  if ( present() ) {
    Wire.beginTransmission( 0x50 );
    Wire.write(( index >> 8 ) & 0xFF );
    Wire.write( index & 0xFF );
    Wire.endTransmission( true );
    for ( int i = 0; i < 64; i++ ) {
      Wire.requestFrom( 0x50, 1 );
      entry[ i ] = Wire.read();
    }
    Wire.endTransmission( true );
  }
  else {
    zerokeyDisplay.wipeScreen();
    display.print( "Can't connect to memory chip" );
    zerokeyDisplay.zerokeydisplay();
    delay( 2000 );
  }
}
