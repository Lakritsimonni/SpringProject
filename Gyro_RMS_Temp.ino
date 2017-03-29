#include <DallasTemperature.h>
#include <L3G.h>
#include <Wire.h>
#include <OneWire.h>
#define ONE_WIRE_BUS 2
L3G gyro;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);




int sample_interval = 500; //Milliseconds
float meanTemperature;
float rms_x, rms_y, rms_z = 0; 
void setup() {




  
  Serial.begin(9600); // initialize Serial communication
  Wire.begin(4,5);
  sensors.begin();


  if (!gyro.init())
  {
    Serial.println("Failed to autodetect gyro type!");
    while (1);
  }

  gyro.enableDefault();
}

void loop() {
  
 
  
  
  
 
  Gyro_RMS();
  meanTemp();

  /*Serial.print("Mean temp: ");
  Serial.print(meanTemperature);
  Serial.print("\n");
  //Serial.print("G ");
  Serial.print("X: ");
  Serial.print("\t");
  Serial.print(rms_x);
  Serial.print("\t");
  Serial.print(" Y: ");
  Serial.print("\t");
  Serial.print(rms_y);
  Serial.print("\t");
  Serial.print(" Z: ");
  Serial.print("\t");
  Serial.println(rms_z);
  */
  delay(100);
}

float Gyro_RMS(){

int gx, gy, gz; //scaled Gyro values
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
     gyro.read();

     
    //Collect 10 samples from the gyroscope, put them in ^2 exponents and add them up into 
    //variable  addition_?
    
     gx = gyro.g.x;
     exponential_x = pow(gx,2);       // X axel
     addition_x = addition_x + exponential_x;

     gy = gyro.g.y; 
     exponential_y = pow(gy,2);       //Y axel
     addition_y = addition_y + exponential_y;

     gz = gyro.g.z; 
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
// Make array here
}


float meanTemp(){


  float tempRead; 
  float combineTemp = 0;
  for (int i = 0; i < 10; i++){
    
  sensors.requestTemperatures();
  tempRead = sensors.getTempCByIndex(0);
  combineTemp = combineTemp + tempRead;
  
  }
   meanTemperature = combineTemp / 10;
   return meanTemperature;
}


















