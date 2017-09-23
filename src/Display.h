#include "Stock.h"

#ifndef DISPLAY_H
#define DISPLAY_H

struct Display_State {
    bool compact;
};

void initDisplay(void);
void setDisplay(Stock_Data data);

#endif
