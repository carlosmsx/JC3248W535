/*
 * main.cpp - Arduino program for JC3248W535 display demo
 * Author: Carlos Escobar
 * Created: April 16, 2026
 * Description: Initializes and demonstrates the AXS15231B display with colors and graphics
 */


#include <Arduino.h>
#include <Arduino_GFX_Library.h>

// Backlight
#define GFX_BL 1

// Pines típicos JC3248W535 / AXS15231B
#define LCD_CS    45
#define LCD_SCK   47
#define LCD_D0    21
#define LCD_D1    48
#define LCD_D2    40
#define LCD_D3    39
#define LCD_RST   41
#define LCD_DC    42


Arduino_DataBus *bus = new Arduino_ESP32QSPI(
    LCD_CS, LCD_SCK,
    LCD_D0, LCD_D1, LCD_D2, LCD_D3);

// Se puede usar este objeto para dibujar el fondo
Arduino_GFX *panel = new Arduino_AXS15231B(
    bus,
    GFX_NOT_DEFINED,
    0,
    false,
    320,
    480
);

// Sin este canvas, el texto se muestra con error y las funcinoes gráficas no andan bien. No se ve nada en pantalla
Arduino_Canvas *gfx = new Arduino_Canvas(320, 480, panel, 0, 0, 0);

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("Init...");

    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);

    if (!gfx->begin()) {
        Serial.println("gfx->begin() fallo");
        while (true) {
            delay(1000);
        }
    }

    Serial.println("Display OK");

    gfx->fillScreen(BLACK);
    delay(500);
}

void loop()
{
    gfx->fillScreen(RED);
    gfx->setTextSize(4);
    gfx->setTextColor(WHITE);
    gfx->setCursor(120, 140);
    gfx->println("R");
    gfx->flush();
    delay(1000);

    gfx->fillScreen(GREEN);
    gfx->setTextSize(4);
    gfx->setTextColor(WHITE);
    gfx->setCursor(120, 140);
    gfx->println("G");
    gfx->flush();
    delay(1000);

    gfx->fillScreen(BLUE);
    gfx->setTextSize(4);
    gfx->setTextColor(WHITE);
    gfx->setCursor(120, 140);
    gfx->println("B");
    gfx->flush();
    delay(1000);

    gfx->fillScreen(WHITE);
    gfx->setTextColor(BLACK);
    gfx->setTextSize(2);
    gfx->setCursor(20, 20);
    gfx->println("Hello World");

    gfx->setTextSize(2);
    gfx->setCursor(20, 60);
    gfx->println("Ventana: 320x480");

    gfx->flush();
    delay(2000);

    gfx->fillScreen(BLACK);

    gfx->setTextSize(2);
    gfx->setTextColor(WHITE, BLACK);
    gfx->setCursor(20, 20);
    gfx->println("Guition JC3248W535");

    gfx->setTextColor(YELLOW, BLACK);
    gfx->setCursor(20, 60);
    gfx->println("Arduino + PlatformIO");

    gfx->drawRect(10, 10, 300, 100, RED);
    gfx->drawLine(10, 10, 310, 110, GREEN);
    gfx->drawCircle(160, 200, 50, BLUE);
    gfx->fillCircle(160, 320, 40, MAGENTA);
    gfx->flush();
    delay(2000);

}