#ifndef ZEROKEY_MENU_H
#define ZEROKEY_MENU_H

#include "zerokey-globals.h"  // Debe incluir Arduino.h y demás definiciones necesarias.


// Tipo de función para las acciones del menú.
typedef void (*MenuAction)();

// Estructura para cada opción del menú.
struct MenuItem {
  const char* label;      // Texto a mostrar para la opción.
  MenuAction action;      // Función a ejecutar al seleccionar la opción (si no tiene submenú).
  MenuItem* submenu;      // Puntero a un array de opciones para el submenú (NULL si no existe).
  uint8_t submenuCount;   // Número de elementos en el submenú.
};

class ZerokeyMenu {
  public:
    // Constructor: recibe el array inicial y su cantidad de elementos.
    ZerokeyMenu(MenuItem* items, uint8_t count);

    // Métodos para la navegación del menú.
    void displayMenu();
    void navigateUp();
    void navigateDown();
    void selectCurrent();
    void goBack();  // (Para volver al menú principal, por ejemplo.)

  private:
    MenuItem* currentMenu;      // Menú actual.
    uint8_t currentMenuCount;   // Número de opciones en el menú actual.
    int currentMenuIndex;       // Índice de la opción seleccionada.
    //void updateSettingsLanguageMenuItem();
};

// Declaración externa de la instancia global del menú.
extern ZerokeyMenu zerokeyMenu;

#endif // ZEROKEY_MENU_H
