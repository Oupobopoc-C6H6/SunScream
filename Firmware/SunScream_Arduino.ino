//SunScream
#include "BluetoothSerial.h"

#define UV 34 //GUVA-SD12SD
#define vstep 3.3/4095.0 //Vstep for ESP ADC
#define pConv 0.0025 //mW/cm^2
#define alarm 33 //Active Buzzer Pin
#define limit 30.0 // maybe 3000?
#define tStep 1000 // time step in ms

float val;
float UVI;
float energy;
float power;
float acc = 0.0; // accumulation of UV-A power
float over;

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
  val = analogRead(UV); // ADC input
  UVI = (val +  82.1) / 20.5; // Calibration curve
  power = UVI * pConv; // in mW/cm^2
  energy = power * (tStep / 1000); // in mJ/cm^2 -- time step /1000 to convert to seconds
  acc = acc + energy; // multiplied by the time between each measuremnt 1 second

  SerialBT.print("Current UV Energy (mJ/cm^2): ");
  SerialBT.print(energy,1);
  SerialBT.print(", Energy Accumulation (mJ/cm^2): ");
  SerialBT.println(acc,1);

  while (acc > limit) {
    digitalWrite(alarm,HIGH);
    delay(500);
    digitalWrite(alarm,LOW);
    delay(500);
    SerialBT.print("Limit Exceded, ");
    over = acc - limit;
    SerialBT.print(over,1);
    SerialBT.print(" mJ/cm^2 over set limit");
  }

  delay(tStep);
}