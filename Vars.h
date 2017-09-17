
int tempIn = 222;//222 means unknown
int rhIn = -1;//-1 means unknown
int tempOut = 222;//222 means unknown
int rhOut= -1;//-1 means unknown
int anemoMaxRpm = -1;//rpm reading from anemometer, -1 means unknown
byte newState = 2;//0-windows closed, 1- windows open, 2-unknown
byte state = 2;
int batteryVoltage = 0;//in millivolts
bool windowError = false;

//controller wakes up each second but only after a set interval it should do measurements
int secondsCounter = 0; //helper for counting up to desired interval
boolean workCycle = false; //helper for passing the state from interrupt to loop()

byte anemoOutput;
byte lastAnemoOutput;
unsigned long anemoTogglesCount;

unsigned long millisNow;
unsigned long debounceStartTime;
int didToggle = 0;//boolean helper for anemometer debouncing

int i;
