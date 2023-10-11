void doButtons(unsigned long int currentTime_) {
  int buttonValueLeft = digitalRead(LEFT_PIN);
  int buttonValueRight = digitalRead(RIGHT_PIN);

  // LEFT button
  if (buttonValueLeft != lastButtonStateLeft) {
    // Check if current button value is different from previous button value
    prevTimeLeft = millis();
  }
  if ((currentTime_ - prevTimeLeft) > debounceTime) {
    // Check that debounce time has been exceeded (to prevent accidental double presses)
    if (buttonValueLeft != buttonStateLeft) {
      // Check that button value is different from previous button value
      buttonStateLeft = buttonValueLeft;
      if (buttonStateLeft == LOW) {
        // Check if button has been pressed
        if (printToSerial) Serial.println("The button left is pressed");
        bleKeyboard.write(KEY_LEFT_ARROW);
        prevTimeSleep = millis();  // Update sleep time to last recorded activity
      }
    }
  }

  // RIGHT button
  if (buttonValueRight != lastButtonStateRight) {
    // Check if current button value is different from previous button value
    prevTimeRight = millis();
  }
  if ((currentTime_ - prevTimeRight) > debounceTime) {
    // Check that debounce time has been exceeded (to prevent accidental double presses)
    if (buttonValueRight != buttonStateRight) {
      // Check that button value is different from previous button value
      buttonStateRight = buttonValueRight;
      if (buttonStateRight == LOW) {
        // Check if button has been pressed
        if (printToSerial) Serial.println("The button right is pressed");
        bleKeyboard.write(KEY_RIGHT_ARROW);
        prevTimeSleep = millis();  // Update sleep time to last recorded activity
      }
    }
  }

  lastButtonStateLeft = buttonValueLeft;    // Update last know left button value
  lastButtonStateRight = buttonValueRight;  // Update last know right button value
}