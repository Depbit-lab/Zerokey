#include "zerokey-globals.h"

ZerokeyUtils zerokeyUtils;
ZerokeySecurity zerokeySecurity;
ZerokeyEeprom zerokeyEeprom;
ZerokeyDisplay zerokeyDisplay; 
ZerokeySetup zerokeySetup;
//ZerokeyMenu zerokeyMenu;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ZerokeyIo zerokeyIo;

//static unsigned long sleepTimer = 0;  
char currentSite[ 16 ] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
char currentUser[ 16 ] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
char currentPass[ 16 ] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
int8_t pinArray[ 16 ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int8_t pinIndex = 0;      //set initial PIN index
uint8_t sleepTimer[ 9 ] = { 0, 0, 0, 0, 0, 0 };
int8_t numpadIndex = 0;   //set initial Numpad index
int8_t typeIndex = 0;     //set index tracker for currently editing information to known value
int8_t cursorIndex = 0;   //set index tracker for current screen cursor position to known value
int8_t pinArrayIndex = 0; //set index tracker for currently selected PIN digit to known value
int8_t selectorIndex = 0; //set index tracker for currently editing account information cursor to known value
int8_t keyboardIndex = 0; //set index tracker for currently selected keyboard entry to known value
int16_t siteIndex = 0;     //set index tracker for currently displayed account to known value
uint8_t programPosition;
byte OkButton = 0;
uint64_t estatus = 0;
uint8_t Timer[9];
uint8_t   Data_Buff[44];

bool invertControls = false;

// TS06
uint16_t  ui16SnapStatus[15], ui16PrevSnap[15];
uint8_t prevState = 0x00;           // Estado anterior de los canales táctiles
uint8_t currentState = 0x00;        // Estado actual de los canales táctiles
uint8_t additionalData[DATA_LENGTH] = {0}; // Buffer para datos adicionales

//EEPROM
uint8_t eepromAddress = 0x57;

extern ZerokeyMenu zerokeyMenu;

int numsetupPages = 4;
int currentsetupPage = 0;

KeyboardLayoutOption currentKeyboardLayout = LAYOUT_EN_US;