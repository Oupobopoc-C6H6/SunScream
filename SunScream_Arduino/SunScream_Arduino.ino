//SunScream
#include "BluetoothSerial.h"

#define UV 34 //GUVA-SD12SD
#define vstep 3.3/4095.0 //Vstep for ESP ADC
#define pConv 0.76 //must power with 5V??
#define alarm 33 //Active Buzzer Pin
#define limit 30 // maybe 3000?
#define tStep 1000 // time step in ms

float energy;
float power;
float val;
float acc = 0.0; // accumulation of UV-A power

BluetoothSerial SerialBT; // Create BT class

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Start serial com 115200 Baud
  SerialBT.begin("SunScream");  // Set Bluetooth device name
  Serial.println("Bluetooth started. Ready to pair.");
  pinMode(UV,INPUT); // Set UV pin to input
  pinMode(alarm,OUTPUT); //Set buzzer pin to output
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(UV);
  power = (val * vstep) / pConv; // in mW/cm^2
  energy = power * (tStep / 1000); // in mJ/cm^2 -- time step /1000 to convert to seconds
  acc = acc + energy; // multiplied by the time between each measuremnt 1 second

  SerialBT.print(val,5);
  SerialBT.print(" , ");
  SerialBT.print(energy,5);
  SerialBT.print(" , ");
  SerialBT.println(acc,5);

  while (acc > limit) {
    digitalWrite(alarm,HIGH);
    delay(500);
    digitalWrite(alarm,LOW);
    delay(500);
    SerialBT.println("Limit Exceded");
  }

  delay(tStep);
}



