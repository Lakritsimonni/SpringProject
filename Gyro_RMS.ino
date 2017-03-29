

/*
 * Copyright (c) 2016 Intel Corporation.  All rights reserved.
 * See the bottom of this file for the license terms.
 */




/*
   This sketch example demonstrates how the BMI160 on the
   Intel(R) Curie(TM) module can be used to read gyroscope data
*/

/* 
 *  Added gyroscope RMS measurements for the axis : x, y z.
 *  Added Timestamp
 *  To-Do: 
 *  
 *  
 *  
 *  Add JSon
 *  
 *  
 *  
 */



#include <CurieTime.h>
#include "CurieIMU.h"


int sample_interval = 500; //Milliseconds

float rms_x, rms_y, rms_z = 0; 
void setup() {

setTime(20, 49, 00, 24, 03, 2017);


  
  Serial.begin(9600); // initialize Serial communication
  while (!Serial);    // wait for the serial port to open

  // initialize device
  Serial.println("Initializing IMU device...");
  CurieIMU.begin();

  // Set the accelerometer range to 250 degrees/second
  CurieIMU.setGyroRange(250);
}

void loop() {
  
  int temp_sensor = analogRead(A0);
  
  /* Global RMS values for Gyro Vectors.
 Will be initialized 0 every time loop runs */
  // read gyro measurements from device, scaled to the configured range
 
Gyro_RMS();
  // display tab-separated gyro x/y/z values
  Serial.print("g_rms_xyz:\t");
  Serial.print(rms_x);
  Serial.print("\t");
  Serial.print(rms_y);
  Serial.print("\t");
  Serial.print(rms_z);
  Serial.print("\t");
  Serial.print("Temperature: ");
  Serial.print(temp_sensor);
  Serial.print("\t");
  Serial.print("Time is: ");
   print2digits(hour());
  Serial.print(":");
  print2digits(minute());
  Serial.print(":");
  print2digits(second());
  Serial.println("\t");
  
 /* Serial.print("\t");
  Serial.print(gy);
  Serial.print("\t");
  Serial.print(gz);
  Serial.println();
*/
}


void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.print('0');
  }
  Serial.print(number);
}



float Gyro_RMS(){

float gx, gy, gz; //scaled Gyro values
float exponential_x = 0;
float addition_x = 0;
float exponential_y = 0;
float addition_y = 0;
float exponential_z = 0;
float addition_z = 0;
float mean_x, mean_y, mean_z = 0;
rms_x = 0;
rms_y = 0;
rms_z = 0;

for (int i=0; i < 10; i++)
        {

     delay(sample_interval);  
    //Collect 10 samples from the gyroscope, put them in ^2 exponents and add them up into 
    //variable  addition_?
     CurieIMU.readGyroScaled(gx, gy, gz);
     exponential_x = pow(gx,2);       // X axel
     addition_x = addition_x + exponential_x;

     exponential_y = pow(gy,2);       //Y axel
     addition_y = addition_y + exponential_y;

     exponential_z = pow(gz,2);       //Z axel
     addition_z = addition_z + exponential_z;
      
    //  Serial.println(addition_z);  //Debug
          
        }
        
mean_x = addition_x / 10;
rms_x = sqrt(mean_x);

mean_y = addition_y / 10;
rms_y = sqrt(mean_y);

mean_z = addition_z / 10;
rms_z = sqrt(mean_z);

return rms_x, rms_y, rms_z;
}






















