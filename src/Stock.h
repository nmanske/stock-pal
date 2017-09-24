#ifndef STOCK_H
#define STOCK_H

enum Slope { SAME, INCREASE, DECREASE };

struct Stock_Data {
    String symbol;
    float current, open, close, high, low;
    uint32_t volume;
    Slope slope;
};

String getStockSymbol(void);
Stock_Data getStockData(String symbol, String response);

#endif
