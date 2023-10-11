void startupLED() {
  // Startup LED sequence
  for (int i = 0; i < 3; i++) {
    // For WROVER, pin 5 pulled HIGH will turn on LED
    digitalWrite(LED_PIN, HIGH);
    delay(400);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}

void lowBatteryLED() {
  // LED sequence for low battery
  for (int i = 0; i < 5; i++) {
    // For WROVER, pin 5 pulled HIGH will turn on LED
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
    delay(50);
  }
}