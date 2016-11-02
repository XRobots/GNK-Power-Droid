#include <PID_v1.h>  //PID loop from http://playground.arduino.cc/Code/PIDLibrary 

// front - back servo

double Pk1 = 40;  //speed it gets there
double Ik1 = 0;
double Dk1 = 0.25;

double Setpoint1, Input1, Output1, Output1a;    // PID variables - front/back servo
PID PID1(&Input1, &Output1, &Setpoint1, Pk1, Ik1 , Dk1, DIRECT);    // PID Setup - front/back servo

// front - back stability

double Pk2 = 30;  //speed it gets there
double Ik2 = 0;
double Dk2 = 0;

double Setpoint2, Input2, Output2, Output2a;    // PID variables - front/back servo
PID PID2(&Input2, &Output2, &Setpoint2, Pk2, Ik2 , Dk2, DIRECT);    // PID Setup - front/back servo

// side - side stability *left ankle*

double PkSide1 = 4;  //positon it goes to
double IkSide1 = 0;
double DkSide1 = 0;

double SetpointSide1, InputSide1, OutputSide1;    // PID variables - front/back servo
PID PIDSide1(&InputSide1, &OutputSide1, &SetpointSide1, PkSide1, IkSide1, DkSide1, DIRECT);    // PID Setup - left ankle

// side - side stability *left hip*

double PkSide2 = 5;  //positon it goes to
double IkSide2 = 0;
double DkSide2 = 0;

double SetpointSide2, InputSide2, OutputSide2;    // PID variables - front/back servo
PID PIDSide2(&InputSide2, &OutputSide2, &SetpointSide2, PkSide2, IkSide2, DkSide2, DIRECT);    // PID Setup - left hip

// side - side stability *right ankle*

double PkSide3 = 4;  //positon it goes to
double IkSide3 = 0;
double DkSide3 = 0;

double SetpointSide3, InputSide3, OutputSide3;    // PID variables - front/back servo
PID PIDSide3(&InputSide3, &OutputSide3, &SetpointSide3, PkSide3, IkSide3, DkSide3, DIRECT);    // PID Setup - right ankle

// side - side stability *right hip*

double PkSide4 = 5;  //positon it goes to
double IkSide4 = 0;
double DkSide4 = 0;

double SetpointSide4, InputSide4, OutputSide4;    // PID variables - front/back servo
PID PIDSide4(&InputSide4, &OutputSide4, &SetpointSide4, PkSide4, IkSide4 , DkSide4, DIRECT);    // PID Setup - right hip


char iam = 'z';    // unique name - remote
char iam2 = 'y';   // unique name - IMU
char ident;        // start data
char ident2;       // end data
char ident3;       // start data
char ident4;       // end data

char youareA = 'a';
char youareB = 'b';
char youareC = 'c';
char youareD = 'd';

unsigned long previousLeftMillis = 0; 
long leftTime = 350;
int leftFlag = 0;

unsigned long previousRightMillis = 0; 
long rightTime = 350;
int rightFlag = 0;

unsigned long previousStepTime;
long stepTime = 360;
int stepFlag = 0;

int read1 = 0;
int read2 = 0;
int read3 = 0;
int read4 = 0;
int read5 = 0;
int read6 = 0;
int read7 = 0;
int read8 = 0;
int read9 = 0;
int read10 = 0;
int read11 = 0;
int read12 = 0;
int read13 = 0;
int read14 = 0;
int read15 = 0;

int but1 = 1;
int but2 = 1;
int but3 = 1;
int but4 = 1;
int but5 = 1;
int but6 = 1;
int but7 = 1;
int but8 = 1;
int but9 = 1;
int slide1 = 512;
int pot1 = 512;
int pot2 = 512;
int pot3 = 512;
int pot4 = 512;
int pot5 = 512;

double pot1a;
double pot2a;
double pot3a;
double pot4a;
double pot5a;

double slide2 = 0;
double slide3;
int count = 0;

float imuRead1;
float imuRead2;
float imuX;
float imuY;

int a1 = 0;
int a2 = 0;
int b1 = 0;
int b2 = 0;
int c1 = 0;
int c2 = 0;
int d1 = 0;
int d2 = 0;

float trimpot = 0;

int waist = 0;

unsigned long previousMillis = 0;
const long interval = 20;
unsigned long lastDataTime;
unsigned long lastDataTime2;

void setup() {
        Serial1.begin(115200);     // opens serial port
        Serial2.begin(115200);     // opens serial port
        Serial3.begin(115200);     // opens serial port
        Serial.begin(115200);     // openes serial port

        pinMode(13,OUTPUT);       // error light
        pinMode(23,OUTPUT);       // error light
        digitalWrite(13,LOW);     //turn off
        digitalWrite(23,LOW);     //turn off

        PID1.SetMode(AUTOMATIC);              // PID Setup - front/back stability
        PID1.SetOutputLimits(-255, 255);
        PID1.SetSampleTime(20);

        PID2.SetMode(AUTOMATIC);              // PID Setup - front/back stability
        PID2.SetOutputLimits(-255, 255);
        PID2.SetSampleTime(20);

        PIDSide1.SetMode(AUTOMATIC);              // PID Setup - *left ankle*
        PIDSide1.SetOutputLimits(-255, 255);
        PIDSide1.SetSampleTime(20);

        PIDSide2.SetMode(AUTOMATIC);              // PID Setup - *left hip*
        PIDSide2.SetOutputLimits(-255, 255);
        PIDSide2.SetSampleTime(20);

        PIDSide3.SetMode(AUTOMATIC);              // PID Setup - *right ankle*
        PIDSide3.SetOutputLimits(-255, 255);
        PIDSide3.SetSampleTime(20);

        PIDSide4.SetMode(AUTOMATIC);              // PID Setup - *right hip
        PIDSide4.SetOutputLimits(-255, 255);
        PIDSide4.SetSampleTime(20);

        pinMode(A0, INPUT_PULLUP);
        delay(1000);
}

void loop() {

   unsigned long currentMillis = millis();
     if (currentMillis - previousMillis >= interval) {  //start timed event
        previousMillis = currentMillis;

        if (but9 == 0){
          digitalWrite(23, HIGH);   // enable
          //Serial.println ("high");
        }
        else {
          digitalWrite (23, LOW);
        }

        

        if (Serial1.available()>=24) {  // check for enough serial data
                // read the incoming byte:
                ident = Serial1.read();
                read1 = Serial1.parseInt();
                read2 = Serial1.parseInt();
                read3 = Serial1.parseInt();
                read9 = Serial1.parseInt();
                read10 = Serial1.parseInt();
                read11 = Serial1.parseInt();
                read12 = Serial1.parseInt();
                read13 = Serial1.parseInt();
                read14 = Serial1.parseInt();
                read15 = Serial1.parseInt();
                ident2 = Serial1.read();

                /*

                Serial.print(ident);
                Serial.print(" , ");
                Serial.print(read1);
                Serial.print(" , ");
                Serial.print(read2);
                Serial.print(" , ");
                Serial.print(read3);
                Serial.print(" , ");
                Serial.print(read9);
                Serial.print(" , ");
                Serial.print(read10);
                Serial.print(" , ");
                Serial.print(read11);
                Serial.print(" , ");
                Serial.print(read12);
                Serial.print(" , ");
                Serial.print(read13);
                Serial.print(" , ");
                Serial.print(read14);
                Serial.print(" , ");
                Serial.print(read15);
                Serial.print(" , ");
                Serial.println(ident2);

                */                

                
                if (ident == iam && ident2 == iam) {  // check data is for this device and in the right order
                    lastDataTime = millis(); // bookmark the time for safties                 
                    but1 = read1;   // if the data is right update to main loop variables
                    but2 = read2; 
                    but3 = read3;
                    but9 = read9;
                    slide1 = read10; 
                    pot1 = read11; 
                    pot2 = read12; 
                    pot3 = read13; 
                    pot4 = read14; 
                    pot5 = read15;  
                   } 

                   pot1a = (double) pot1;
                   pot2a = (double) pot2;
                   pot3a = (double) pot3;
                   pot4a = (double) pot4;
                   pot5a = (double) pot5;

        }

        if (Serial2.available()>=4) {  // check for enough serial data
          // read the incoming byte:
          ident3 = Serial2.read();
          imuRead1 = Serial2.parseFloat();
          imuRead2 = Serial2.parseFloat();
          ident4 = Serial2.read();
          
          if (ident3 == iam2 && ident4 == iam2) {  // check data is for this device and in the right order
              lastDataTime2 = millis(); // bookmark the time for safties                 
              imuX = imuRead1;   // if the data is right update to main loop variables
              imuY = imuRead2;
              trimpot = analogRead(A1);                           
              imuY = imuY+((pot1a-512)/100);
              //Serial.println(imuY);
          } 
  }
      

      if (millis() - lastDataTime <= 200 && millis() - lastDataTime2 <=200) {  //saftey check - proceed if data is current enough
              // main code goes in here
              digitalWrite(13,LOW);  //  LED off

              // front - back stability

              //Serial.println(imuY);

              waist = analogRead(A0);
              waist = map(waist,0,1023,-255,255);

              slide2 = (double) slide1;
              slide3 = ((slide2/25)-20)*-1;
              
              Input2 = imuX;
              Setpoint2 = slide3;
              PID2.Compute();
              
              Input1 = waist;
              Setpoint1 = map(Output2,255,-255,10,65);              
              PID1.Compute();         

              // Drive front/back stability motor

               if (Output1 < 0)                                      // decide which way to turn the wheels based on deadSpot variable
                    {
                    Output1a = abs(Output1);
                    analogWrite(2, Output1a);                                // set PWM pins 
                    analogWrite(3, 0);
                    }
                 else if (Output1 >= 0)                          // decide which way to turn the wheels based on deadSpot variable
                    { 
                    Output1a = abs(Output1);
                    analogWrite(3, Output1a);  
                    analogWrite(2, 0);
                    } 
                 else
                    {
                    analogWrite(2, 0);  
                    analogWrite(3, 0);
                    }

                 // side - side stability

                 SetpointSide1 = 0-abs(imuY/5) + ((pot2a-512)/100) + (((pot3a-512)*-1)/100);           // left ankle
                 SetpointSide2 = 0-abs(imuY/5);           // left hip
                 SetpointSide3 = 0+abs(imuY/5) - ((pot2a-512)/100) + (((pot3a-512)*-1)/100);           // right ankle
                 SetpointSide4 = 0+abs(imuY/5);           // right hip
                 
                 InputSide1 = imuY;
                 InputSide2 = imuY;
                 InputSide3 = imuY;
                 InputSide4 = imuY;

                 PIDSide1.Compute();
                 PIDSide2.Compute();
                 PIDSide3.Compute();
                 PIDSide4.Compute();

                 a1 = OutputSide1*-1;         // left ankle
                 a2 = OutputSide2*1;            // left hip
                 c1 = OutputSide3*-1;         // right ankle
                 c2 = OutputSide4*1;            // right hip  


                   // dynamic timing

                   leftTime = leftTime+(abs(imuY/8));
                   rightTime = rightTime+(abs(imuY/8));
                   stepTime = stepTime+(abs(imuY/8));


                   // ************ step timer ************

                     if (but1 == 0 && stepFlag == 0) {
                      stepFlag = 1;
                      }

                      if (stepFlag == 1) {
                        leftFlag = 1;
                        stepFlag = 2;
                        previousStepTime = currentMillis; // reset the clock
                      }
                      
                      if (stepFlag == 2 && currentMillis - previousStepTime >= ( stepTime + (abs(pot5a/1000))) ) {
                       rightFlag = 1;
                       stepFlag = 3;
                       previousStepTime = currentMillis; // reset the clock
                      } 
                      
                      if (stepFlag == 3 && currentMillis - previousStepTime >= ( stepTime + (abs(pot5a/1000))) ) {
                       stepFlag = 0;
                       previousStepTime = currentMillis; // reset the clock
                      }                    

                    


                    // ************ left ***************

                    if (but7 == 0) {
                      leftFlag = 1;
                    }
                  
                    if (leftFlag == 1) {
                      b1 = 50;
                      b2 = 50;    
                      leftFlag = 2;
                      previousLeftMillis = currentMillis; // reset the clock
                    }
                  
                    if (leftFlag == 2 && currentMillis - previousLeftMillis >= ( leftTime + (abs(pot5a/1000))) ){
                      b1 = 0 + ((pot5-512)/10) ;
                      b2 = 0 - ((pot5-512)/10) ;
                      leftFlag = 0;
                      previousLeftMillis = currentMillis; // reset the clock
                    }
                  
                    // ************ right ***************

                    if (but8 == 0) {
                      rightFlag = 1;
                    }                 
                  
                    if (rightFlag == 1) {
                      d1 = 50;
                      d2 = 50;
                      rightFlag = 2;
                      previousRightMillis = currentMillis; // reset the clock
                    }
                  
                    if (rightFlag == 2 && currentMillis - previousRightMillis >= ( rightTime + (abs(pot5a/1000))) ) {
                      d1 = 0 + ((pot5-512)/10) ;
                      d2 = 0 - ((pot5-512)/10) ;
                      rightFlag = 0;
                      previousRightMillis = currentMillis; // reset the clock
                    }
                  
                     // send all serial data in one go
                  
                     Serial3.print(youareA);
                     Serial3.print(" , ");
                     Serial3.print(a1);
                     Serial3.print(" , ");
                     Serial3.print(a2);
                     Serial3.print(" , ");
                     Serial3.print(b1);
                     Serial3.print(" , ");
                     Serial3.print(b2);
                     Serial3.print(" , ");
                     Serial3.print(c1);
                     Serial3.print(" , ");
                     Serial3.print(c2);
                     Serial3.print(" , ");
                     Serial3.print(d1);
                     Serial3.print(" , ");
                     Serial3.print(d2);
                     Serial3.print(youareA);
              
              }   // end of main code
              
        else if (millis() - lastDataTime > 200 || millis()-lastDataTime2 > 200) {  // safety check - do whatever because data has stopped
          
              // error state code goes here
                             
              Serial.println("error state");
              digitalWrite(13,HIGH);  //  LED on

      }  // end of error state - emergency stop etc

     }  // end of timed event
     
} //end of main loop
