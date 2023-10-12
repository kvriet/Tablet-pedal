/*
 Katrien van Riet - September 2023 - v5.5
 Keyboard code from: https://github.com/T-vK/ESP32-BLE-Keyboard
 Code for ESP32 WROVER version (board T18_3.0). Choose board: ESP32 Wrover Kit (all versions)
 If your board manager doesn't show the WROVER board, put this URL under "Additional boards manager URLs" in Preferences:
 https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
 */

#include <BleKeyboard.h>
#include <driver/adc.h>
#include "esp_adc_cal.h"

//// VARIABLES YOU CAN CHANGE ////
BleKeyboard bleKeyboard("Pedal Page Turner", "CM van Riet", 100);
// ("Bluetooth Device Name", "Bluetooth Device Manufacturer", initial battery level of your device)
// You can change the bluetooth device name to suit your own needs

bool printToSerial = false;                   // Set to 'true' to print debugging statements to serial port
bool lowBatteryMessage = true;                // Set to 'false' to disable LED flashing when battery is low
unsigned int timeUntilSleepMins = 15;         // Time in minutes until device goes to sleep
unsigned int batteryMeasureIntervalMins = 1;  // Time in minutes between battery level readings


//// THINGS THAT SHOULD BE LEFT ALONE ////
const int LEFT_PIN = 2;
const int RIGHT_PIN = 4;
const int LED_PIN = 5;
const int VOLTAGE_DIVIDER_PIN = 14;  // Not sure what this pin does, but for battery voltage reading, it needs to be HIGH
                                     // To conserve energy, pin 14 is kept LOW when not reading battery voltage level
const int BATTERY_LEVEL_PIN = 35;
const int debounceTime = 15;  // Debounce time in millis for buttons
bool flagLeft = false;
bool flagRight = false;
bool lowBattery = false;
unsigned long int timeMultiplier = 60000;      // Multiplier from mins to millis = 60 * 1,000
unsigned long int prevTimeSleep = 0;           // In millis
unsigned long int prevTimeBatteryMeasure = 0;  // In millis
unsigned long int prevTimeLeft = 0;            // In millis
unsigned long int prevTimeRight = 0;           // In millis
int buttonStateLeft;
int lastButtonStateLeft = LOW;
int buttonStateRight;
int lastButtonStateRight = LOW;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(VOLTAGE_DIVIDER_PIN, OUTPUT);

  digitalWrite(VOLTAGE_DIVIDER_PIN, LOW);  // Preserve energy

  startupLED();  // Show startup LED sequence
  bleKeyboard.begin();

  if (printToSerial) Serial.begin(115200);
  if (printToSerial) Serial.println("Starting BLE!");

  // Two statements below are needed for battery measurement
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize((adc_unit_t)ADC_UNIT_1, (adc_atten_t)ADC_ATTEN_DB_2_5, (adc_bits_width_t)ADC_WIDTH_BIT_12, 1100, &adc_chars);
}

void loop() {
  unsigned long int currentTime = millis();  // Current time in millis

  if ((currentTime - prevTimeSleep) > timeUntilSleepMins * timeMultiplier) {
    // Board goes to deep sleep if no buttons are pressed for a certain time
    if (printToSerial) Serial.println("Entering deep sleep now!");
    esp_deep_sleep_start();
  }

  if (bleKeyboard.isConnected()) {
    // If pedal is paired through bluetooth, buttons will be read
    doButtons(currentTime);
  }

  if ((currentTime - prevTimeBatteryMeasure) > batteryMeasureIntervalMins * timeMultiplier) {
    // This function reads the battery level every few minutes
    readBatteryLevel();
    if (lowBattery && lowBatteryMessage) {
      lowBatteryLED();
    }
    prevTimeBatteryMeasure = currentTime;
  }

  delay(20);  // Small delay to save energy (don't increase further than 50!)
}
