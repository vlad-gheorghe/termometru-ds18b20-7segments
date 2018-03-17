/* Arduino 7 Segment Display Thermometer with DS18B20 temp Sensor
   Dev: Vasilakis Michalis // Date: 25/7/2015 // www.ardumotive.com */

//http://www.instructables.com/id/Seven-Segment-Display-Thermometer-Arduino-Based/

//Libraries
#include "SevenSeg.h"
#include <OneWire.h>
#include <DallasTemperature.h>

/*---------------DS18B20--------------------*/
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS A1
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

/*---------7 Segment 2 digit display--------*/
//Defines the segments A-G: SevenSeg(A, B, C, D, E, F, G);
SevenSeg disp (2,3,4,5,12,7,8);
//Number of 7 segments
const int numOfDigits =3;
//CC(or CA) pins of segment
int digitPins [numOfDigits]={11,10,9};//11-left, 10-midle, 9-left

//Variables
int digitL;
int digitR;
int temp; 

void setup() {
  sensors.begin();
  //Defines the number of digits to be "numOfDigits" and the digit pins to be the elements of the array "digitPins"
    disp.setDigitPins ( numOfDigits , digitPins );
    //Only for common cathode 7segments
    disp.setCommonCathode();
    //Control brightness (values 0-100);
    disp.setDutyCycle(80);
    
    disp.setTimer (2);
    disp.startTimer ();
    disp . setDPPin (13) ;
  
}

void loop(){
  //Get temperature  
  sensors.requestTemperatures();  
 float temp = sensors.getTempCByIndex(0);
 
  disp.write(temp,1);
}
ISR( TIMER2_COMPA_vect ){
 disp.interruptAction ();
 }
