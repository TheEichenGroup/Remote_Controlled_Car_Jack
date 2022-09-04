////////////////////////////////////////////////////////////////////////////////////////////////////
//*******FILE NAME:   main.cpp**********************************************************************
//*******AUTHOR:      Chima Okwara (AlphaChi)*******************************************************
//*******DESC:        Code for jack controller of remote-controlled   ******************************
//                    car jack.*********************************************************************
//*******LICENCE:     Academic Free License v2.1****************************************************
//*******CREATED:     Friday, 26 August 2022 02:21**************************************************
//*******MODIFIED:    Sunday, 4 September 2022 13:23************************************************
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <pincontrol.hpp>

void setup();
void loop();

outputPin buzzer {8}, sw1 {7}, sw2 {6}, sw3 {4}, sw4 {5};
RH_ASK rx;

char buffer [3] = { };
uint8_t temp [3] = { },
        buflen = sizeof(buffer);

void setup()
{
  rx.init();
  //Beep buzzer 5 times.
  for (int i =0; i>5; )
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
  rx.recv(temp, &buflen);
  strcpy(buffer, (char*)temp);

  if(strcmp((char*) buffer, "up"))
  {
    sw1.write(1);
    sw2.write(0);
    sw3.write(0);
    sw4.write(1);
    buzzer.toggle();
    delay(250);
  }

  if(strcmp((char*) buffer, "dn"))
  {
    sw1.write(0);
    sw2.write(1);
    sw3.write(1);
    sw4.write(0);
    buzzer.toggle();
    delay(250);
  }

  if(strcmp((char*) buffer, "bp"))
  {
    buzzer.write(1);
    delay(300);
    buzzer.write(0);
    delay(200);
  }

  if(strcmp((char*) buffer, "np"))
  {
    buzzer.write(0);
    delay(300);
    buzzer.write(1);
    delay(200);
  }
}
