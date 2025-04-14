//SunScream
#define UV A1
#define vstep 5.0/1023.0
#define calib 10
int in;
float Vo;
float index;
float sum;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(UV,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  sum = 0.0;
  for (int i = 0; i < 100; i++) {
        sum = sum + (analogRead(UV)*vstep*calib);
        delay(10);
  }
  index = sum/100;

  if (index <= 2) {
    
  }
  else if (index <= 5) {

  }
  else if (index <= 7) {

  }
  else if (index <= 10) {

  }
  else if (index <= 15) {

  }
  else {
    Serial.println("Either something broke or you about to become roasted human");
  }
}

