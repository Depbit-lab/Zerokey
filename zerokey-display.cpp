#include "zerokey-display.h"

GLOBAL_VARIABLES
uint8_t firstime;
static uint8_t buffer[ 512 ] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x20, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0xE0, 0xF0, 0x90, 0x80, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x10, 0x10, 0xF0, 0x80, 0x80, 0xF0, 0x10, 0x10, 0xF0, 0x80, 0x80, 0xF0, 0x10, 0x10, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x18, 0x38, 0x3C, 0x1C, 0x1E, 0x0E, 0x07, 0x07, 0xC3, 0x3F, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xF8, 0xF8, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x30, 0x0C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x40, 0x80, 0xC0, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xC0, 0x20, 0x10, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x60, 0x60, 0xE0, 0xF0, 0x70, 0x39, 0x3E, 0x1C, 0x18, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x80, 0x00, 0x00, 0x00, 0x10, 0x18, 0x1F, 0x1F, 0x18, 0x10, 0x00, 0x00, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x30, 0x0C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x03, 0x00, 0x00, 0x03, 0xFC, 0x03, 0x00, 0x00, 0x03, 0xFC, 0x00, 0x00, 0x00, 0xFE, 0x11, 0x10, 0x10, 0x10, 0x10, 0x0F, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x03, 0x0C, 0x30, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x02, 0x07, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 };
// Función para dibujar un bitmap invertido sin alterar el resto del display.
void ZerokeyDisplay::drawInvertedBitmap(int x, int y, const uint8_t *bitmap, int w, int h) {
  // Calcula la cantidad de bytes del bitmap.
  // Para un bitmap monocromo, cada fila ocupa ceil(w/8) bytes.
  int bytesPerRow = (w + 7) / 8;
  int totalBytes = bytesPerRow * h;
  
  // Crea un buffer en RAM para el bitmap invertido.
  uint8_t inverted[totalBytes];
  
  // Lee cada byte del bitmap en PROGMEM, inviértelo y almacénalo en el buffer.
  for (int i = 0; i < totalBytes; i++) {
    inverted[i] = ~pgm_read_byte(&bitmap[i]);
  }
  
  // Dibuja el bitmap invertido.
  display.drawBitmap(x, y, inverted, w, h, WHITE);
  display.display();
}

void ZerokeyDisplay::renderHelloScreen(int page) {
zerokeyDisplay.wipeScreen();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0, 0);
      SerialUSB.println("page:");
      SerialUSB.println(page);
  switch(page) {
    case 0:
display.println("First Startup");
display.println("ZeroKey USB");
display.println("---------->");
display.display();
  programPosition = SETUP;
break;
    case 1:
// Page 3: Additional info and help

display.println("Check 'About'");
display.println("for info and support");
display.println("<------------->");
      SerialUSB.println("segunda pantalla.");
        programPosition = SETUP;
break;       
    case 2:

display.println("Enter Master PIN");
display.println("Up/Down: Change Digit");
display.println("<-------------->");
      SerialUSB.println("tercera pantalla.");
        programPosition = SETUP;
break;   
default: 
  programPosition = EDITPIN;
  zerokeyDisplay.drawScreen(); // Actualiza la pantalla con el estado actual.
break;  
  }
  //display.display();
    //delay( 2000 );
}

void ZerokeyDisplay::renderKeyCreationScreen() {
    zerokeyDisplay.wipeScreen();
  display.setTextSize(1);
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
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Listo para usar");
  display.display();
  delay(3000);
}

void ZerokeyDisplay::renderIndicator(const char* indicator) {
  // Dibuja un rectángulo blanco en el borde izquierdo de la pantalla.
  // Suponemos que la pantalla tiene SCREEN_WIDTH x SCREEN_HEIGHT.
if (programPosition == MAIN_INDEX || programPosition == MENU) {
    // Dibuja un cuadrado vacío de 1 píxel de ancho (solo el borde)
  display.setTextColor(BLACK, WHITE);
    display.fillRect(0, 0, 10, SCREEN_HEIGHT, WHITE);  // Rectángulo relleno
} else {
    // Dibuja el rectángulo relleno cuando programPosition es igual a MAIN_INDEX
      display.setTextColor(WHITE, BLACK);
    display.drawRect(0, 0, 10, SCREEN_HEIGHT, WHITE);  // Cuadrado vacío de 1px de grosor
}


  display.setTextSize(1); // Tamaño 1 (altura aproximada de 8 píxeles por línea)

  // Calcula la longitud del indicador.
  int len = strlen(indicator);
  // Calcula la altura total del bloque de texto.
  int lineHeight = 8; // Aproximadamente 8 píxeles por línea.
  int totalHeight = len * lineHeight;
  // Centra verticalmente el bloque de texto.
  int startY = (SCREEN_HEIGHT - totalHeight) / 2;

  // Imprime cada carácter en una línea separada.
  for (int i = 0; i < len; i++) {
    display.setCursor(3, startY + i * lineHeight);
    display.print(indicator[i]);
  }
  
  display.display();
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

  zerokeyDisplay.renderIndicator(String(siteIndex + 1).c_str());
  display.setTextSize( 2 );
  // SerialUSB: Imprimir los datos en ASCII y HEX
  SerialUSB.println("\n===============================");
  SerialUSB.println("📖 Mostrando datos en pantalla:");
  SerialUSB.print(siteIndex + 1);
  // 🔍 Mostrar Site en pantalla y SerialUSB

  if (programPosition == MAIN_SITE) {   zerokeyDisplay.drawInvertedBitmap(12, 0, globeIcon, 15, 15);}
  else {    display.drawBitmap(12, 0, globeIcon, 15, 15, WHITE);}

 display.setTextColor(WHITE);
    display.setCursor(28, 0);

  for (int i = 0; i < 16; i++) { 
    display.print(currentSite[i]);

  }


  // 🔍 Mostrar User en pantalla y SerialUSB
  
  if (programPosition == MAIN_USER) {   zerokeyDisplay.drawInvertedBitmap(12, 16, userIcon, 15, 15);}
  else {     display.drawBitmap(12, 16, userIcon, 15, 15, WHITE);}
 display.setTextColor(WHITE);
      display.setCursor(28, 16);

  for (int i = 0; i < 16; i++) { 
    display.print(currentUser[i]);

  }
  if (programPosition == MAIN_PASS) {   
      display.fillRect(12, 16, 120, 16, BLACK);
    zerokeyDisplay.drawInvertedBitmap(12, 16, passIcon, 15, 15);
    display.setTextColor(WHITE);
    display.setCursor(28, 16);
      for (int i = 0; i < 16; i++) { 
      display.print(currentPass[i]);

      }
  }
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
    case EDITPIN:
    renderPinScreen();
    break;
    case MENU:
    zerokeyMenu.displayMenu();
    break;
        case SETUP:
        renderHelloScreen(currentsetupPage);
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



void ZerokeyDisplay::wipeScreen() {           //reset the OLED display
 display.clearDisplay();
 display.setCursor(0, 0);
 display.setTextSize(1);
 display.setTextColor(WHITE);
}






//trimmed down adafruit's gfx implementation
