//SunScream
#define UV A1
#define vstep 5.0/1023.0
#define calib 10
#define alarm 9
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
    Serial.println("Most people are safe, you pastey mfs Put on 15+ SPF");
  }
  else if (index <= 5) {
    alarmLoop();
  }
  else if (index <= 7) {
    alarmLoop();
  }
  else if (index <= 10) {
    alarmLoop();
  }
  else if (index <= 15) {
    alarmLoop();
  }
  else {
    Serial.println("Either something broke or you're about to become roasted human");
  }
}

void alarmLoop() {
  while (true) {
    digitalWrite(alarm,HIGH);
  }
}
