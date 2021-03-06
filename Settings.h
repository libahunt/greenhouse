/*** WORK PARAMETER VARIABLES - change if nescessary ***/

/***
Tomato plants require:
20-25 degrees Celsius daytime (30 critically bad)
16-18 degrees Celsius nighttime (13 needed, though short periods close to freezing do not kill it either)
Relative humidity 60-70%. 80-90% is bad.
If there is not sufficient light the temperatures may be lowered (to 12 deg celsius) for better results.
***/

/*first we check windspeed, because a storm can break open windows*/
const int closeWindowsAnemoRpm = 60;
const int openWindowsAnemoRpm = 40;

/*if windspeed allows open windows we want to maintain ideal temperature inside the greenhouse*/
const int openWindowsTemp = 24;
const int closeWindowsTemp = 20;

/*If the RH is getting too high we ventilate on lower temperatures also, but only if outside air is more dry*/ 
const int moistRH = 75; //RH higher than this inside makes this rule apply
const int moistRHOutsideDifference = 10; //RH outside has to be this much lower
const int openWindowsIfMoistTemp = 18; //min temperature inside to open windows in case of moisture
const int closeWindowsIfMoistTemp = 15; //temperature inside to close windows in case of moisture


/*how often the controller wakes up and performs measurements, value in SECONDS*/
const int interval = 15*60;//15 mins

/*how many attempts to make with DHT11 temperature/RH sensors if the communication fails*/
const int tempReadMaxTries = 3;

/*over how long period to count anemometer RPM for one result, in MILLISECONDS*/
const unsigned long windMeasureTime = 10000; //10 seconds
/*how many samples to take - the highest result is used to determine dangerous wind speed.
NOTE: You might want to reduce the number of samples while debugging with serial to save time*/
int windMeasureReps = 12; //10sec * 12 means the samples are taken over 2 min period

/*debouncing threshold for anemometer comparator output in milliseconds*/
const unsigned long anemoDebounceThres = 10;

/*there are different types of relays that are triggered by either low (0) or high (1) level, choose which ones you have*/
const bool relayTriggerLevel = 0;

/*how long to spin the motor for opening or closng windows if the limit switch does not indicate it's done (in milliseconds)*/
const unsigned long windowOperationTimeout = 120*1000;

/*Battery monitoring voltage divider resistor values (in ohms)*/
const int dividerUpper = 64759;
const int dividerLower = 32240;
/*5V regulator exact output in millivolts - if you can measure it. Otherwise approximate 5000.*/
const int referenceVoltage = 5000;

