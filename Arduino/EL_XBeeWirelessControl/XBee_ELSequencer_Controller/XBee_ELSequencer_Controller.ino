/*******************************************************************
SparkFun XBee EL Sequencer Controller
Ho Yun Bobby Chan @ SparkFun Electronics June 20, 2014
Updated by Toni Klopfenstein @ SparkFun Electronics April, 2015
https://github.com/sparkfun/EL_Sequencer

Description:
This is a basic test of the EL Sequencer with a wireless controller.
The wireless controller consists of an Arduino Uno, XBee Explorer,
XBee Series 1 transceiver, and LED Push Button. The EL Sequencer
uses an EL component, EL inverter, XBee female sockets soldered,
battery, and a XBee Series 1 transceiver. An XBee Series 2
can be used but the throughput of the Series 1 is much higher. To
reduce latency, I recommend using the XBee Series 1. The basic
configuration of the XBee module with point-to-point configuratin is
based on Digi's Example tutorial
=> http://examples.digi.com/get-started/basic-xbee-802-15-4-chat/ .
Page 5 of the tutorial shows you how to broadcast with
point-to-multipoint configuration so that multiple EL Sequencers
can be controlled.

Connect the XBee Explorer to the Arduino:
     GND = GND
     3.3V = 3.3V
     DOUT (i.e. Tx of XBee) = Pin 2 (Rx on Arduino)
     DIN (i.e. Rx of XBee)= Pin 3 (Tx on Arduino)

By pushing the button, a character is sent from a remote microcontroller.
The corresponding EL Sequencer will receive the character and control
the EL component on a channel that is associated with that character.
A LED push button was used but not necessary for this to operate. A
normal momentary push button can be used.

Connect momentary LED tactile push buttons to Arduino:
     C = pin 13, the cathode (+) of the LED
     A = GND, the anode (-) of the LED
     B1 = GND
     B2 = pin 8

Using an Arduino Uno, the XBee transceiver is connected to the
Software Serial pins. By pushing the button, the Arduino will
send one character through the XBee. Logic is used to control
how many characters are sent with the push button. The Arduino
will not send another character until the button is pressed again.

Note: This section of the code can be optimized. As the user is not
pressing down on the button, logic can be added so that the XBee is
not continuously sending serial characters to the receiving
EL Sequencer when idle.

Development environment specifics:
Arduino 1.6.3

This code is beerware; if you see me (or any other SparkFun employee) at the local,
and you've found our code helpful, please buy us a round!
Distributed as-is; no warranty is given.
**************************************************************************/

#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3); //Rx = 2, Tx = 3

//Declare variables and pin definitions

//SEND Button
const int button1Pin = 4; //push button
const int ledPin1 = 13;  //LED on the push button

boolean prev_button1State = false;
boolean current_button1State = false;

char send_CHAR = 'A'; //default send character

//LED Status Indicator
int ledR = 5;//hardware PWM //pin 0 on ATtiny85
int ledG = 6;//hardware PWM //pin 1 on ATtiny85
int ledB = 9; //hardware PWM

int pattern = 0; //pattern

//UP Button
const int button2Pin = 11; //push button

boolean prev_button2State = false;
boolean current_button2State = false;

//DOWN Button
const int button3Pin = 12;
boolean prev_button3State = false;
boolean current_button3State = false;

/*******************Setup Loop***************************/
void setup() {
  // initialize the digital pins as an output for LEDs
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);

  sequenceTest();//visually initialization

  //Declare buttons
  pinMode(button1Pin, INPUT_PULLUP); //use internal pullup resistor
  pinMode (ledPin1, OUTPUT);

  pinMode(button2Pin, INPUT_PULLUP); //use internal pullup resistor
  pinMode(button3Pin, INPUT_PULLUP); //use internal pullup resistor

  //Declare serial connections for debugging
  Serial.begin(9600);
  Serial.println("Arduino started sending bytes via XBee");

  xbee.begin(9600);
  Serial.println("EL Sequencer Controller's XBee Ready to Communicate");
}

/*******************Main Loop***************************/
void loop() {
  int button1State;
  int button2State;
  int button3State;

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);
  /*buttonXstate
   - LOW or 0 means pressed
   - HIGH or 1 means not pressed
   */

  //if button is pressed, it will be pulled low
  if (button1State == LOW) {
    digitalWrite(ledPin1, HIGH); //turn push button LED ON
    current_button1State = true; // button has been pressed once

    if (prev_button1State != current_button1State) //check to see if button is still being pressed
    {
      Serial.println("Button is pressed.");
      xbee.write(send_CHAR);//Tell Sequencer to change to mode
    }
    else {
      //do nothing because finger is still on button
    }
    prev_button1State = current_button1State;
  }

  //button has not been pressed, it will be high again
  else {
    current_button1State = false;
    digitalWrite(ledPin1, LOW); // turn push button LED OFF

    prev_button1State = current_button1State;
  }

  if (button2State == LOW) {
    current_button2State = true; //button has been pressed once

    if (prev_button2State != current_button2State) { //check to see if button is still being pressed
      pattern = pattern + 1; //change LED pattern after button has been pressed
      if (pattern < 0 || pattern > 5) {
        //reset pattern
        pattern = 0;
      }

      /*if(pattern == 3){
       blinkPress = blinkPress+1;
       if(blinkPress<0 || blinkPress>2){
       blinkPress=0;
       }
       switch(blinkPress){
       case 1:
       blinkRate=250;
       break;
       case 2:
       blinkRate=500;
       break;
       default:
       blinkRate=750;
       break;
       }
       }*/

    }
    else { //do nothing because finger is still on button
    }
    prev_button2State = current_button2State;
  }
  //button has not been pressed, it will be high
  else {
    current_button2State = false;
    prev_button2State = current_button2State;
  }

  if (button3State == LOW) {
    current_button3State = true; //button has been pressed once

    if (prev_button3State != current_button3State) { //check to see if button is still being pressed
      pattern = pattern - 1; //change LED pattern after button has been pressed
      if (pattern < 0 || pattern > 5) {
        //reset pattern
        pattern = 5;
      }
    }
    else { //do nothing because finger is still on button
    }
    prev_button3State = current_button3State;
  }
  //button has not been pressed, it will be high
  else {
    current_button3State = false;
    prev_button3State = current_button3State;
  }

  switch (pattern) {
    case 1:
      greenON();
      send_CHAR = 'B';
      break;
    case 2:
      blueON();
      send_CHAR = 'C';
      break;
    case 3:
      allOFF();//blink
      delay(50);
      blueON();
      delay(50);
      send_CHAR = 'D';
      break;
    case 4:
      blueON();
      send_CHAR = 'E';
      break;
    default:
      redON();
      send_CHAR = 'A';
      break;
  }

}//end loop


/*
 ROYGBIV
 a 9V battery is not able to fully power all three LEDs simultaneously...
 MODE
 1.) red              = red[HIGH]
 .) tangerine orange = red[HIGH]+ green[50]
 2.) yellow           = red[HIGH]+ green[HIGH]
 3.) green            =          + green[HIGH]
 4.) clear blue       =          + green[HIGH] + blue[HIGH]
 5.) blue             =                        + blue[HIGH]
 6.) magenta          = red[HIGH]+             + blue[HIGH]
 .) white            = red[HIGH]+ green[HIGH] + blue[HIGH]
 */

void allOFF() {
  analogWrite(ledR, 0);
  analogWrite(ledG, 0);
  analogWrite(ledB, 0);
}

void redON() { //Seq 1
  analogWrite(ledR, 255);
  analogWrite(ledG, 0);
  analogWrite(ledB, 0);
}

void greenON() { //Seq 2
  analogWrite(ledR, 0);
  analogWrite(ledG, 255);
  analogWrite(ledB, 0);
}

void blueON() { //Seq 3
  analogWrite(ledR, 0);
  analogWrite(ledG, 0);
  analogWrite(ledB, 255);
}

void yellowON() {
  analogWrite(ledR, 255);
  analogWrite(ledG, 255);
  analogWrite(ledB, 0);
}



void clearblueON() { //MODE 4
  analogWrite(ledR, 0);
  analogWrite(ledG, 255);
  analogWrite(ledB, 255);
}

void magentaON() {
  analogWrite(ledR, 255);
  analogWrite(ledG, 0);
  analogWrite(ledB, 255);
}

void sequenceTest() {
  redON();
  delay(50);
  allOFF();
  delay(50);

  yellowON();
  delay(50);
  allOFF();
  delay(50);

  greenON();
  delay(50);
  allOFF();
  delay(50);

  clearblueON();
  delay(50);
  allOFF();
  delay(50);

  blueON();
  delay(50);
  allOFF();
  delay(50);

  magentaON();
  delay(50);
  allOFF();
  delay(50);

  //whiteON();
  //delay(50);
  //allOFF();
  //delay(50);

}
