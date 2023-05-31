#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

const char* ssid = "wifi_name"; //change
const char* password = "wifi_password"; //change

const int lcdColumns = 16;
const int lcdRows = 2;
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);

const int buttonPin = 4;

void setup() {
  pinMode(buttonPin, INPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  lcd.print("Procurando WI-FI");

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(1000);
  }

  lcd.clear();
  lcd.print("Conectado!");
  delay(1000);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);

  if (WiFi.status() == WL_CONNECTED) {
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();

    HTTPClient https;

    if (https.begin(*client, "your_api")) { //change
      int httpCode = https.GET();

      if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          lcd.clear();
          Serial.println(payload);
          lcd.setCursor(0, 0);
          lcd.print(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
  }

  delay(1000);
}
