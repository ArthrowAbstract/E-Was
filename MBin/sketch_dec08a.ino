  #include <Servo.h>
Servo servo;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

servo.attach(8);

servo.write(0);

delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Go for it");
  while (Serial.available()==0){
    }
  int a =Serial.parseInt();
  servo.write(a);
  delay(1000);
  int dummy = Serial.read();

}
