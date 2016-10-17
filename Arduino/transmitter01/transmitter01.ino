#include <Adafruit_NeoPixel.h>
#define PIN            2
#define NUMPIXELS      1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

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
int state = 0;


char youareZ = 'z';  //identifiers for each slave device

unsigned long previousMillis = 0;
const long interval = 80;

void setup() {

  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(5,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  pinMode(A0, INPUT);

  pixels.begin(); // This initializes the NeoPixel library.


  Serial.begin(115200);

  pair();
}

void pair()

{
    state = 0;
    pixels.setPixelColor(0, pixels.Color(100,0,0));
    pixels.show();
      
   while(state == 0) {
          state = digitalRead(12);  // check to see when BT is paired
          }
          // when it's paired
          pixels.setPixelColor(0, pixels.Color(0,100,0));
          pixels.show();
          delay(1000);  
          pixels.setPixelColor(0, pixels.Color(0,0,100));
          pixels.show();      
}


void loop() {
     unsigned long currentMillis = millis();
     if (currentMillis - previousMillis >= interval) {  // start timed event
        previousMillis = currentMillis;

  state = digitalRead(12);  // check to see when BT is paired
  if (state == 0) {
    pair();
  }
  

  but1 = digitalRead(3);
  but2 = digitalRead(4);
  but3 = digitalRead(5);
  but4 = digitalRead(6);
  but5 = digitalRead(7);
  but6 = digitalRead(8);
  but7 = digitalRead(9);
  but8 = digitalRead(10);
  but9 = digitalRead(11);
  slide1 = analogRead(A0); 

  Serial.print(youareZ);  // send identifier
  Serial.print(" , ");
  Serial.print(but1);
  Serial.print(" , ");
  Serial.print(but2);
  Serial.print(" , ");
  Serial.print(but3);
  Serial.print(" , ");
  Serial.print(but4);
  Serial.print(" , ");
  Serial.print(but5);
  Serial.print(" , ");
  Serial.print(but6);
  Serial.print(" , ");
  Serial.print(but7);
  Serial.print(" , ");
  Serial.print(but8);
  Serial.print(" , ");
  Serial.print(but9);
  Serial.print(" , ");
  Serial.print(slide1);
  Serial.print(youareZ);  // send identifier

     }

}
