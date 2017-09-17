
void measureBattery() {
  batteryVoltage = analogRead(batteryADC) * referenceVoltage / 1023 / (dividerLower/(dividerLower+dividerUpper));
  /*debug*/DP("Battery voltage (mV): ");
  /*debug*/DPL(batteryVoltage);
}

