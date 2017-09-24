#include <Arduino.h>

#include "Stock.h"

#define MAX_PRICE_DIGITS 6
#define MAX_VOLUME_DIGITS 10

#define OPEN_PRICE_OFFSET 8
#define CLOSE_PRICE_OFFSET 9
#define HIGH_PRICE_OFFSET 8
#define LOW_PRICE_OFFSET 7
#define VOLUME_OFFSET 10

void Stock::update(String data) {
    char temp_price[MAX_PRICE_DIGITS];
    int pos_open = data.indexOf("open");
    for (int i = 0; i <= MAX_PRICE_DIGITS; i++) {
        temp_price[i] = data[pos_open+OPEN_PRICE_OFFSET+i];
    }
    float last = open;
    open = (float) atof(temp_price);
    
    if (open == last) {
        trend = NO_CHANGE;
    } else if (open > last) {
        trend = INCREASE;
    } else if (open < last) {
        trend = DECREASE;
    }

    int pos_close = data.indexOf("close");
    for (int i = 0; i <= MAX_PRICE_DIGITS; i++) {
        temp_price[i] = data[pos_close+CLOSE_PRICE_OFFSET+i];
    }
    close = (float) atof(temp_price);

    int pos_high = data.indexOf("high");
    for (int i = 0; i <= MAX_PRICE_DIGITS; i++) {
        temp_price[i] = data[pos_high+HIGH_PRICE_OFFSET+i];
    }
    high = (float) atof(temp_price);

    int pos_low = data.indexOf("low");
    for (int i = 0; i <= MAX_PRICE_DIGITS; i++) {
        temp_price[i] = data[pos_low+LOW_PRICE_OFFSET+i];
    }
    low = (float) atof(temp_price);

    char temp_volume[MAX_VOLUME_DIGITS];
    int pos_volume = data.indexOf("volume");
    int i = 0;
    while(data[pos_volume+i+VOLUME_OFFSET] != '"' && i < MAX_VOLUME_DIGITS) {
        temp_volume[i] = data[pos_volume+i+VOLUME_OFFSET];
        i++;
    }
    volume = (uint32_t) atol(temp_volume);

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
