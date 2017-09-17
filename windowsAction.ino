void operateWindows() {
/*moves windows to state determined by newState variable
turns relays on til limit switch gets pushed*/
  unsigned long startTime = millis();
  if (newState == 1) {//open windows
    /*debug*/DPL("start opening windows");
    if ((PINC & 0x10) == 0x10) {//negative logic switch goes to low when pushed   digitalRead(limitSwOpen)
      if (relayTriggerLevel) {
        //turn on the relays (high level trigger)
        PORTB |= 0x01;
        PORTB |= 0x02;
        //wait til switch gets pushed      
        while ((PINC & 0x10) == 0x10) {
          if (millis() > startTime + windowOperationTimeout) {
            DPL("window operation timed out");
            break;
          }
        }      
        //turn off the relays (high level trigger)
        PORTB &= ~0x01;
        PORTB &= ~0x02;
      }
      else {
        //turn on the relays (low level trigger)
        PORTB &= ~0x01;
        PORTB &= ~0x02;
        //wait til switch gets pushed      
        while ((PINC & 0x10) == 0x10) {
          if (millis() > startTime + windowOperationTimeout) {
            DPL("window operation timed out");
            break;
          }
        }      
        //turn off the relays (low level trigger)
        PORTB |= 0x01;
        PORTB |= 0x02;
      }
      /*debug*/DPL("limit switch hit");
      /*debug*/DPL("done opening windows");
    }
    else {/*debug*/DPL("limit switch already active");}
  }  
     
  else {//close windows
    /*debug*/DPL("start closing windows");
    if ((PINC & 0x08) == 0x08) {//negative logic switch goes to low when pushed   digitalRead(limitSwClose)
      if (relayTriggerLevel) {
        //turn on the relays (high level trigger)
        PORTD |= 0x40;
        PORTD |= 0x80;
        //wait til switch gets pushed
        while ((PINC & 0x08) == 0x08) {
          if (millis() > startTime + windowOperationTimeout) {
            DPL("window operation timed out");
            break;
          }
        }
        //turn off the relays (high level trigger)
        PORTD &= ~0x40;
        PORTD &= ~0x80;
      }
      else {
        //turn on the relays (low level trigger)
        PORTD &= ~0x40;
        PORTD &= ~0x80;
        //wait til switch gets pushed
        while ((PINC & 0x08) == 0x08) {
          if (millis() > startTime + windowOperationTimeout) {
            DPL("window operation timed out");
            break;
          }
        }
        //turn off the relays (low level trigger)
        PORTD |= 0x40;
        PORTD |= 0x80;
      }
      /*debug*/DPL("limit switch hit");
      /*debug*/DPL("done closing windows");
    }
    else {/*debug*/DPL("limit switch already active");}
  } 
}

void turnOffRelays() {
  if (relayTriggerLevel) {
    //To turn off high level trigger relays set those pins low
    PORTB &= ~0x01;
    PORTB &= ~0x02;
    PORTD &= ~0x40;
    PORTD &= ~0x80;
  }
  else {
    //To turn off low level trigger relays set those pins high
    PORTB |= 0x01;
    PORTB |= 0x02;
    PORTD |= 0x40;
    PORTD |= 0x80;
  }
}

