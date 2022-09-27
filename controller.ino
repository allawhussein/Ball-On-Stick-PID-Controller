#include <Servo.h>

Servo servo;
int trig = 3;
int echo = 2;

int servo_pin = 9;

float p_gain, d_gain;
float distance;
float prev_dist;

float dist()
{
  long lap;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  lap = pulseIn(echo, HIGH);

  return (34.3 * lap /2000);
}

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(9, OUTPUT);

  servo.attach(9);
  p_gain = 2;
  d_gain = 0;
  prev_dist = 15;
}

void loop() {
  distance = dist() - 15;
  
  servo.write(50 + p_gain * distance + d_gain * (distance - prev_dist));
  Serial.println(distance);

  prev_dist = distance;
}
