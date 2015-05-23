void measureWind() {
  
  /*debug*/DPL("starting measuring wind");
  
  int anemoRpmSamples[windMeasureReps];
  
  
  for (i=0; i<windMeasureReps; i++) {
  
    unsigned long measureStartTime = millis();
    lastAnemoOutput = PIND & 0x10;//digitalRead(anemometer);
    anemoTogglesCount = 0;
    didToggle = 0;
    millisNow = millis();
    while (millisNow - measureStartTime < windMeasureTime) {
      anemoOutput = PIND & 0x10;//digitalRead(anemometer);
      if (lastAnemoOutput != anemoOutput) {
       debounceStartTime = millis();
       didToggle = 1; 
      }
      else if (didToggle && millisNow - debounceStartTime > anemoDebounceThres) {
       anemoTogglesCount++;
       didToggle = 0;
      }
      lastAnemoOutput = anemoOutput;
      millisNow = millis();
    }
    /*debug*/DP("anemoTogglesCount = ");
    /*debug*/DPL(anemoTogglesCount);
    anemoRpmSamples[i] = anemoTogglesCount * 60*1000 / (windMeasureTime * 12);
    /*my anemometer's Hall sensor toggles 6 times back and forth in one cycle
    because we count from LOW to HIGH as well as HIGH to LOW that means 12 toggles,
    60*1000 makes count per millisecond into per minute*/
    /*debug*/DP("sample ");
    /*debug*/DP(i);
    /*debug*/DP(" result is ");
    /*debug*/DPL(anemoRpmSamples[i]);
        
  }
  
  anemoMaxRpm = 0;
  for (i=0; i<windMeasureReps; i++) {
    if (anemoRpmSamples[i] > anemoMaxRpm) {
      anemoMaxRpm = anemoRpmSamples[i];
    }
  }
  
  
  /*debug*/DP("anemoMaxRpm = ");
  /*debug*/DPL(anemoMaxRpm);
  
}
