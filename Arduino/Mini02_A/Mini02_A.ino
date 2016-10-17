#include <PID_v1.h>  //PID loop from http://playground.arduino.cc/Code/PIDLibrary

char iam = 'a';

int offSet1 = 28;
int offSet2 = 25;

double Pk1 = 20;  
double Ik1 = 0;
double Dk1 = 0.1;
double Setpoint1, Input1, Output1, Output1a;    

PID PID1(&Input1, &Output1, &Setpoint1, Pk1, Ik1 , Dk1, DIRECT);   

double Pk2 = 20; 
double Ik2 = 0;
double Dk2 = 0.1;
double Setpoint2, Input2, Output2, Output2a;   

PID PID2(&Input2, &Output2, &Setpoint2, Pk2, Ik2 , Dk2, DIRECT);   

unsigned long previousMillis = 0;
const long interval = 10;
unsigned long lastDataTime;

int read1;
int read2;
int read3;
int read4;
int read5;
int read6;
int read7;
int read8;

int joint1 = 0;
int joint2 = 0;
int actualJoint1;
int actualJoint2;

int ident;
int ident2;

void setup() {

Serial.begin(115200);     // opens serial port

PID1.SetMode(AUTOMATIC);              // PID Setup
PID1.SetOutputLimits(-255, 255);
PID1.SetSampleTime(10);

PID2.SetMode(AUTOMATIC);              // PID Setup
PID2.SetOutputLimits(-255, 255);
PID2.SetSampleTime(10);
}

void loop() {

     unsigned long currentMillis = millis();
     if (currentMillis - previousMillis >= interval) {  //start timed event
        previousMillis = currentMillis;

              if (Serial.available()>=24) {  // check for enough serial data
              ident = Serial.read();
              read1 = Serial.parseInt();  // a
              read2 = Serial.parseInt();  // a
              read3 = Serial.parseInt();  // b
              read4 = Serial.parseInt();  // b
              read5 = Serial.parseInt();  // c
              read6 = Serial.parseInt();  // c
              read7 = Serial.parseInt();  // d
              read8 = Serial.parseInt();  // d
              ident2 = Serial.read();
              
              if (ident == iam && ident2 == iam) {  // check data is for this device and in the right order
                  lastDataTime = millis(); // bookmark the time for safties                 
                  joint1 = read1;   // if the data is right update to main loop variables
                  joint2 = read2;  
              } 
      }

      actualJoint1 = analogRead(A0);
      actualJoint2 = analogRead(A1);

      actualJoint1 = map(actualJoint1,0,1023,-255,255);
      actualJoint2 = map(actualJoint2,0,1023,-255,255);

/*
      Serial.print(" demand1: ");
      Serial.print(joint1);
      Serial.print(" actual1: ");
      Serial.print(actualJoint1);
      Serial.print(" Output1: ");
      Serial.print(Output1);

      Serial.print(" demand2: ");
      Serial.print(joint2);
      Serial.print(" actual2: ");
      Serial.print(actualJoint2);
      Serial.print(" Output2: ");
      Serial.println(Output2);
*/

      Input1 = actualJoint1+offSet1;
      Input2 = actualJoint2+offSet2;
      Setpoint1 = constrain(joint1,-30,30);
      Setpoint2 = constrain(joint2,-30,30);

      PID1.Compute();
      PID2.Compute();


      // ************* output 1  ****************

      if (Output1 <= 5)                               // decide which way to turn based on deadSpot variable
            {
            Output1a = abs(Output1);
            analogWrite(3, Output1a);                 // set PWM pins 
            analogWrite(5, 0);
            }
      else if (Output1 > 5)                          // decide which way to turn the wheels based on deadSpot variable
            { 
            Output1a = abs(Output1);
            analogWrite(5, Output1a);  
            analogWrite(3, 0);
            }
      else {
            analogWrite(5,0);  
            analogWrite(3, 0);
      }

      // ************* output 2  ****************

      if (Output2 <= 5)                               // decide which way to turn based on deadSpot variable
            {
            Output2a = abs(Output2);
            analogWrite(9, Output2a);                 // set PWM pins 
            analogWrite(10, 0);
            }
      else if (Output2 > 5)                          // decide which way to turn the wheels based on deadSpot variable
            { 
            Output2a = abs(Output2);
            analogWrite(10, Output2a);  
            analogWrite(9, 0);
            }
      else {
            analogWrite(9,0);  
            analogWrite(10, 0);
      }

  
     } // end of timed event

}  // end of main loop
