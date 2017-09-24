#ifndef STOCK_H
#define STOCK_H

enum Trend { NO_CHANGE, INCREASE, DECREASE };

class Stock {
    String symbol;
    float current, open, close, high, low;
    uint32_t volume;
    Trend trend;
    static uint8_t total;
  public:
    Stock(String s);
    void update(String data);
    String getSymbol(void) { return symbol; }
    float getCurrentPrice(void) { return current; }
    float getOpenPrice(void) { return open; }
    float getClosePrice(void) { return close; }
    float getHighPrice(void) { return high; }
    float getLowPrice(void) { return low; }
    uint32_t getVolume(void) { return volume; }
    Trend getTrend(void) { return trend; }
    uint8_t getTotal(void) { return total; } 
};

#endif
