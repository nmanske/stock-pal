#include <Arduino.h>

#include "Stock.h"

#define NUM_STOCK_SYMBOLS 4
#define MAX_PRICE_DIGITS 6
#define MAX_VOLUME_DIGITS 10

#define OPEN_PRICE_OFFSET 8
#define CLOSE_PRICE_OFFSET 9
#define HIGH_PRICE_OFFSET 8
#define LOW_PRICE_OFFSET 7
#define VOLUME_OFFSET 10

static const char* symbols[NUM_STOCK_SYMBOLS] = {"AMD", "AMZN", "SNAP", "VTTSX"};

static uint8_t symbol_index = 0;
static float stock_prices[NUM_STOCK_SYMBOLS];

/* Add status enum here (increase, decrease, same) for stock data struct */

String getStockSymbol(void) {
    if (++symbol_index == NUM_STOCK_SYMBOLS) {
        symbol_index = 0;
    }
    return symbols[symbol_index];
}

Stock_Data getStockData(String symbol, String r) {
    Stock_Data data;
    data.symbol = symbol;

    char temp_price[MAX_PRICE_DIGITS];
    char temp_volume[MAX_VOLUME_DIGITS];
    int i, pos_open, pos_close, pos_high, pos_low, pos_volume;

    pos_open = r.indexOf("open");
    if (pos_open > 0) {
        for (i = 0; i <= MAX_PRICE_DIGITS; i++) {
            temp_price[i] = r[pos_open+OPEN_PRICE_OFFSET+i];
        }
        data.open = (float) atof(temp_price);
    }
    pos_close = r.indexOf("close");
    if (pos_close > 0) {
        for (i = 0; i <= MAX_PRICE_DIGITS; i++) {
            temp_price[i] = r[pos_close+CLOSE_PRICE_OFFSET+i];
        }
        data.close = (float) atof(temp_price);
    }
    pos_high = r.indexOf("high");
    if (pos_high > 0) {
        for (i = 0; i <= MAX_PRICE_DIGITS; i++) {
            temp_price[i] = r[pos_high+HIGH_PRICE_OFFSET+i];
        }
        data.high = (float) atof(temp_price);
    }
    pos_low = r.indexOf("low");
    if (pos_low > 0) {
        for (i = 0; i <= MAX_PRICE_DIGITS; i++) {
            temp_price[i] = r[pos_low+LOW_PRICE_OFFSET+i];
        }
        data.low = (float) atof(temp_price);
    }
    pos_volume = r.indexOf("volume");
    if (pos_volume > 0) {
        i = 0;
        while(r[pos_volume+i+VOLUME_OFFSET] != '"' && i < MAX_VOLUME_DIGITS) {
            temp_volume[i] = r[pos_volume+i+VOLUME_OFFSET];
            i++;
        }
        data.volume = (uint32_t) atol(temp_volume);
    }

    Serial.print("Symbol: ");
    Serial.println(data.symbol);
    Serial.print("Open: ");
    Serial.println(data.open);
    Serial.print("Close: ");
    Serial.println(data.close);
    Serial.print("High: ");
    Serial.println(data.high);
    Serial.print("Low: ");
    Serial.println(data.low);
    Serial.print("Volume: ");
    Serial.println(data.volume);
    Serial.println();

    return data;
}
