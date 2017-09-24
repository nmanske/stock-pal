#include <Arduino.h>

#include "LED.h"
#include "Stock.h"
#include "WiFi.h"

#define MAX_PRICE_DIGITS 6
#define MAX_VOLUME_DIGITS 10

#define OPEN_PRICE_OFFSET 8
#define CLOSE_PRICE_OFFSET 9
#define HIGH_PRICE_OFFSET 8
#define LOW_PRICE_OFFSET 7
#define VOLUME_OFFSET 10

void Stock::update(void) {
    String r = getResponse(symbol);

    char temp_price[MAX_PRICE_DIGITS];
    char temp_volume[MAX_VOLUME_DIGITS];
    int i, pos_open, pos_close, pos_high, pos_low, pos_volume;
    float last;

    pos_open = r.indexOf("open");
    if (pos_open > 0) {
        for (i = 0; i <= MAX_PRICE_DIGITS; i++) {
            temp_price[i] = r[pos_open+OPEN_PRICE_OFFSET+i];
        }
        last = open;
        open = (float) atof(temp_price);
        if (open == last) {
            trend = NO_CHANGE;
            setLED(0, 0, 255);
        } else if (open > last) {
            trend = INCREASE;
            setLED(0, 255, 0);
        } else if (open < last) {
            trend = DECREASE;
            setLED(255, 0, 0);
        }
    }
    pos_close = r.indexOf("close");
    if (pos_close > 0) {
        for (i = 0; i <= MAX_PRICE_DIGITS; i++) {
            temp_price[i] = r[pos_close+CLOSE_PRICE_OFFSET+i];
        }
        close = (float) atof(temp_price);
    }
    pos_high = r.indexOf("high");
    if (pos_high > 0) {
        for (i = 0; i <= MAX_PRICE_DIGITS; i++) {
            temp_price[i] = r[pos_high+HIGH_PRICE_OFFSET+i];
        }
        high = (float) atof(temp_price);
    }
    pos_low = r.indexOf("low");
    if (pos_low > 0) {
        for (i = 0; i <= MAX_PRICE_DIGITS; i++) {
            temp_price[i] = r[pos_low+LOW_PRICE_OFFSET+i];
        }
        low = (float) atof(temp_price);
    }
    pos_volume = r.indexOf("volume");
    if (pos_volume > 0) {
        i = 0;
        while(r[pos_volume+i+VOLUME_OFFSET] != '"' && i < MAX_VOLUME_DIGITS) {
            temp_volume[i] = r[pos_volume+i+VOLUME_OFFSET];
            i++;
        }
        volume = (uint32_t) atol(temp_volume);
    }

    Serial.print("Symbol: ");
    Serial.println(symbol);
    Serial.print("Open: ");
    Serial.println(open);
    Serial.print("Close: ");
    Serial.println(close);
    Serial.print("High: ");
    Serial.println(high);
    Serial.print("Low: ");
    Serial.println(low);
    Serial.print("Volume: ");
    Serial.println(volume);
    Serial.print("Trend: ");
    Serial.println(trend);
    Serial.println();
}
