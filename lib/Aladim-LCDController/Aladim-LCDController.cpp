/*
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Aladim-LCDController.h"

// Default Constructor
Aladim_LCDController::Aladim_LCDController(int lcd_adrr)
{

    LCD_Address = lcd_adrr;
    LCD_Cols = lcd_adrr;
    LCD_Rows = lcd_adrr;

    // Create LCD object
    LiquidCrystal_I2C lcdDisplay = LiquidCrystal_I2C(LCD_Address, LCD_Cols, LCD_Rows);

    // Initialize the LC Display
    lcdDisplay.init();

    // Turn on the backlight
    lcdDisplay.backlight();
}

void Aladim_LCDController::print(String param)
{
    Aladim_LCDController::lcdDisplay.setCursor(0, 0);
    lcdDisplay.print(param);
}
*/