#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

struct Stock_Data {
    String symbol;
    float current, open, close, high, low;
    uint32_t volume;
};

void connect(void);
String getStockSymbol(void);
String getResponse(String symbol);
Stock_Data parseResponse(String symbol, String response);
void setDisplay(String symbol, float price);

#define D1_PIN 5
#define D2_PIN 4
#define D5_PIN 14
#define D6_PIN 12
#define D7_PIN 13
#define RED_PIN 16
#define GREEN_PIN 0
#define BLUE_PIN 2

#define BAUD_RATE 9600
#define HTTPS_PORT 443

#define NUM_STOCK_SYMBOLS 4
#define MAX_PRICE_DIGITS 6

#define OPEN_PRICE_OFFSET 8
#define CLOSE_PRICE_OFFSET 9
#define HIGH_PRICE_OFFSET 8
#define LOW_PRICE_OFFSET 7
#define VOLUME_OFFSET 10

static const char* ssid = "my_ssid";
static const char* password = "my_password";
static const char* host = "www.alphavantage.co";
static const char* fingerprint = "3C B9 DA D3 0E 01 0F 53 EB B0 42 DD 39 73 44 9B 89 BD 1D BE";
static const char* symbols[NUM_STOCK_SYMBOLS] = {"AMD", "AMZN", "SNAP", "VTTSX"};

static Adafruit_PCD8544 display = Adafruit_PCD8544(D5_PIN, D7_PIN, D6_PIN, D1_PIN, D2_PIN);
static uint8_t status = WL_IDLE_STATUS;
static uint8_t symbol_index = 0;
static float stock_prices[NUM_STOCK_SYMBOLS];

void setup(void) {
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    display.begin();
    display.setContrast(50);

    ESP.wdtDisable();
    ESP.wdtEnable(WDTO_500MS);
    
    Serial.begin(BAUD_RATE);
    while (!Serial);

    connect();
}

void loop(void) {
    ESP.wdtFeed();
    String symbol = getStockSymbol();
    String response = getResponse(symbol);
    Stock_Data data = parseResponse(symbol, response);
    //setDisplay(data);
}

void connect(void) {
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        while (true);
    }
  
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid, password);
        delay(10000);
    }
  
    Serial.println("\nWiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal strength: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dbm\n\n");
}

String getStockSymbol(void) {
    if (++symbol_index == NUM_STOCK_SYMBOLS) {
        symbol_index = 0;
    }
    return symbols[symbol_index];
}

String getResponse(String symbol) {
    Serial.print("Connecting to ");
    Serial.println(host);

    WiFiClientSecure client;
    if (!client.connect(host, HTTPS_PORT)) {
        Serial.println("Connection failed");
        return "None";
    }

    if (client.verify(fingerprint, host)) {
        Serial.println("Certificate matches");
    } else {
        Serial.println("Certificate does not match");
    }

    String url = "/query?function=TIME_SERIES_DAILY&symbol=" + symbol + "&apikey=AMM1WB1N7FPD4U8P";
    String request = String("GET ") + url + " HTTP/1.1\r\n" +
                            "Host: " + host + "\r\n" + 
                            "Connection: close\r\n\r\n";

    Serial.print("Requesting URL: ");
    Serial.println(url);
    Serial.println("Request:");
    Serial.println(request);
    Serial.println();
    client.print(request);

    while(!client.available()) {
        delay(1000);
    }

    String line, response;
    while(client.available()) {
        line = client.readStringUntil('}');
        if (line.indexOf("(Daily)") > 1) {
            response = line;
            break;
        }
    }

    Serial.println("Response:\n");
    Serial.println(response);
    Serial.println("\nClosing connection...\n");

    return response;
}

Stock_Data parseResponse(String symbol, String r) {
    int i, j;
    Stock_Data data;
    char temp_price[MAX_PRICE_DIGITS];
    data.symbol = symbol;
    for (i = 0; i < r.length(); i++) {
        if (r[i] == 'o' && r[i+1] == 'p' && r[i+2] == 'e' && r[i+3] == 'n') {
            for (j = 0; j <= MAX_PRICE_DIGITS; j++) {
                temp_price[j] = r[i+j+OPEN_PRICE_OFFSET];
            }
            data.open = (float) atof(temp_price);
        } else if (r[i] == 'c' && r[i+1] == 'l' && r[i+2] == 'o' && r[i+3] == 's' && r[i+4] == 'e') {
            for (j = 0; j <= MAX_PRICE_DIGITS; j++) {
                temp_price[j] = r[i+j+CLOSE_PRICE_OFFSET];
            }
            data.close = (float) atof(temp_price);
        } else if (r[i] == 'h' && r[i+1] == 'i' && r[i+2] == 'g' && r[i+3] == 'h') {
            for (j = 0; j <= MAX_PRICE_DIGITS; j++) {
                temp_price[j] = r[i+j+HIGH_PRICE_OFFSET];
            }
            data.high = (float) atof(temp_price);
        } else if (r[i] == 'l' && r[i+1] == 'o' && r[i+2] == 'w') {
            for (j = 0; j <= MAX_PRICE_DIGITS; j++) {
                temp_price[j] = r[i+j+LOW_PRICE_OFFSET];
            }
            data.low = (float) atof(temp_price);
        } 
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
    Serial.println();

    return data;
}

void setDisplay(String symbol, float price) {
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);
    display.setTextColor(BLACK);
    display.println(symbol);
    display.println(price);
    display.display();
}
