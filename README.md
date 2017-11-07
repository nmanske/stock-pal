# Stock Pal

A scrolling LED display showing a list of custom stocks and their daily trends. Uses the power of WiFi to update stock information every few minutes. Upward and downward trends visually indicated using a strip of RGB LEDs.

With Stock Pal you can **put a stock in it!**

### Materials

* x1 NodeMCU 1.0 ESP-12E board
* x1 Nokia5110 LCD
* x1 RGB LED
* x3 330 ohm 1% resistors

### Wiring

Because I'm too lazy to draw up the schematic...

* Nokia RST <---> Node D2
* Nokia CE  <---> Node D1
* Nokia DC  <---> Node D6
* Nokia DIN <---> Node D7
* Nokia CLK <---> Node D5

* Node D0   <---> Resistor <---> Red LED Pin
* Node D3   <---> Resistor <---> Green LED Pin
* Node D4   <---> Resistor <---> Blue LED Pin

Then just connect all the power and ground pins and you're good to go!
