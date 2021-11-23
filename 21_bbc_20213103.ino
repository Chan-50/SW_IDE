#include <Servo.h>

// Arduino pin assignment
#define PIN_SERVO 10

// configurable parameters
#define _DUTY_MIN 1320 // 레일 판 아래로
#define _DUTY_NEU 1570 // 레일 판 중립
#define _DUTY_MAX 1800 // 레일 판 위로

// Arduino pin assignment
#define PIN_IR A0
#define PIN_LED 9

//#define _DIST_ALPHA 0.3
//
//#define _SERVO_SPEED 2000
//#define INTERVAL 20

int a, b; // unit: mm

float alpha;

Servo myservo;

void setup() {
// initialize GPIO pins
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED, 1);
  
// initialize serial port
  Serial.begin(57600);

  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);

  a = 66;   // a : 최소 거리 
  b = 382;  // b : 최대 거리

  //EMA 필터의 a 값
//  alpha = _DIST_ALPHA;

  //서보 속도 조절
//  duty_chg_per_interval = (_DUTY_MAX - _DUTY_MIN) * (_SERVO_SPEED / 180.0) * (INTERVAL / 1000.0);
}

float ir_distance(void){ // return value unit: mm
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  return val;
}

void loop() {
//  while(1){
//    myservo.writeMicroseconds(_DUTY_NEU);
//  }
  float raw_dist = ir_distance();
  float dist_cali = 100 + 300.0 / (b - a) * (raw_dist - a);
//  float dist_ema = alpha * dist_cali + (1 - alpha) * dist_ema;
  Serial.print("min:0,max:500,dist:");
  Serial.print(raw_dist);
  Serial.print(",dist_cali:");
  Serial.println(dist_cali);
  if(dist_cali > 230){
    myservo.writeMicroseconds(_DUTY_MIN);
  }
  else myservo.writeMicroseconds(_DUTY_MAX);
  delay(20);
}
