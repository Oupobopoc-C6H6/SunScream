#define UV A1
float index;
char in = 'o';

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    in=Serial.read();
    if(in=='\n'){
      in='o';
    }
  }
  if (in == 't') {
    index = analogRead(UV) * 10;
    Serial.println(index);
    in = 'o';
  }
  delay(200);
}
