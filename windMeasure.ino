void measureWind() {
  
  /*debug*/DPL("starting measuring wind");
  
  unsigned long measureStartTime = millis();
  lastAnemoOutput = PIND & 0x10;//digitalRead(anemometer);
  anemoTogglesCount = 0;
  millisNow = millis();
  while (millisNow - measureStartTime < windMeasureTime) {
    anemoOutput = PIND & 0x10;//digitalRead(anemometer);
    if (lastAnemoOutput != anemoOutput) {
     debounceStartTime = millis(); 
    }
    else if (millisNow - debounceStartTime > anemoDebounceThres) {
     anemoTogglesCount++; 
    }
    lastAnemoOutput = anemoOutput;
    millisNow = millis();
  }
  /*debug*/DP("anemoTogglesCount");
  /*debug*/DPL(anemoTogglesCount);
  anemoRpm = anemoTogglesCount * 60*1000 / (windMeasureTime * 12);
  /*my anemometer's Hall sensor toggles 6 times back and forth in one cycle
  because we count from LOW to HIGH as well as HIGH to LOW that means 12 toggles,
  60*1000 makes count per millisecond into per minute*/
  
  /*debug*/DP("anemoRpm");
  /*debug*/DPL(anemoRpm);
  
}
