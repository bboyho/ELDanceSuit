/**********************************************************************
XBee_ELSequencerV3.ino
 * SparkFun XBee EL Sequencer Demo Sketch
 * Ho Yun Bobby Chan @ SparkFun Electronics June 20, 2014
 * Updated by Toni Klopfenstein @ SparkFun Electronics April, 2015
 * https://github.com/sparkfun/EL_Sequencer
 *
 * Description:
 * This is a basic test of the EL Sequencer with a wireless controller.
 * The wireless controller consists of an Arduino Uno, XBee Explorer,
 * XBee Series 1 transceiver, and LED Push Button. The EL Sequencer
 * uses an EL component, EL inverter, XBee female sockets soldered,
 * battery, and a XBee Series 1 transceiver.  An XBee Series 2
 * can be used but the throughput of the Series 1 is much higher. To
 * reduce latency, I recommend using the XBee Series 1. The basic
 * configuration of the XBee module with point-to-point configuratin is
 * based on Digi's Example tutorial
 * => https://www.digi.com/blog/xbee/basic-xbee-802-15-4-chat/.
 * Page 5 of the tutorial shows you how to broadcast with
 * point-to-multipoint configuration so that multiple EL Sequencers
 * can be controlled.
 *
 * By pushing the button, a character is sent from a remote microcontroller.
 * The corresponding EL Sequencer will receive the character and control
 * the EL component on a channel that is associated with that character.
 *
 * EL Sequencer uses the hardware UART of the Atmega328 for communication:
 * pin 0 = Rx
 * pin 1 = Tx
 *
 * Note: Make sure to remove the XBee Series 1 on the EL Sequencer when
 * uploading a new sketch file otherwise it will brick the XBee. You can
 * always use the next generation XCTU software to unbrick and recover
 * the transceiver.
 *
 * Development environment specifics:
 * Arduino 1.6.3
 *
 * This code is beerware; if you see me (or any other SparkFun employee) at the local,
 * and you've found our code helpful, please buy us a round!
 * Distributed as-is; no warranty is given.
 *
 ***********************************************************************/

//Declare character 'val'
char val;
char temp_delete;

//LED to check if the LED is initialized.
const int status_LED = 13;

//adding counter to prevent false triggers for a small period of time
int counter = 0;
boolean XBee_sent = false;

/*******************Setup Loop***************************/
void setup() {
  Serial.begin(9600); //Begin Serial communication and debugging
  Serial.println("EL Sequencer's XBee is Ready to Receive Characters");

  val = 'A';// button pressed, controller sending  letter A
  val = 'B';
  val = 'C';
  val = 'D';
  val = 'E';

  //Initialize pins
  pinMode(status_LED, OUTPUT); //Set pin mode as output for status LED
  pinMode(2, OUTPUT); //Set pin mode as output for Channel A
  pinMode(3, OUTPUT); //Set pin mode as output for Channel B
  pinMode(4, OUTPUT); //Set pin mode as output for Channel C
  pinMode(5, OUTPUT); //Set pin mode as output for Channel D
  pinMode(6, OUTPUT); //Set pin mode as output for Channel E
  pinMode(7, OUTPUT); //Set pin mode as output for Channel F
  pinMode(8, OUTPUT); //Set pin mode as output for Channel G
  pinMode(9, OUTPUT); //Set pin mode as output for Channel H

  //Status LED to see if the EL Sequencer is initializing
  for (int i = 0; i < 3; ++i) {
    digitalWrite(status_LED, HIGH);//set Status LED on
    delay(50);
    digitalWrite(status_LED, LOW); //set Status LED off
    delay(50);
  }

  all_ON();

  delay(100); //Wait 1 second
}

/*******************Main Loop***************************/
void loop() {
  if (XBee_sent == false) {

    //Check if XBee is receiving data from other XBee
    if (Serial.available()) {
      val = Serial.read();
      counter = 0;
      XBee_sent = true;
      Serial.print("Character Received = ");
      Serial.println(val);

      //Check to see if character sent is letter A
      if (val == 'A') {
        Seq_0();
      }
      else if (val == 'B') {
        Seq_1();
      }
      else if (val == 'C') {
        Seq_2();
      }
      else if (val == 'D') {
        Seq_3();
      }
      else if (val == 'E') {
        Seq_4();
      }

      //else {
      //rewrote controller code to stop constantly sending Z
      //toggled pins outside of this nested condition statement
      //}
    }//end buffer check
  }//end test for counter

  if (counter >= 10) {
    if (XBee_sent == true) {
      Serial.println("Counter = 10, we are ready to receive characters again");
    }
    XBee_sent = false;
  }

  if (XBee_sent == true) {
    counter = ++counter;//keep adding until reach 10, then we can reset flag and beging receiving again
    Serial.print("Counter = ");
    Serial.println(counter);
    temp_delete = Serial.read();//try to clear false triggers in buffer provided by XBee until counter resets
  }

}//end loop()

//**********MODULAR SEQUENCED FUNCTIONS

void all_ON() {
  //Bobby
  digitalWrite(2, HIGH); //Channel A, hoodie
  digitalWrite(3, HIGH); //Channel B, pants
  //Antuan, Kaden
  digitalWrite(4, HIGH); //Channel C, hoodie
  digitalWrite(5, HIGH); //Channel D, pants
  //Mireku, Talon
  digitalWrite(6, HIGH); //Channel E, hoodie
  digitalWrite(7, HIGH); //Channel F, pants
  //Madi, Henry
  digitalWrite(8, HIGH); //Channel G, hoodie
  digitalWrite(9, HIGH); //Channel H, pants
}


void all_OFF() {
  //Bobby
  digitalWrite(2, LOW); //Channel A, hoodie
  digitalWrite(3, LOW); //Channel B, pants
  //Antuan, Kaden
  digitalWrite(4, LOW); //Channel C, hoodie
  digitalWrite(5, LOW); //Channel D, pants
  //Mireku, Talon
  digitalWrite(6, LOW); //Channel E, hoodie
  digitalWrite(7, LOW); //Channel F, pants
  //Madi, Henry
  digitalWrite(8, LOW); //Channel G, hoodie
  digitalWrite(9, LOW); //Channel H, pants
}

void Seq_0() {
  digitalWrite(status_LED, LOW); //turn ON Status LED
  digitalWrite(2, LOW); //Channel A
  digitalWrite(3, LOW); //Channel B
  delay(500);

  digitalWrite(status_LED, HIGH); //turn on Status LED

  digitalWrite(2, HIGH); //Channel A
  delay(500);
  digitalWrite(3, HIGH); //Channel B
  delay(500);
  digitalWrite(2, LOW); //Channel A
  digitalWrite(3, LOW); //Channel B
  delay(500);
  digitalWrite(2, HIGH); //Channel A
  digitalWrite(3, HIGH); //Channel B

  delay(500);
  digitalWrite(2, LOW); //Channel A
  digitalWrite(3, LOW); //Channel B
  delay(250);
  digitalWrite(2, HIGH); //Channel A
  digitalWrite(3, HIGH); //Channel B

  delay(500);

  digitalWrite(2, LOW); //Channel A
  digitalWrite(3, LOW); //Channel B
  delay(500);
  digitalWrite(2, HIGH); //Channel A
  digitalWrite(3, HIGH); //Channel B

  delay(250);
  digitalWrite(2, LOW); //Channel A
  digitalWrite(3, LOW); //Channel B
  delay(250);
  digitalWrite(2, HIGH); //Channel A
  digitalWrite(3, HIGH); //Channel B
  delay(250);
  digitalWrite(2, LOW); //Channel A
  digitalWrite(3, LOW); //Channel B
  delay(250);
  digitalWrite(2, HIGH); //Channel A
  digitalWrite(3, HIGH); //Channel B
  delay(250);
  digitalWrite(2, LOW); //Channel A
  digitalWrite(3, LOW); //Channel B
  delay(250);
  digitalWrite(2, HIGH); //Channel A
  digitalWrite(3, HIGH); //Channel B
  delay(250);
  digitalWrite(2, LOW); //Channel A
  digitalWrite(3, LOW); //Channel B
  delay(250);
  digitalWrite(2, HIGH); //Channel A
  digitalWrite(3, HIGH); //Channel B

  all_ON();
}

void Seq_1() {

  for (int i = 0; i < 8; ++i) {
    //Bobby
    digitalWrite(2, HIGH); //Channel A, hoodie
    digitalWrite(3, LOW); //Channel B, pants
    //Antuan, Kaden
    digitalWrite(4, HIGH); //Channel C, hoodie
    digitalWrite(5, LOW); //Channel D, pants
    //Mireku, Talon
    digitalWrite(6, LOW); //Channel E, hoodie
    digitalWrite(7, HIGH); //Channel F, pants
    //Madi, Henry
    digitalWrite(8, LOW); //Channel G, hoodie
    digitalWrite(9, HIGH); //Channel H, pants
    delay(250);

    //Bobby
    digitalWrite(2, LOW); //Channel A, hoodie
    digitalWrite(3, HIGH); //Channel B, pants
    //Antuan, Kaden
    digitalWrite(4, LOW); //Channel C, hoodie
    digitalWrite(5, HIGH); //Channel D, pants
    //Mireku, Talon
    digitalWrite(6, HIGH); //Channel E, hoodie
    digitalWrite(7, LOW); //Channel F, pants
    //Madi, Henry
    digitalWrite(8, HIGH); //Channel G, hoodie
    digitalWrite(9, LOW); //Channel H, pants
    delay(250);
  }

  all_ON();
  delay(750);
  all_OFF();
  delay(100);
  all_ON();

}

void Seq_2() {
  all_ON();
}

void Seq_3() {

  all_OFF();
  delay(100);
  //Madi, Henry
  digitalWrite(8, HIGH); //Channel G, hoodie
  digitalWrite(9, LOW); //Channel H, pants
  delay(100);
  //Antuan, Kaden
  digitalWrite(4, HIGH); //Channel C, hoodie
  digitalWrite(5, LOW); //Channel D, pants
  delay(100);
  //Bobby
  digitalWrite(2, HIGH); //Channel A, hoodie
  digitalWrite(3, LOW); //Channel B, pants

  //Mireku, Talon
  digitalWrite(6, HIGH); //Channel E, hoodie
  digitalWrite(7, LOW); //Channel F, pants
  delay(100);

  //Madi, Henry
  digitalWrite(8, HIGH); //Channel G, hoodie
  digitalWrite(9, HIGH); //Channel H, pants
  delay(100);
  //Antuan, Kaden
  digitalWrite(4, HIGH); //Channel C, hoodie
  digitalWrite(5, HIGH); //Channel D, pants
  delay(100);
  //Bobby
  digitalWrite(2, HIGH); //Channel A, hoodie
  digitalWrite(3, HIGH); //Channel B, pants

  //Mireku, Talon
  digitalWrite(6, HIGH); //Channel E, hoodie
  digitalWrite(7, HIGH); //Channel F, pants
  delay(100);

}

void Seq_4() {
  all_ON();
}
