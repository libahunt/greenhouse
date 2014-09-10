void watchdogInterruptSetup() {
  //Based on https://github.com/tdicola/Low_Power_Wifi_Datalogger Example 2
  
  noInterrupts();
  
  // Set the watchdog reset bit in the MCU status register to 0.
  MCUSR &= ~(1<<WDRF);
  
  // Set WDCE and WDE bits in the watchdog control register.
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  // Set watchdog clock prescaler bits to a value of 1 second.
  WDTCSR = (1<<WDP1) | (1<<WDP2);
  
  // Enable watchdog as interrupt only (no reset).
  WDTCSR |= (1<<WDIE);
  
  // Enable interrupts again.
  interrupts();
  
  /*debug*/DPL("Watchdog interrupt set");
  
} //watchdogInterruptSetup()

ISR(WDT_vect) {
  //count the time up to mesurement interval
  secondsCounter++;
  //next finishes goToSleep if WDT woke it up and goes to loop
  //or goes back to where it was in loop if in the middle of work cycle
}


void goToSleep() { //routines needed before putting controller to sleep and then going into sleep mode
  /*debugDP("sleep in 1 s");*/
  /*following delay is needed to not mess up serial communication*/
  /*debug*/#ifdef DEBUG
    /*debug*/delay(500);
  /*debug*/#endif
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // Turn off the ADC while asleep.
  power_adc_disable();

  // Enable sleep and enter sleep mode.
  sleep_mode();

  // CPU is now asleep and program execution completely halts!
  // Once awake, execution will resume at this point.
  
  // When awake, disable sleep mode and turn on all devices.
  sleep_disable();
  power_all_enable();

  //now leaves interrupt routine and does things in loop()

}
