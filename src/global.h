#include <Wire.h>
#include <LiquidCrystal_I2C_Menu_Btns.h>
LiquidCrystal_I2C_Menu_Btns lcd(0x27, 16, 2);

uint8_t selectedMenuItem;

// Пины, к которым подключены кнопки
#define pinLeft 2
#define pinRight 3
#define pinEnter 4
#define pinBack 5 // Back - необязательная кнопка

int brightness = 50;
int _delay = 10;