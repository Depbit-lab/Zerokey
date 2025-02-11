#include "zerokey-menu.h"
GLOBAL_VARIABLES

void updateSettingsLanguageMenuItem();
void settingsLanguaje();
//--------------------------------------------------
// Funciones dummy para las acciones del menú.
// Asegúrate de que estas funciones queden definidas ANTES de usarlas en los arrays.
void backupImport()      { zerokeySecurity.loadAllbackupCredentials(); }
void backupExport()      { zerokeySecurity.backupAllCredentials(); }
void bitcoinImportPSBT() { SerialUSB.println("Bitcoin - Import PSBT ejecutado"); }
void bitcoinSign()       { SerialUSB.println("Bitcoin - Sign ejecutado"); }
void bitcoinExport()     { SerialUSB.println("Bitcoin - Export ejecutado"); }
void bitcoinAddresses()  { SerialUSB.println("Bitcoin - Addresses ejecutado"); }
void bitcoinNewWallet()  { SerialUSB.println("Bitcoin - New Wallet ejecutado"); }
void settingsRotate()    { 
  zerokeyUtils.toggleScreenOrientation();
  zerokeyUtils.initScreenOrientation();}
void settingsLanguajemenu()    { settingsLanguaje();}
  void settingsAbout()    {
// Page 1: Basic info
zerokeyDisplay.wipeScreen();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0, 0);
display.println("ZeroKey v1.0");
display.println("Created by @depbit");
display.println("X and instagram");
display.display();  // Update the display (if required by your library)
//delay(3000);        // Pause for 3 seconds

// Page 2: Repository details
zerokeyDisplay.wipeScreen();
display.setCursor(0, 0);
display.println("Code at:");
display.println("github.com/Depbit-lab");
display.println("Join us on GitHub");
display.display();
//delay(3000);        // Pause for 3 seconds

// Page 3: Thanks and invitation to collaborate
zerokeyDisplay.wipeScreen();
display.setCursor(0, 0);
display.println("Thanks for using");
display.println("ZeroKey USB!");
display.println("www.zerokeyusb.com");
display.display();
//delay(3000);        // Pause for 3 seconds

   }
void settingsResetPIN()  { programPosition = EDITPIN;  }
void settingsDeleteCred(){  
  zerokeySecurity.eraseAll(); }
void settingsFactoryReset(){ 
  zerokeySetup.resetConfigurationFlag();
  zerokeySecurity.eraseAll();
  zerokeyDisplay.wipeScreen();
display.setCursor(0, 0);
display.println("Factory reset done");
display.println("Please disconnect");
display.println("and reconnect device");
display.display();
delay(10000);
  }
//--------------------------------------------------

// Definición de los submenús.
MenuItem backupSubmenu[] = {
  {"Import", backupImport, NULL, 0},
  {"Export", backupExport, NULL, 0}
};
/*
MenuItem bitcoinSubmenu[] = {
  {"Import PSBT", bitcoinImportPSBT, NULL, 0},
  {"Sign", bitcoinSign, NULL, 0},
  {"Export", bitcoinExport, NULL, 0},
  {"Addresses", bitcoinAddresses, NULL, 0},
  {"New Wallet", bitcoinNewWallet, NULL, 0}
};
*/
MenuItem dangerSubmenu[] = {
  {"Reset PIN", settingsResetPIN, NULL, 0},
  {"Delete Credentials", settingsDeleteCred, NULL, 0},
  {"Factory Reset", settingsFactoryReset, NULL, 0}

};
MenuItem settingsSubmenu[] = {
  {"Rotate Screen", settingsRotate, NULL, 0},
  {"Keyboard", settingsLanguajemenu, NULL, 0},
  {"About", settingsAbout, NULL, 0}
};

// Menú principal.
MenuItem mainMenu[] = {
  {"Backup", NULL, backupSubmenu, sizeof(backupSubmenu)/sizeof(backupSubmenu[0])},
  {"Settings", NULL, settingsSubmenu, sizeof(settingsSubmenu)/sizeof(settingsSubmenu[0])},
  {"Danger Zone", NULL, dangerSubmenu, sizeof(dangerSubmenu)/sizeof(dangerSubmenu[0])}
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
    updateSettingsLanguageMenuItem();
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

static const char* getKeyboardLayoutName() {
    switch(currentKeyboardLayout) {
        case LAYOUT_EN_US: return "US";
        case LAYOUT_DA_DK: return "da_DK";
        case LAYOUT_DE_DE: return "de_DE";
        case LAYOUT_ES_ES: return "es_ES";
        case LAYOUT_FR_FR: return "fr_FR";
        case LAYOUT_HU_HU: return "hu_HU";
        case LAYOUT_IT_IT: return "it_IT";
        case LAYOUT_PT_PT: return "pt_PT";
        case LAYOUT_SV_SE: return "sv_SE";
        default: return "Unknown";
    }
}

void updateSettingsLanguageMenuItem() {
  // Usamos un buffer estático para formar la nueva etiqueta.
  static char labelBuffer[40];
  snprintf(labelBuffer, sizeof(labelBuffer), "Keyboard: %s", getKeyboardLayoutName());
  // Asignamos el nuevo label al ítem del menú.
  settingsSubmenu[1].label = labelBuffer;
}

void settingsLanguaje() {
    // código actualizado para cambiar la distribución del teclado
    if (currentKeyboardLayout < LAYOUT_SV_SE) {
        currentKeyboardLayout = (KeyboardLayoutOption)(currentKeyboardLayout + 1);
    } else {
        currentKeyboardLayout = LAYOUT_EN_US;
    }
    zerokeyEeprom.writeKeyboardLayout(currentKeyboardLayout);
    updateSettingsLanguageMenuItem();
}
