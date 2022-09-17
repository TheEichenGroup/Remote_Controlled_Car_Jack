////////////////////////////////////////////////////////////////////////////////////////////////////
//*******FILE NAME:   main.cpp**********************************************************************
//*******AUTHOR:      Chima Okwara (AlphaChi)*******************************************************
//*******DESC:        Code for jack controller of remote-controlled   ******************************
//                    car jack.*********************************************************************
//*******LICENCE:     Academic Free License v2.1****************************************************
//*******CREATED:     Friday, 26 August 2022 02:21**************************************************
//*******MODIFIED:    Friday, 16 September 2022 13:43***********************************************
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <pincontrol.hpp>

void setup();
void loop();
enum btnPress { None = 0, Up = 1, Down= 2 };
btnPress &checkPress(inputPin*, inputPin*);

outputPin buzzer {8}, sw1 {7}, sw2 {6}, sw3 {4}, sw4 {5};
inputPin upBtn {2} /*White Wire*/, dnBtn{3} /*Red Wire*/;
RH_ASK rx;
btnPress btnState { };

char buffer [3] = { };
uint8_t temp [3] = { },
        buflen = sizeof(buffer);

void setup()
{
  upBtn.write(1);
  dnBtn.write(1);
  rx.init();

  //Beep buzzer 5 times.
  for (int i = 0; i< 5; )
  {
    buzzer.toggle();
    if (buzzer.read())
      ++i;
    delay(500);
  }
  buzzer.write(OFF);
}

void loop()
{
  sw1.write(1);
  sw2.write(1);
  sw3.write(1);
  sw4.write(1);
  rx.recv(temp, &buflen);
  strcpy(buffer, (char*)temp);
  btnState = checkPress(&upBtn, &dnBtn);

  while(!strcmp(buffer, "up") || btnState == Up)
  {
    sw1.write(0);
    sw2.write(1);
    sw3.write(1);
    sw4.write(0);
    buzzer.toggle();
    delay(200);
    rx.recv(temp, &buflen);
    strcpy(buffer, (char*)temp);
    btnState = checkPress(&upBtn, &dnBtn);
  }

  while(!strcmp(buffer, "dn") || btnState == Down)
  {
    sw1.write(1);
    sw2.write(0);
    sw3.write(0);
    sw4.write(1);
    buzzer.toggle();
    delay(200);
    rx.recv(temp, &buflen);
    strcpy(buffer, (char*)temp);
    btnState = checkPress(&upBtn, &dnBtn);
  }

  if(!strcmp(buffer, "bp") || btnState == None)
  {
    buzzer.write(0);
  }

  if(!strcmp(buffer, "np") || btnState == None)
  {
    buzzer.write(0);
  }

  delay(100);
}


btnPress &checkPress(inputPin *a, inputPin *b)
{
  static btnPress temp = None;
  if(a->read() == 0 || b->read() == 0)
    temp = ((a->read()==0)?Up:Down);
  else
    temp = None;
  return temp;
}
