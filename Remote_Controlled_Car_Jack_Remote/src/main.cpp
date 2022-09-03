////////////////////////////////////////////////////////////////////////////////////////////////////
//*******FILE NAME:   main.cpp**********************************************************************
//*******AUTHOR:      Chima Okwara (AlphaChi)*******************************************************
//*******DESC:        Code for remote control of remote-controlled   *******************************
//                    car jack.*********************************************************************
//*******CREATED:     Friday, 26 August 2022 02:21**************************************************
//*******MODIFIED:    Friday, 26 August 2022 02:21**************************************************
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Arduino.h>
#include <pincontrol.hpp>
// #include <sensors.hpp>
#include <RH_ASK.h>
#include <SPI.h>
#define DELAY1 500
#define DELAY2 1000
#define DELAY3 100


void setup();
void loop();


inputPin upbtn {3}, downbtn {2};        //Buttons to move the car jack up and down
outputPin led {13};                       //To indicate the state of the motor
RH_ASK tx;                                //The transmitter module, connected to the MISO pin.
char msg[3] { };



void setup()
{
  tx.init();

  upbtn.write(1);
  downbtn.write(1);

  //Blink the led five times:
  for(int i = 0; i < 5; )
  {
    led.toggle();
    if (led.read() == 1)
      ++i;
    delay(500);
  }
  led.write(ON);
}

void loop()
{
  while((upbtn.read() == 0) && (downbtn.read() == 1))
  {
      strcpy(msg, "up");
      tx.send((uint8_t *)msg, strlen(msg));
      tx.waitPacketSent();
      led.toggle();
      delay(DELAY1);
      break;
  }

  while((downbtn.read() == 0) && (upbtn.read() == 1))
  {
      strcpy(msg, "dn");
      tx.send((uint8_t *)msg, strlen(msg));
      tx.waitPacketSent();
      led.toggle();
      delay(DELAY1);
      break;
  }

  while((upbtn.read() == 1) && (downbtn.read() == 1))
  {
    strcpy(msg, "np");
    tx.send((uint8_t *)msg, strlen(msg));
    tx.waitPacketSent();
    led.write(ON);
    break;
  }

  while((upbtn.read() == 0) && (downbtn.read() == 0))
  {
    strcpy(msg, "bp");
    tx.send((uint8_t *)msg, strlen(msg));
    tx.waitPacketSent();
    led.write(OFF);
    break;
  }
}
