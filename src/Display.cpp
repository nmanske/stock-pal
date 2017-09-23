#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "Stock.h"

#define D1_PIN 5
#define D2_PIN 4
#define D5_PIN 14
#define D6_PIN 12
#define D7_PIN 13

static Adafruit_PCD8544 display = Adafruit_PCD8544(D5_PIN, D7_PIN, D6_PIN, D1_PIN, D2_PIN);

void initDisplay(void) {
    display.begin();
    display.setContrast(50);
}

void setDisplay(Stock_Data data) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.println(data.symbol);
    display.println(data.open);
    display.display();
}
