#include "zerokey-display.h"

GLOBAL_VARIABLES
uint8_t firstime;
static uint8_t buffer[ 512 ] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x20, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0xE0, 0xF0, 0x90, 0x80, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x10, 0x10, 0xF0, 0x80, 0x80, 0xF0, 0x10, 0x10, 0xF0, 0x80, 0x80, 0xF0, 0x10, 0x10, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x18, 0x38, 0x3C, 0x1C, 0x1E, 0x0E, 0x07, 0x07, 0xC3, 0x3F, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xF8, 0xF8, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x30, 0x0C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x40, 0x80, 0xC0, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xC0, 0x20, 0x10, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x60, 0x60, 0xE0, 0xF0, 0x70, 0x39, 0x3E, 0x1C, 0x18, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x80, 0x00, 0x00, 0x00, 0x10, 0x18, 0x1F, 0x1F, 0x18, 0x10, 0x00, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x30, 0x0C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x03, 0x00, 0x00, 0x03, 0xFC, 0x03, 0x00, 0x00, 0x03, 0xFC, 0x00, 0x00, 0x00, 0xFE, 0x11, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x03, 0x0C, 0x30, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 };
/*
void ZerokeyDisplay::renderMenu() {          //put the PIN Screen in the buffer
  zerokeyDisplay.wipeScreen();
  display.setTextSize(1);
  for (uint8_t i = 0; i < currentMenuCount; i++) {
    if (i == (uint8_t)currentMenuIndex) {
      display.setTextColor(BLACK, WHITE);  // Opción seleccionada (invertida)
    } else {
      display.setTextColor(WHITE, BLACK);
    }
    display.setCursor(0, i * 10);  // Suponiendo 10 píxeles de alto por opción
    display.println(currentMenu[i].label);
  }
  display.display();

}
*/
void ZerokeyDisplay::renderHelloScreen() {
  zerokeyDisplay.wipeScreen();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hola!");
  display.setTextSize(1);
  display.println("");
  display.println("Boton 1: A");
  display.println("Boton 2: B");
  display.println("Boton 3: C");
  display.println("Boton 4: D");
  display.println("Boton 5: E");
  display.display();
  delay(5000); // Espera 5 segundos para que el usuario lea el mensaje
}

void ZerokeyDisplay::renderKeyCreationScreen() {
    zerokeyDisplay.wipeScreen();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Creando clave");
  display.println("de cifrado...");
  display.display();
  // Simula el proceso de creación de clave (puedes poner animación o progreso)
  delay(3000);
}

void ZerokeyDisplay::renderReadyScreen() {
    zerokeyDisplay.wipeScreen();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Listo para usar");
  display.display();
  delay(3000);
}

void ZerokeyDisplay::renderPinScreen() {          //put the PIN Screen in the buffer
  zerokeyDisplay.wipeScreen();
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE); // screen frame
  display.setTextSize( 3 );
  for ( int i = 0; i < pinIndex; i++ ) {
    if ( 82 - ( 17 * i ) > -4 ) { //ugh
      display.setCursor( 82 - ( 17 * i ), 6 );
      display.println( pinArray[ pinIndex - ( i + 1 ) ] );
    }
  }
  display.drawBitmap( 104, 0, pinFrame, 24, 32, WHITE );
  display.setCursor( 109, 6 );
  display.setTextColor( BLACK, WHITE);
  display.println( numpadIndex );
}

void ZerokeyDisplay::renderMainScreen() {  
  if (programPosition == MAIN_INDEX) {
    zerokeyDisplay.wipeScreen();
    display.drawBitmap(0, 0, arrows, 24, 8, WHITE);
    display.setTextColor(WHITE, BLACK);
  } else {
    zerokeyDisplay.wipeScreen();
    display.drawBitmap(0, 0, arrows, 24, 8, BLACK);
    display.setTextColor(WHITE);
  }

  display.setCursor(6, 0);
  display.println(siteIndex + 1);
  display.setTextColor(WHITE);
  display.setCursor(28, 0);

  // SerialUSB: Imprimir los datos en ASCII y HEX
  SerialUSB.println("\n===============================");
  SerialUSB.println("📖 Mostrando datos en pantalla:");
  SerialUSB.print(siteIndex + 1);
  // 🔍 Mostrar Site en pantalla y SerialUSB
  display.setCursor(0, 8);
  display.setTextColor(WHITE);
  if (programPosition == MAIN_SITE) { display.setTextColor(BLACK, WHITE); }
  else { display.setTextColor(WHITE); }
  display.print("Site");
  display.setTextColor(WHITE);
  display.print(":");
  
  SerialUSB.print("✅ Site: ");
  for (int i = 0; i < 16; i++) { 
    display.print(currentSite[i]);
    SerialUSB.print(currentSite[i]);  // ASCII
  }
  SerialUSB.print("   [HEX] ");
  for (int i = 0; i < 16; i++) {
    SerialUSB.print(currentSite[i], HEX); 
    SerialUSB.print(" ");
  }
  SerialUSB.println();

  // 🔍 Mostrar User en pantalla y SerialUSB
  display.setCursor(0, 16);
  if (programPosition == MAIN_USER) { display.setTextColor(BLACK, WHITE); }
  else { display.setTextColor(WHITE); }
  display.print("User");
  display.setTextColor(WHITE);
  display.print(":");
  
  SerialUSB.print("✅ User: ");
  for (int i = 0; i < 16; i++) { 
    display.print(currentUser[i]);
    SerialUSB.print(currentUser[i]);  // ASCII
  }
  SerialUSB.print("   [HEX] ");
  for (int i = 0; i < 16; i++) {
    SerialUSB.print(currentUser[i], HEX); 
    SerialUSB.print(" ");
  }
  SerialUSB.println();

  // 🔍 Mostrar Pass en pantalla y SerialUSB
  display.setCursor(0, 24);
  if (programPosition == MAIN_PASS) { display.setTextColor(BLACK, WHITE); }
  else { display.setTextColor(WHITE); }
  display.print("Pass");
  display.setTextColor(WHITE);
  display.print(":");
  
  SerialUSB.print("✅ Pass: ");
  for (int i = 0; i < 16; i++) { 
    display.print(currentPass[i]);
    SerialUSB.print(currentPass[i]);  // ASCII
  }
  SerialUSB.print("   [HEX] ");
  for (int i = 0; i < 16; i++) {
    SerialUSB.print(currentPass[i], HEX); 
    SerialUSB.print(" ");
  }
  SerialUSB.println();
  SerialUSB.println("===============================\n");
}


void ZerokeyDisplay::renderEditScreen() {         //put the Edit Screen in the buffer
  switch ( typeIndex ) {
    case 0: display.print("Site:"); break;
    case 1: display.print("User:"); break;
    case 2: display.print("Pass:"); break;
  }
  for ( int i = 0; i < 16; i++ ) {
    if ( cursorIndex == i ) display.setTextColor( BLACK, WHITE );
    else display.setTextColor( WHITE );
    switch ( typeIndex ) {
      case 0: display.print( currentSite[ i ]); break;
      case 1: display.print( currentUser[ i ]); break;
      case 2: display.print( currentPass[ i ]); break;
    }
  }
  display.setTextColor( WHITE );
  display.print(" ");
  if ( programPosition == EDIT_LEFT_CURSOR ) display.setTextColor( BLACK, WHITE );
  else display.setTextColor( WHITE );
  display.print("<");
  if ( programPosition == EDIT_RIGHT_CURSOR ) display.setTextColor( BLACK, WHITE );
  else display.setTextColor( WHITE );
  display.print(">");
  display.setTextColor( WHITE );
  display.print(" ");
  display.print(" ");
  for ( int i = 0; i < 16; i++ ) {
    if (( programPosition == EDIT_KB1 ) && ( selectorIndex == i )) display.setTextColor( BLACK, WHITE );
    else display.setTextColor( WHITE );
    display.print( char( pgm_read_byte_near( keyboard1 + i + keyboardIndex )));
  }
  if ( programPosition == EDIT_RAND ) display.setTextColor( BLACK, WHITE );
  else display.setTextColor( WHITE );
 display.print("Rand");
  display.setTextColor( WHITE );
 display.print(" ");
  for ( int i = 0; i < 16; i++ ) {
    if (( programPosition == EDIT_KB2 ) && ( selectorIndex == i )) display.setTextColor( BLACK, WHITE );
    else display.setTextColor( WHITE );
   display.print( char( pgm_read_byte_near( keyboard2 + i + keyboardIndex )));
  }
  if ( programPosition == EDIT_BACK ) display.setTextColor( BLACK, WHITE );
  else display.setTextColor( WHITE );
 display.print("Save");
  display.setTextColor( WHITE );
 display.print(" ");
  for ( int i = 0; i < 16; i++ ) {
    if (( programPosition == EDIT_KB3 ) && ( selectorIndex == i )) display.setTextColor( BLACK, WHITE );
    else display.setTextColor( WHITE );
   display.print( char( pgm_read_byte_near( keyboard3 + i + keyboardIndex )));
  }
}
void ZerokeyDisplay::drawScreen() {               //draw current program state's associated screen
  //zerokeyDisplay.drawScreen(); 
  zerokeyDisplay.wipeScreen();
  switch ( programPosition ) {
    case PIN_SCREEN:
      renderPinScreen();
      break;
    case MAIN_INDEX:
    case MAIN_SITE:
    case MAIN_USER:
    case MAIN_PASS:
      renderMainScreen();
      break;
    case EDIT_LEFT_CURSOR:
    case EDIT_RIGHT_CURSOR:
    case EDIT_RAND:
    case EDIT_BACK:
    case EDIT_KB1:
    case EDIT_KB2:
    case EDIT_KB3:
      renderEditScreen();
      break;
    case MENU:
    zerokeyMenu.displayMenu();
    break;
    default:
      zerokeyUtils.throwErrorScreen();
      break;
  }
  zerokeyDisplay.zerokeydisplay();
}

void ZerokeyDisplay::zerokeydisplay() {
  //display.flip();
  display.display();

}

void ZerokeyDisplay::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
  for (int16_t i = x; i < x + w; i++) {
//    drawFastVLine(i, y, h, color);
  }
}


/*size_t ZerokeyDisplay::write(uint8_t c) {
  if (c == '\n') {
    cursor_y += textsize * 8;
    cursor_x  = 0;
  } else if (c == '\r') {
    // skip em
  } else {
    if (wrap && ((cursor_x + textsize * 6) >= _width)) { // Heading off edge?
      cursor_x  = 0;            // Reset x to zero
      cursor_y += textsize * 8; // Advance y one line
    }
    display.drawChar(cursor_x, cursor_y, c, textcolor, textbgcolor, textsize);
    cursor_x += textsize * 6;
  }
  return 1;
}

void ZerokeyDisplay::drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size) {

  if ((x >= _width)            || // Clip right
      (y >= _height)           || // Clip bottom
      ((x + 6 * size - 1) < 0) || // Clip left
      ((y + 8 * size - 1) < 0))   // Clip top
    return;

  //if(!_cp437 && (c >= 176)) c++; // Handle 'classic' charset behavior
  if (c >= 176) c++; // Handle 'classic' charset behavior

  for (int8_t i = 0; i < 6; i++ ) {
    uint8_t line;
    if (i < 5) line = pgm_read_byte(font + (c * 5) + i);
    else      line = 0x0;
    for (int8_t j = 0; j < 8; j++, line >>= 1) {
      if (line & 0x1) {
        if (size == 1) display.drawPixel(x + i, y + j, color);
        else          fillRect(x + (i * size), y + (j * size), size, size, color);
      } else if (bg != color) {
        if (size == 1) display.drawPixel(x + i, y + j, bg);
        else          fillRect(x + i * size, y + j * size, size, size, bg);
      }
    }
  }
}
*/

void ZerokeyDisplay::wipeScreen() {           //reset the OLED display
 display.clearDisplay();
 display.setCursor(0, 0);
 display.setTextSize(1);
 display.setTextColor(WHITE);
}






//trimmed down adafruit's gfx implementation
