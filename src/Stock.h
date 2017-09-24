#ifndef STOCK_H
#define STOCK_H

enum Slope { NO_CHANGE, INCREASE, DECREASE };

class Stock {
    String symbol;
    float current, open, close, high, low;
    uint32_t volume;
    Slope slope;
  public:
    Stock(String s) : symbol(s) { update(); }
    void update(void);
    String getSymbol(void) { return symbol; }
    float getCurrentPrice(void) { return current; }
    float getOpenPrice(void) { return open; }
    float getClosePrice(void) { return close; }
    float getHighPrice(void) { return high; }
    float getLowPrice(void) { return low; }
    uint32_t getVolume(void) { return volume; }
    Slope getSlope(void) { return slope; }
};

#endif
