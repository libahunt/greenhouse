/*** WORK PARAMETER VARIABLES - change if nescessary ***/

/***
Tomato plants require:
20-25 degrees Celsius daytime (30 critically bad)
16-18 degrees Celsius nighttime (13 needed, though short periods close to freezing do not kill it either)
Relative humidity 60-70%. 80-90% is bad.
If there is not sufficient light the temperatures may be lowered (to 12 deg celsius) for better results.
***/

/*first we check windspeed, because a storm can break open windows*/
const int closeWindowsAnemoRpm = 90;
const int openWindowsAnemoRpm = 60;

/*if windspeed allows open windows we want to maintain ideal temperature inside the greenhouse*/
const int openWindowsTemp = 24;
const int closeWindowsTemp = 20;

/*If the RH is getting too high we ventilate on lower temperatures also, but only if outside air is more dry*/ 
const int moistRH = 75; //RH higher than this inside makes this rule apply
const int moistRHOutsideDifference = 10; //RH outside has to be this much lower
const int openWindowsIfMoistTemp = 18; //min temperature inside to open windows in case of moisture
const int closeWindowsIfMoistTemp = 15; //temperature inside to close windows in case of moisture


/*how often the controller wakes up and performs measurements, value in SECONDS*/
const int interval = 30;//30*60; //30 mins

/*how many attempts to make with DHT11 temperature/RH sensors if the communication fails*/
int tempReadMaxTries = 3;

/*over how long peiod to count anemometer RPM, in MILLISECONDS*/
unsigned long windMeasureTime = 10000;
/*debouncing threshold for anemometer comparator output in milliseconds*/
unsigned long anemoDebounceThres = 10;

