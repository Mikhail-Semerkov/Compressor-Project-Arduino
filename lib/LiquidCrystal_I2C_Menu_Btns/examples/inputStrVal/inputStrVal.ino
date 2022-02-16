/* Пример использования функции inputStrVal для маскированного ввода. Синтаксис:
 * inputStrVal(title, buffer, len, availSymbols), где
 * title - заголовок
 * buffer - указатель на массив char для вводимых символов
 * len - длина вводимого значения
 * availSymbols - массив символов, доступных для ввода и редактирования
 */
 
#include <Wire.h>
#include <LiquidCrystal_I2C_Menu_Btns.h>
LiquidCrystal_I2C_Menu_Btns lcd(0x27, 20, 4);
#define getEncoderState getButtonsState

// Пины, к которым подключены кнопки
#define pinLeft  2
#define pinRight 3
#define pinEnter 4
#define pinBack  5 // Back - необязательная кнопка

char *buffer; // Буфер для ввода

void setup() {
  lcd.begin();
  lcd.attachButtons(pinLeft, pinRight, pinEnter, pinBack);
  buffer = (char*) malloc (16); // Выделим 16 байт (15 символов + конец строки)
  memset(buffer, '\0', 16); // Заполним их все символом конца строки
}

void loop() {
  if (lcd.inputStrVal("Input your name", buffer, 15, "ABCDEFGHIJKLMNOPQRSTUVWXYZ")){
    lcd.print("Hello,");
    lcd.printAt(0, 1, buffer);
  }
  else
    lcd.print("Input canceled");
  while (lcd.getButtonsState() == eNone);
}
