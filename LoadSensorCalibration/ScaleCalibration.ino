//----------------------------------
//--- Weight sensor calibration tool
//----------------------------------
#include <OneWire.h>
#include <Wire.h>
#include <HX711.h>
#include <DS3231.h>

HX711 scale1(A1, A0);   
HX711 scale2(A3, A2);
DS3231 RTC;   

int i = 1;
double  WGHT_E_A1 = 2.79888E-18;
double  WGHT_E_B1= -6.417E-11;
double  WGHT_E_C1 = 0.000447765;
double  WGHT_E_D1 = -897.6871728;

double  WGHT_E_A2 = 3.44083E-19;
double  WGHT_E_B2= -7.60712E-12;
double  WGHT_E_C2 = 2.2515E-5;
double  WGHT_E_D2 = 140.7635036;
  
void setup() {
  Serial.begin(9600);
  Wire.begin();
  RTC.begin(); 
  Serial.println("HX711 CALIBRATION PROTOCOL");
  Serial.println("==========================");
  scale1.set_scale(); 
  scale2.set_scale(); 
   
}

void loop() {
  double reading1 = 0;
  double weight1 = 0;
  double reading2 = 0;
  double weight2 = 0;
  char tempBuffer[8];
  char temperature[6];
  
    reading1 = scale1.get_units(30);
    weight1 = WGHT_E_A1 * pow(reading1,3) + WGHT_E_B1 * pow(reading1,2) + WGHT_E_C1 * reading1 + WGHT_E_D1;
    if(weight1 < 0){
      weight1 = 0;
    }
    
    reading2 = scale2.get_units(30);
    weight2 = WGHT_E_A2 * pow(reading2,3) + WGHT_E_B2 * pow(reading2,2) + WGHT_E_C2 * reading2 + WGHT_E_D2;
    if(weight2 < 0){
      weight2 = 0;
    }
    Serial.print(i);
    Serial.print("   SENSOR1 reading: ");
    Serial.print(reading1);
    Serial.print("  weight[kg]: ");
    Serial.print(double(weight1));
    Serial.print("         SENSOR2 reading: ");
    Serial.print(reading2);
    Serial.print("  weight[kg]: ");
    Serial.print(double(weight2));
    Serial.print("  Temperature[C]: ");
    dtostrf(RTC.getTemperature(), 4, 2, temperature);
    sprintf(tempBuffer,"%s",temperature);
    Serial.print(tempBuffer);
    Serial.println("");
    scale1.power_down();            
    scale2.power_down(); 
    delay(3000);
    scale1.power_up();
    scale2.power_up();
    i++;
}




