#include <global.h>
// Обработчики пунктов меню SetBrightness и SetDelay
// Используются для ввода значений brightness и _delay
void SetBrightness()
{
  brightness = lcd.inputVal("Input brightness(%)", 0, 100, brightness, 5);
}

void SetDelay()
{
  _delay = lcd.inputVal("Input delay(ms)", 0, 20, _delay);
}

// Объявим перечисление, используемое в качестве ключа пунктов меню
enum
{
  mkBack,
  mkRoot,
  mkOptions,
  mkInformation,
  mkSetBrightness,
  mkSetDelay,
  mkStart_1,
  mkStart_2
};

// Описание меню
// структура пункта меню: {ParentKey, Key, Caption, [Handler]}
sMenuItem menu[] = {

    {mkRoot, mkInformation, "Information", NULL},
    {mkRoot, mkStart_1, "Start 1", NULL},
    {mkRoot, mkStart_2, "Start 2", NULL},
    {mkRoot, mkOptions, "Options", NULL},
    {mkOptions, mkSetBrightness, "SetBrightness", SetBrightness},
    {mkOptions, mkSetDelay, "SetDelay", SetDelay},
    {mkOptions, mkBack, "Back", NULL},
    {mkRoot, mkBack, "Back", NULL}};

uint8_t menuLen = sizeof(menu) / sizeof(sMenuItem);

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.attachButtons(pinLeft, pinRight, pinEnter, pinBack);
}

void loop()
{
  // selectedMenuItem = lcd.showMenu(menu, menuLen, 0); // Вызываем меню
  /* Реакция на выбор пунктов меню SetBrightness и SetDelay реализована
   * в функциях-обработчиках.
   * При необходимости здесь может располагаться анализ значения selectedMenuItem
   * для пунктов, не имеющих обработчиков:
     if (selectedMenuItem == ...) {...}
  */

  eButtonsState ButtonsState = lcd.getButtonsState();

  if (selectedMenuItem == mkInformation)
  {
    lcd.printAt(0, 0, "INFORMATION " + String(random(0, 1000)));
    delay(100);

    switch (ButtonsState)
    {
    case eLeft: // Нажали влево - уменьшаем значение переменной
      Serial.println("Left");
      break;
    case eRight: // Нажали вправо - увеличиваем значение переменной
      Serial.println("Right");
      break;
    case eButton: // Нажата кнопка Enter
      Serial.println("Enter");
      selectedMenuItem = mkBack;
      break;
    case eNone: // Нет нажатых кнопок, выходим из функции
      return;
    }
  }
  if (selectedMenuItem == mkStart_1)
  {
    lcd.printAt(0, 0, "START 1 " + String(random(0, 1000)));
    delay(100);

    switch (ButtonsState)
    {
    case eLeft: // Нажали влево - уменьшаем значение переменной
      Serial.println("Left");
      break;
    case eRight: // Нажали вправо - увеличиваем значение переменной
      Serial.println("Right");
      break;
    case eButton: // Нажата кнопка Enter
      Serial.println("Enter");
      selectedMenuItem = mkBack;
      break;
    case eNone: // Нет нажатых кнопок, выходим из функции
      return;
    }
  }
  else
  {
    selectedMenuItem = lcd.showMenu(menu, menuLen, 0);
  }
}
