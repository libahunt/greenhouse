/*Problems:
code size - SD card functions and debug code do not fit at the same time
atmega168
switch off SD logging and test the rest of the code with DEBUG

*/



#include <SdFat.h>
#include <idDHT11.h>

#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>


/*debug*/
#define DEBUG /*comment this line out in production then all Serial instructsions are ignored*/
#include "DebugUtils.h"


#include "layout.h" //Pin connections
#include "Settings.h" //Variables that might need tweaking
#include "Vars.h"


/***************************************************************
   initialize library objects
****************************************************************/

void dht11_wrIn(); // must be declared before the lib initialization
void dht11_wrOut(); // must be declared before the lib initialization

idDHT11 DHT11A(tempSensorIn, tempSensorInIntNr, dht11_wrIn);
idDHT11 DHT11B(tempSensorOut, tempSensorOutIntNr, dht11_wrOut);

SdFat sd;
SdFile file;

/***************************************************************
   SETUP 
****************************************************************/

void setup() {
  
  /*debug*/#ifdef DEBUG
    /*debug*/Serial.begin(9600);
  /*debug*/#endif
  
  /*Pin modes - I am using direct port manipulation instead, but for quick grasp in Arduino language it would be:
  pinMode(relayClose1, OUTPUT);
  pinMode(relayClose2, OUTPUT);
  pinMode(relayOpen1, OUTPUT);
  pinMode(relayOpen2, OUTPUT);
  pinMode(anemometer, INPUT);
  pinMode(tempSensorIn, INPUT);
  pinMode(tempSensorOut, INPUT);
  pinMode(limitSwClose, INPUT);
  pinMode(limitSwOpen, INPUT);
  */
  
  /*port B:
  PD0, PD1 relays = outputs
  PB2 - sd card chip select = output - don't know if I have to explicitly set?
  PB3, PB4, PB5 - miso, mosi, sck - SD library will take care of them
  PB7, PB6 - unused, normally would be xtal*/
  DDRB = DDRB | 0x07;//outputs
  
  /*port C:
  PC0-PC2 unused
  PC3, PC4 - limit switches = inputs
  PC5 unused
  */
  DDRC = DDRC & ~0x18;//inputs
  
  /*port D:
  PD0, PD1 - TX and RX unused and anyway better not to touch
  PD2,PD3 temp sensors - leave for the library to handle
  PD4 - anemometer = input
  PD5 - unused
  PD6, PD7 relays = outputs*/
  DDRD = DDRD | 0xC0;//outputs
  DDRD = DDRD & ~0x10;//inputs
  
  
  logReset();//record the fact of setup running in log file and add column headings
  
  watchdogInterruptSetup();//set up 1 second watchdog timer interrupts for waking up from sleep
  
}


/***************************************************************
   MAIN LOOP
****************************************************************/

void loop() {
  
  /*debug*/DP("secondsCounter =");
  /*debug*/DPL(secondsCounter);
  
  
  if (secondsCounter >= interval) {
    secondsCounter = 0;
    workCycle = true;
  }
  
  //if the interval has passed, take measurements and do action
  if (workCycle) {
    
    /*debug*/DPL("started work cycle");
    
    /***measure***/    
    measureTemp();
    /*debug*/DPL("temp measurements done");
    measureWind();
    /*debug*/DPL("wind measurement done");
    
    
    /***decide***/
    
    if (anemoRpm >= closeWindowsAnemoRpm) {
    //has got too windy, close windows disregarding anything else
     newState = 0;//closed
     /*debug*/DPL("too windy");
    }
    else if (anemoRpm <= openWindowsAnemoRpm || state == 1) {
    //wind is safely low (time to open) 
    //or medium (but lower than closing threshold) and windows are already open
    //concider other factors
      if (rhIn >= moistRH && rhOut <= rhIn-moistRHOutsideDifference) {
      //inside moisture is high but outside is dryer, so ventilating would have a point
      //check for temperature conditions
        if (tempIn >= openWindowsIfMoistTemp || (state == 1 && tempIn >= closeWindowsIfMoistTemp)) {
        //temperature sufficent to open in case of moisture OR already open and temp within allowed range
          newState = 1;//open
          /*debug*/DPL("moisture and warm");
        }
        else {//too cold even for moisture conditions
          newState = 0;//closed
          /*debug*/DPL("moisture and cold");
        }
      }
      else {
      //normal moisture conditions or outside also too moist
        if (tempIn >= openWindowsTemp || (state == 1 && tempIn >= closeWindowsTemp)) {
        //temperature sufficent to open OR already open and temp within allowed range
          newState = 1; //open
          /*debug*/DPL("normal warm");
        }
        else {//too cold
          newState = 0;//close
          /*debug*/DPL("normal cold");
        }
      }
    }
    else {
    //wind is below closing, but over opening threshold, windows are closed
    //leave them closed til wind slows down even more
      newState = 0;//closed
      /*debug*/DPL("medium wind, not opening yet");
    }
    
    
    
    /***log data***/
    logData();
    
    /***move windows***/
    if (newState != state) {
      operateWindows();
    }
    
    workCycle = false;//all done, go back to passive mode
    
  }
  
  goToSleep(); //back to sleep til next interrupt
  
}


