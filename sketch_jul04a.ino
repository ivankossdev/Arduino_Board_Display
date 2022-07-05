#include <TimerOne.h>

int latchPin = 4;
int clockPin = 7;
int dataPin = 8;
unsigned char numberChar[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0X80, 0X90};
unsigned char segment[]   = {0xF1, 0xF2, 0xF4, 0xF8};
unsigned char number[]  =  {0, 0, 0, 0};
int i = 0;
bool flag_up = false;

void setup ()
{
  Timer1.initialize(50000);
  Timer1.attachInterrupt(setFlag);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void sevenIndicator()
{
  for (char i = 0; i <= 3; i++)
  {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, numberChar[number[i]]);
    shiftOut(dataPin, clockPin, MSBFIRST, segment[i] );
    digitalWrite(latchPin, HIGH);
  }
}

void setFlag(){
  flag_up = true;
}

void counter(){
  if(flag_up){
    number[0] = i / 1000;
    number[1] = i % 1000 / 100;
    number[2] = i % 100 / 10;
    number[3] = i % 10;
    if(i >= 9999){
      i = 0;
    }
    i++;
  }
  flag_up = false;
}

void loop()
{
  counter();
  sevenIndicator();
}
