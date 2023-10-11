void readBatteryLevel() {
  // Function to read battery level
  digitalWrite(VOLTAGE_DIVIDER_PIN, HIGH);  // This pin needs to be pulled HIGH before battery voltage can be read
  delay(1);
  float measurement = (float)analogRead(BATTERY_LEVEL_PIN);
  float batteryVoltage = (measurement / 4095.0) * 7.26;  // Convert pin reading to battery voltage
  digitalWrite(VOLTAGE_DIVIDER_PIN, LOW);                // Set pin low to conserve energy
  if (printToSerial) Serial.println(batteryVoltage);
  if (batteryVoltage < 3.7) lowBattery = true;  // If battery voltage drops below 3.5V, set low battery flag, which will turn on low battery LED sequence
  else lowBattery = false;
}