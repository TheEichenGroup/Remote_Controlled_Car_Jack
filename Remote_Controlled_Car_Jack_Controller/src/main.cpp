////////////////////////////////////////////////////////////////////////////////////////////////////
//*******FILE NAME:   main.cpp**********************************************************************
//*******AUTHOR:      Chima Okwara (AlphaChi)*******************************************************
//*******DESC:        Code for jack controller of remote-controlled   ******************************
//                    car jack.*********************************************************************
//*******LICENCE:     Academic Free License v2.1****************************************************
//*******CREATED:     Friday, 26 August 2022 02:21**************************************************
//*******MODIFIED:    Sunday, 28 August 2022 08:10**************************************************
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <pincontrol.hpp>

void setup();
void loop();

outputPin buzzer {8}, sw1 {7}, sw2 {6}, sw3 {4}, sw4 {5};
RH_ASK rx;

uint8_t buffer [12],
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
  rx.recv(buffer, &buflen);

  while(strcmp((char*) buffer, "up"))
  {
    sw1.write(1);
    sw2.write(0);
    sw3.write(0);
    sw4.write(1);
    buzzer.toggle();
    delay(250);
    break;
  }

  while(strcmp((char*) buffer, "dn"))
  {
    sw1.write(0);
    sw2.write(1);
    sw3.write(1);
    sw4.write(0);
    buzzer.toggle();
    delay(250);
    break;
  }

  while(strcmp((char*) buffer, "bp"))
  {
    buzzer.write(1);
    delay(300);
    buzzer.write(0);
    delay(200);
    break;
  }

  while(strcmp((char*) buffer, "np"))
  {
    buzzer.write(0);
    delay(300);
    buzzer.write(1);
    delay(200);
    break;
  }
}
