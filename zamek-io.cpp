#include "zamek-io.h"

GLOBAL_VARIABLES

void ZamekIo::leftButtonPressed() {
  char cipherText[ 50 ];
  switch ( programPosition ) {
    case SPLASHSCREEN: break;
    case PIN_SCREEN:
      if ( pinIndex > 0 ) {
        pinArray[ pinIndex ] = 0;
        pinIndex--;
      }
      break;
    case MAIN_INDEX:
    case MAIN_SITE:
    case MAIN_USER:
    case MAIN_PASS:
      siteIndex = siteIndex - 1;
        if ( siteIndex < 0 ) {programPosition = MENU;   
        }
      zamekSecurity.unlock();
      break;
    case EDIT_LEFT_CURSOR: break;
    case EDIT_RIGHT_CURSOR:
      programPosition = EDIT_LEFT_CURSOR;
      break;
    case EDIT_RAND: break;
    case EDIT_BACK: break;
    case EDIT_KB1:
      if (( selectorIndex == 0 ) && ( keyboardIndex == 0 )) programPosition = EDIT_RIGHT_CURSOR;
      else if (( selectorIndex == 0 ) && ( keyboardIndex >= 0 )) keyboardIndex = keyboardIndex - 1;
      else selectorIndex = selectorIndex - 1;
      break;
    case EDIT_KB2:
      if (( selectorIndex == 0 ) && ( keyboardIndex == 0 )) programPosition = EDIT_RAND;
      else if (( selectorIndex == 0 ) && ( keyboardIndex >= 0 )) keyboardIndex = keyboardIndex - 1;
      else selectorIndex = selectorIndex - 1;
      break;
    case EDIT_KB3:
      if (( selectorIndex == 0 ) && ( keyboardIndex == 0 )) programPosition = EDIT_BACK;
      else if (( selectorIndex == 0 ) && ( keyboardIndex >= 0 )) keyboardIndex = keyboardIndex - 1;
      else selectorIndex = selectorIndex - 1;
      break;
    case MENU: break;
     
    default: zamekUtils.throwErrorScreen(); break;
  }
}



void ZamekIo::rightButtonPressed() {
  switch ( programPosition ) {
    case SPLASHSCREEN: break;
    case PIN_SCREEN:

        if (pinIndex < 16) {
          pinArray[ pinIndex ] = numpadIndex;
          pinIndex++;
        }
      //  break;
    
    if ( pinIndex > 0 ) {
    int array1[16] = {1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0};  //Contraseña!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    int error = 0; 
    for (int i = 0; i<16; i++){
         if (array1[i] != pinArray[i]){
             error++;
         }
    }
   if (error == 0){
    
        programPosition = MAIN_INDEX;
        zamekSecurity.unlock();
        zamekDisplay.wipeScreen();
        zamekDisplay.renderMainScreen();
        zamekDisplay.zamekdisplay();
        break; 
    }else {
    //    zamekDisplay.wipeScreen();
    //    display.setTextSize( 3 );
    //    display.print( "ERROR" );
    //    zamekDisplay.zamekdisplay();
    //    delay( 2000 );
    //    programPosition = PIN_SCREEN;
    //    break; 
//        return 0;
    }
      }
      break;  
    case MAIN_INDEX:
    case MAIN_SITE:
    case MAIN_USER:
    case MAIN_PASS:
      siteIndex = siteIndex + 1;
      if ( siteIndex > ( MAXSITES - 1 )) siteIndex = 0;
      zamekSecurity.unlock();
      break;
    case EDIT_LEFT_CURSOR: programPosition = EDIT_RIGHT_CURSOR; break;
    case EDIT_RIGHT_CURSOR: programPosition = EDIT_KB1; break;
    case EDIT_RAND: programPosition = EDIT_KB2; break;
    case EDIT_BACK: programPosition = EDIT_KB3; break;
    case EDIT_KB1:
      if ( selectorIndex < 15 ) selectorIndex = selectorIndex + 1;
      else if ( keyboardIndex < 16 ) keyboardIndex = keyboardIndex + 1;
      break;
    case EDIT_KB2:
      if ( selectorIndex < 15 ) selectorIndex = selectorIndex + 1;
      else if ( keyboardIndex < 16 ) keyboardIndex = keyboardIndex + 1;
      break;
    case EDIT_KB3:
      if ( selectorIndex < 15 ) selectorIndex = selectorIndex + 1;
      else if ( keyboardIndex < 16 ) keyboardIndex = keyboardIndex + 1;
      break;
    case MENU: 
       programPosition = MAIN_INDEX;
       siteIndex = 0;
      zamekSecurity.unlock();
    break;
    default: zamekUtils.throwErrorScreen(); break;
  }
}

void ZamekIo::upButtonPressed() {
  switch ( programPosition ) {
    case SPLASHSCREEN: break;
    case PIN_SCREEN:
      if ( numpadIndex < 9 ) numpadIndex++;
      else numpadIndex = 0;
      break;
    case MAIN_INDEX: break;
    case MAIN_SITE: programPosition = MAIN_INDEX; break;
    case MAIN_USER: programPosition = MAIN_SITE; break;
    case MAIN_PASS: programPosition = MAIN_USER; break;
    case EDIT_LEFT_CURSOR: break;
    case EDIT_RIGHT_CURSOR: break;
    case EDIT_RAND: programPosition = EDIT_LEFT_CURSOR; break;
    case EDIT_BACK: programPosition = EDIT_RAND; break;
    case EDIT_KB1: break;
    case EDIT_KB2: programPosition = EDIT_KB1; break;
    case EDIT_KB3: programPosition = EDIT_KB2; break;
    case MENU: 
        zamekUtils.reciveSerial();
    break; 
    default: zamekUtils.throwErrorScreen(); break;
  }
}
void ZamekIo::customButtonPressed() {
}
void ZamekIo::downButtonPressed() {
  switch ( programPosition ) {
    case SPLASHSCREEN: break;
    case PIN_SCREEN:
      if ( numpadIndex > 0 ) numpadIndex--;
      else numpadIndex = 9;
      break;
    case MAIN_INDEX: programPosition = MAIN_SITE; break;
    case MAIN_SITE: programPosition = MAIN_USER; break;
    case MAIN_USER: programPosition = MAIN_PASS; break;
    case MAIN_PASS: break;
    case EDIT_LEFT_CURSOR: programPosition = EDIT_RAND; break;
    case EDIT_RIGHT_CURSOR: programPosition = EDIT_RAND; break;
    case EDIT_RAND: programPosition = EDIT_BACK; break;
    case EDIT_BACK: break;
    case EDIT_KB1: programPosition = EDIT_KB2; break;
    case EDIT_KB2: programPosition = EDIT_KB3; break;
    case EDIT_KB3: break;
    case MENU: 
    zamekUtils.sendSerial();
    break;   
    default: zamekUtils.throwErrorScreen(); break;
  }
}

void ZamekIo::centerButtonPressed() {
  //OkButton = 1;
  unsigned long lockCheckTimer = millis();
//  entropy += micros();
  byte finish = 1;
  char cipherText[ 50 ];
  //while ( !analogRead( BUTTON_CENTER_PIN )) {
    if ( programPosition == PIN_SCREEN ) {
      zamekDisplay.wipeScreen();
      display.setTextSize( 3 );
      switch ( pinIndex ) {
        case 0: break;
        default:
          for ( int i = 0; i < pinIndex; i++ ) {
            if ( 82 - ( 17 * i ) > -4 ) {
              display.setCursor( 82 - ( 17 * i ), 6 );
              display.print( pinArray[ pinIndex - (i + 1) ] );
            }
          }
          break;
      }
      display.drawBitmap( 104, 0, pinFrame, 24, 32, WHITE );
      zamekDisplay.zamekdisplay();
    }

  if ( finish ) {
    switch ( programPosition ) {
      case SPLASHSCREEN:
        programPosition = PIN_SCREEN;
        break;
      case PIN_SCREEN:      break;
      case MAIN_INDEX:
        zamekUtils.typePassword();
       // zamekUtils.clearAccount();
        break;
      case MAIN_SITE:
        programPosition = EDIT_RIGHT_CURSOR;
        cursorIndex = 0;
        typeIndex = 0;
        break;
      case MAIN_USER:
        programPosition = EDIT_RIGHT_CURSOR;
        cursorIndex = 0;
        typeIndex = 1;
        break;
      case MAIN_PASS:
        programPosition = EDIT_RIGHT_CURSOR;
        cursorIndex = 0;
        typeIndex = 2;
        break;
      case EDIT_LEFT_CURSOR:
        cursorIndex = cursorIndex - 1;
        if ( cursorIndex < 0 ) cursorIndex = 15;
        break;
      case EDIT_RIGHT_CURSOR:
        cursorIndex = cursorIndex + 1;
        if ( cursorIndex > 15 ) cursorIndex = 0;
        break;
      case EDIT_RAND:
        zamekUtils.randomEntry();
        break;
      case EDIT_BACK:
        programPosition = MAIN_SITE;
        zamekSecurity.lock();
        break;
      case EDIT_KB1:
        switch ( typeIndex ) {
          case 0: currentSite[ cursorIndex ] = char( pgm_read_byte_near( keyboard1 + keyboardIndex + selectorIndex )); break;
          case 1: currentUser[ cursorIndex ] = char( pgm_read_byte_near( keyboard1 + keyboardIndex + selectorIndex )); break;
          case 2: currentPass[ cursorIndex ] = char( pgm_read_byte_near( keyboard1 + keyboardIndex + selectorIndex )); break;
          default: break;
        }
        if ( cursorIndex < 15 ) cursorIndex = cursorIndex + 1;
        else cursorIndex = 0;
        break;
      case EDIT_KB2:
        switch (typeIndex) {
          case 0: currentSite[ cursorIndex ] = char( pgm_read_byte_near( keyboard2 + keyboardIndex + selectorIndex )); break;
          case 1: currentUser[ cursorIndex ] = char( pgm_read_byte_near( keyboard2 + keyboardIndex + selectorIndex )); break;
          case 2: currentPass[ cursorIndex ] = char( pgm_read_byte_near( keyboard2 + keyboardIndex + selectorIndex )); break;
          default: break;
        }
        if ( cursorIndex < 15 ) cursorIndex = cursorIndex + 1;
        else cursorIndex = 0;
        break;
      case EDIT_KB3:
        switch ( typeIndex ) {
          case 0: currentSite[ cursorIndex ] = char( pgm_read_byte_near( keyboard3 + keyboardIndex + selectorIndex )); break;
          case 1: currentUser[ cursorIndex ] = char( pgm_read_byte_near( keyboard3 + keyboardIndex + selectorIndex )); break;
          case 2: currentPass[ cursorIndex ] = char( pgm_read_byte_near( keyboard3 + keyboardIndex + selectorIndex )); break;
          default: break;
        }
        if ( cursorIndex < 15 ) cursorIndex = cursorIndex + 1;
        else cursorIndex = 0;
        break;
    case MENU: break;
      default:
        zamekUtils.throwErrorScreen();
        break;
    }
  }
}


void ZamekIo::handleButtonChecker() {
    uint8_t status = readRegister(0x25); // Reemplaza 0x00 con STATUS_REGISTER si está definido

    // Verifica el estado de cada canal táctil
    for (uint8_t channel = 0; channel < NUM_CHANNELS; channel++) {
        if (status & (1 << channel)) { // Si el bit del canal está activo
            handleChannelPress(channel); // Ejecuta la función correspondiente
        }
    }

    delay(200); // Ajusta el tiempo de muestreo según sea necesario
}

uint8_t ZamekIo::readRegister(uint8_t registerAddress) {
    Wire.beginTransmission(TS06_ADDRESS);
    Wire.write(registerAddress);
    if (Wire.endTransmission(false) != 0) {
        SerialUSB.println("Error leyendo el registro.");
        return 0xFF;
    }

    Wire.requestFrom(TS06_ADDRESS, (uint8_t)1);
    if (Wire.available()) {
        return Wire.read();
    } else {
        SerialUSB.println("No se pudo leer el registro.");
        return 0xFF;
    }
}

void ZamekIo::handleChannelPress(uint8_t channel) {
    switch (channel) {
        case 0:
            upButtonPressed();
            SerialUSB.println("Up button pressed.");
            break;
        case 1:
                  customButtonPressed();
            SerialUSB.println("Custom button pressed.");
            break;
        case 2:
            rightButtonPressed();
            SerialUSB.println("Right button pressed.");
            break;
        case 3:
            centerButtonPressed();
            SerialUSB.println("Center button pressed.");
            break;
        case 4:
            downButtonPressed();
            SerialUSB.println("Down button pressed.");
            break;
        case 5:

            leftButtonPressed();
            SerialUSB.println("Left button pressed.");
            break;
        default:
            SerialUSB.println("Unknown channel.");
    }
}
