#include "zerokey-menu.h"
GLOBAL_VARIABLES


//--------------------------------------------------
// Funciones dummy para las acciones del menú.
// Asegúrate de que estas funciones queden definidas ANTES de usarlas en los arrays.
void backupImport()      { SerialUSB.println("Backup - Import ejecutado"); }
void backupExport()      { SerialUSB.println("Backup - Export ejecutado"); }
void bitcoinImportPSBT() { SerialUSB.println("Bitcoin - Import PSBT ejecutado"); }
void bitcoinSign()       { SerialUSB.println("Bitcoin - Sign ejecutado"); }
void bitcoinExport()     { SerialUSB.println("Bitcoin - Export ejecutado"); }
void bitcoinAddresses()  { SerialUSB.println("Bitcoin - Addresses ejecutado"); }
void bitcoinNewWallet()  { SerialUSB.println("Bitcoin - New Wallet ejecutado"); }
void settingsRotate()    { 
  zerokeyUtils.toggleScreenOrientation();
  zerokeyUtils.initScreenOrientation();}
void settingsResetPIN()  { programPosition = EDITPIN;  }
void settingsDeleteCred(){  
  zerokeySecurity.eraseAll(); }
void settingsFactoryReset(){ 
  zerokeySecurity.eraseAll();
  zerokeySetup.resetConfigurationFlag();}
//--------------------------------------------------

// Definición de los submenús.
MenuItem backupSubmenu[] = {
  {"Import", backupImport, NULL, 0},
  {"Export", backupExport, NULL, 0}
};

MenuItem bitcoinSubmenu[] = {
  {"Import PSBT", bitcoinImportPSBT, NULL, 0},
  {"Sign", bitcoinSign, NULL, 0},
  {"Export", bitcoinExport, NULL, 0},
  {"Addresses", bitcoinAddresses, NULL, 0},
  {"New Wallet", bitcoinNewWallet, NULL, 0}
};

MenuItem settingsSubmenu[] = {
  {"Rotate Screen", settingsRotate, NULL, 0},
  {"Reset PIN", settingsResetPIN, NULL, 0},
  {"Delete Credentials", settingsDeleteCred, NULL, 0},
  {"Factory Reset", settingsFactoryReset, NULL, 0}
};

// Menú principal.
MenuItem mainMenu[] = {
  {"Backup", NULL, backupSubmenu, sizeof(backupSubmenu)/sizeof(backupSubmenu[0])},
  {"Bitcoin", NULL, bitcoinSubmenu, sizeof(bitcoinSubmenu)/sizeof(bitcoinSubmenu[0])},
  {"Settings", NULL, settingsSubmenu, sizeof(settingsSubmenu)/sizeof(settingsSubmenu[0])}
};

const uint8_t mainMenuCount = sizeof(mainMenu) / sizeof(mainMenu[0]);

//--------------------------------------------------
// Implementación de la clase ZerokeyMenu.

ZerokeyMenu::ZerokeyMenu(MenuItem* items, uint8_t count) {
  currentMenu = items;
  currentMenuCount = count;
  currentMenuIndex = 0;
}

void ZerokeyMenu::displayMenu() {
  zerokeyDisplay.wipeScreen();   // Limpia el buffer del display.
    zerokeyDisplay.renderIndicator("MENU");
  display.setTextSize(1);
  for (uint8_t i = 0; i < currentMenuCount; i++) {
    if (i == (uint8_t)currentMenuIndex)
      display.setTextColor(BLACK, WHITE);
    else
      display.setTextColor(WHITE, BLACK);
    display.setCursor(12, i * 10);  // Asume 10 píxeles por opción.
    display.println(currentMenu[i].label);
  }
  display.display();
}

void ZerokeyMenu::navigateUp() {
  currentMenuIndex--;
  if (currentMenuIndex < 0)
    currentMenuIndex = currentMenuCount - 1;
  displayMenu();
}

void ZerokeyMenu::navigateDown() {
  SerialUSB.print("Antes navigateDown: currentMenuIndex=");
  SerialUSB.print(currentMenuIndex);
  SerialUSB.print(" currentMenuCount=");
  SerialUSB.println(currentMenuCount);
  
  currentMenuIndex++;
  if (currentMenuIndex >= currentMenuCount)
    currentMenuIndex = 0;
  
  SerialUSB.print("Despues navigateDown: currentMenuIndex=");
  SerialUSB.println(currentMenuIndex);
  
  displayMenu();
}



void ZerokeyMenu::selectCurrent() {
  MenuItem selectedItem = currentMenu[currentMenuIndex];
  // Si la opción tiene un submenú, cambiamos al submenú.
  if (selectedItem.submenu != NULL && selectedItem.submenuCount > 0) {
    currentMenu = selectedItem.submenu;
    currentMenuCount = selectedItem.submenuCount;
    currentMenuIndex = 0;
    displayMenu();
  } 
  // Si no tiene submenú y tiene una acción, la ejecutamos.
  else if (selectedItem.action != NULL) {
    selectedItem.action();
    // Luego de ejecutar la acción, se vuelve a mostrar el menú.
    displayMenu();
  }
}

void ZerokeyMenu::goBack() {
  // Por simplicidad, esta función vuelve al menú principal.
  currentMenu = mainMenu;
  currentMenuCount = mainMenuCount;
  currentMenuIndex = 0;
  displayMenu();
}

//--------------------------------------------------
// Definición de la instancia global del menú.
ZerokeyMenu zerokeyMenu(mainMenu, mainMenuCount);
