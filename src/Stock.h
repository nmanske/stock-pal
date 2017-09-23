#ifndef STOCK_H
#define STOCK_H

struct Stock_Data {
    String symbol;
    float current, open, close, high, low;
    uint32_t volume;
};

String getStockSymbol(void);
Stock_Data getStockData(String symbol, String response);

#endif
