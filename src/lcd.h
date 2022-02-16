void SetBrightness()
{
    brightness = lcd.inputVal("Input brightness(%)", 0, 100, brightness, 5);

    Serial.println("Brightness: " + String(brightness));
}

void SetDelay()
{
    _delay = lcd.inputVal("Input delay(ms)", 0, 20, _delay);

    Serial.println("Delay: " + String(_delay));
}

enum
{
    mkBack,
    mkRoot,
    mkOptions,
    mkSetBrightness,
    mkSetDelay,
    mkStart_1,
    mkStart_2,
    mkStop,
    mkExit
};

sMenuItem menu[] = {

    {mkRoot, mkStart_1, "Start 1", NULL},
    {mkRoot, mkStart_2, "Start 2", NULL},
    {mkRoot, mkStop, "Stop All", NULL},
    {mkRoot, mkOptions, "Options", NULL},
    {mkRoot, mkExit, "Exit", NULL},
    {mkOptions, mkSetBrightness, "SetBrightness", SetBrightness},
    {mkOptions, mkSetDelay, "SetDelay", SetDelay},
    {mkOptions, mkBack, "Back", NULL}};

uint8_t menuLen = sizeof(menu) / sizeof(sMenuItem);

void load_lcd()
{
    lcd.begin();
    lcd.attachButtons(pinLeft, pinRight, pinEnter, pinBack);
    lcd.printAt(0, 0, "    Loading     ");
    lcd.printAt(0, 1, "****************");
    delay(500);
    lcd.clear();
}

void setting_page_lcd()
{

    ButtonsState = lcd.getButtonsState(); // Обработчик нажатий кнопок

    if (selectedMenuItem == mkStart_1)
    {
        lcd.printAt(0, 0, "START 1 " + String(random(0, 1000)));
        delay(100);

        switch (ButtonsState)
        {
        case eLeft:
            Serial.println("Left");

            break;
        case eRight:
            Serial.println("Right");

            break;
        case eButton:
            Serial.println("Enter");

            selectedMenuItem = mkBack;
            break;
        case eNone:
            return;
        }
    }
    if (selectedMenuItem == mkExit)
    {
        String Sost;
        switch (sost_compressor)
        {
        case true:
            Sost = "RUN";
            break;
        case false:
            Sost = "STOP";
            break;

        default:
            break;
        }

        lcd.printAt(0, 0, "Sost: " + Sost);
        delay(100);

        switch (ButtonsState)
        {
        case eLeft:
            Serial.println("Left");
            break;
        case eRight:
            Serial.println("Right");
            break;
        case eButton:
            Serial.println("Enter");
            selectedMenuItem = mkBack;
            break;
        case eNone:
            return;
        }
    }
    else
    {
        selectedMenuItem = lcd.showMenu(menu, menuLen, 0);
    }
}

void setup_lcd()
{
    Serial.begin(9600);

    load_lcd();
}

void loop_lcd()
{
    if (millis() - myTimer1 >= 500)
    {
        myTimer1 = millis();
        count_time++;
        Serial.println(count_time);
    }

    setting_page_lcd();
}