void operateWindows() {
/*moves windows to state determined by newState variable
turns relays on til limit switch gets pushed*/
  if (newState == 1) {//open windows
    /*debug*/DPL("start opening windows");
    if ((PINC & 0x10) > 0) {//negative logic switch goes to low when pushed   digitalRead(limitSw)
      //turn on the relays
      PORTB |= 0x01;
      PORTB |= 0x02;
      //wait til switch gets pushed
      while ((PINC & 0x10) > 0) {
        
      }
      /*debug*/DPL("limit switch hit");
      //turn off the relays
      PORTB &= ~0x01;
      PORTB &= ~0x02;
      /*debug*/DPL("done opening windows");
    }
    else {/*debug*/DPL("limit switch already active");}
  }  
     
  else {//close windows
    /*debug*/DPL("start closing windows");
    if ((PINC & 0x08) > 0) {//negative logic switch goes to low when pushed   digitalRead(limitSw)
      //turn on the relays
      PORTD |= 0x40;
      PORTD |= 0x80;
      //wait til switch gets pushed
      while ((PINC & 0x08) > 0) {
        
      }
      /*debug*/DPL("limit switch hit");
      //turn off the relays
      PORTD &= ~0x40;
      PORTD &= ~0x80;
      /*debug*/DPL("done closing windows");
    }
    else {/*debug*/DPL("limit switch already active");}
  } 
}
