#include <Adafruit_BLEMIDI.h>
#include <Adafruit_BLEBattery.h>
#include <Adafruit_ATParser.h>
#include <Adafruit_BLEEddystone.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <Adafruit_BLEGatt.h>
#include <Adafruit_BluefruitLE_UART.h>
#include <Adafruit_BLE.h>

#define NAME                            "Tohken"
#define SECRET                          "SECRET"

#define LED_PIN                         13
#define BLUEFRUIT_SPI_CS                8
#define BLUEFRUIT_SPI_IRQ               7
#define BLUEFRUIT_SPI_RST               4

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

void setup() {  
  pinMode(LED_PIN, OUTPUT);
  ble.begin(true);
  ble.sendCommandCheckOK("AT+GAPDEVNAME=" NAME);
  ble.sendCommandCheckOK("AT+BLEKEYBOARDEN=On");
}

void led_pattern_blink() {
  digitalWrite(LED_PIN, HIGH);
  delay(50);
  digitalWrite(LED_PIN, LOW);
  delay(50);
}

void loop() {
  while (!ble.isConnected()) {
    led_pattern_blink();
    led_pattern_blink();
    delay(750);
  }

  digitalWrite(LED_PIN, LOW);
  ble.println("AT+BLEKEYBOARD=" SECRET);
  ble.waitForOK();
  led_pattern_blink();
  ble.println("AT+BLEKEYBOARDCODE=00-00-28");
  ble.waitForOK();
  led_pattern_blink();
  ble.println("AT+BLEKEYBOARDCODE=00-00");
  ble.waitForOK();
  led_pattern_blink();
  delay(5000);
}
