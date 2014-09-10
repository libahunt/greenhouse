/* SD card connections
(SD card pins starting from the cut corner)

9
1 SS(Chip select)  --- Arduino D10, PB2 (with voltage divider)
2 MOSI             --- Arduino D11 (MOSI), PB3 (with voltage divider)
3 GND              --- GND
4 VCC              --- 3V3
5 SCK              --- Arduino D13 (SCK), PB5 (with voltage divider)
6 GND              --- GND
7 MISO             --- Arduino D12 (MISO), PB4
8
*/
const byte sdCS = 10;//PB2


/*
Motor relays connections

Clockwise - closing windows
Positive            - D6 = PD6
Negative            - D7 = PD7
Counterclockwise - opening windows
Positive            - D8 = PB0
Negative            - D9 = PB1
*/

/*will be used in direct port maipulation - no need to declare
const int relayClose1 = 6;//PD6
const int relayClose2 = 7;//PD7
const int relayOpen1 = 8;//PB0
const int relayOpen2 = 9;//PB1
*/

/*
Anemometer          - D4 = PD4
will be used in direct port maipulation - no need to declare
const int anemometer = 4;//PD4*/

/*
Temp sensor outside - PD3 INT1
Temp sensor inside  - PD2 INT0
*/

const int tempSensorIn = 2;//PD2
const int tempSensorInIntNr = 0; //interrupt number
const int tempSensorOut = 3;//PD3
const int tempSensorOutIntNr = 1; //interrupt number

/*
Limit switch closed/top  - A3 = D17 = PC3
Limit switch open/bottom - A4 = D18 = PC4
*/
/*will be used in direct port maipulation - no need to declare
const int limitSwClose = 17;//PC3
const int limitSwOpen = 18;//PC4
*/


/*
Atmega168 unused I/O-s so far:
PC0
PC1
PC2
PC5
PD5
PD0 - RX (no low impedance allowed)
PD1 - TX (no low impedance allowed)
PB7 and PB6 - normally XTAL connections

*/
