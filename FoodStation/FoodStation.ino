#include <Servo.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define SERVO_PIN 4

const int MIN_DISTANCE = 5;
const int MAX_DISTANCE = 10;

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN,OUTPUT); pinMode(ECHO_PIN,INPUT);
  servo.attach(SERVO_PIN);
}

void loop() {
  // clear triger pin then set to HIGH state for 10 ms
  digitalWrite(TRIG_PIN,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN,LOW);

  // calculate distance1
  int duration; int distance;
  duration = pulseIn(ECHO_PIN,HIGH);
  distance = duration * 0.034 / 2;

  if (distance <= MAX_DISTANCE) {
    servo.write(180);
  } else {
    servo.write(90);
  }
  delay(1000);
}
