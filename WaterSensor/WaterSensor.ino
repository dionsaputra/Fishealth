#include <L298N.h>


const int EN_A = 0;
const int IN_1 = 7;
const int IN_2 = 6;
const int IN_3 = 5;
const int IN_4 = 4;
const int EN_B = 1;

L298N driver(EN_A,IN_1,IN_2,IN_3,IN_4,EN_B);

//L293D
//Motor A
const int motorPin1  = 3;  // Pin 14 of L293
const int motorPin2  = 4;  // Pin 10 of L293

//This will run only one time.
void setup(){
}


void loop(){
  //This code  will turn Motor A clockwise for 2 sec.
  driver.forward(1000,150);  
}
