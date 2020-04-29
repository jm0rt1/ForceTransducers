/*
 Example using the SparkFun HX711 breakout board with a scale
 By: Nathan Seidle
 SparkFun Electronics
 Date: November 19th, 2014
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 This example demonstrates basic scale output. See the calibration sketch to get the calibration_factor for your
 specific load cell setup.

 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE

 The HX711 does one thing well: read load cells. The breakout board is compatible with any wheat-stone bridge
 based load cell which should allow a user to measure everything from a few grams to tens of tons.
 Arduino pin 2 -> HX711 CLK
 3 -> DAT
 5V -> VCC
 GND -> GND

 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.

*/

#include "HX711.h"

#define calibration_factor 3000 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT1  3
#define CLK1  2
#define DOUT2  5
#define CLK2  4
#define DOUT3  7
#define CLK3  6
#define DOUT4  9
#define CLK4  8

HX711 scale1;
HX711 scale2;
HX711 scale3;
HX711 scale4;

void setup() {
  Serial.begin(115200);


  scale1.begin(DOUT1, CLK1);
  scale2.begin(DOUT2, CLK2);
  scale3.begin(DOUT3, CLK3);
  scale4.begin(DOUT4, CLK4);
  
  scale1.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale2.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale3.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale4.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch

  /*
  scale1.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  scale2.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  scale3.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  scale4.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  */
}

void loop() {
  char temp = Serial.read();
  if (temp == '1') {
    //Serial.print("Reading: ");
    Serial.print(scale1.get_units(), 1); //scale.get_units() returns a float
    //Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
    Serial.println();
  } else if (temp == '2') {
    //Serial.print("Reading: ");
    Serial.print(scale2.get_units(), 1); //scale.get_units() returns a float
    //Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
    Serial.println();
  } else if (temp == '3') {
    //Serial.print("Reading: ");
    Serial.print(scale3.get_units(), 1); //scale.get_units() returns a float
    //Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
    Serial.println();
  }else if (temp == '4') {
    //Serial.print("Reading: ");
    Serial.print(scale4.get_units(), 1); //scale.get_units() returns a float
    //Serial.print(" lbs"); //You can change this to kg but you'll need to refactor the calibration_factor
    Serial.println();
  } else if (temp == '5') {
    scale1.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
    scale2.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
    scale3.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
    scale4.tare();
  }

}
