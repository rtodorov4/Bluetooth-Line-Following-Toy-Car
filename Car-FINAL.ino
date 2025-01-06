//Bluetooth car with line following sensors - Written by Ryan T. 2023.6.1

//declare constants for line following sensors
const int Rightsensor = 2;
const int Leftsensor = 4;

//define motor pins
const int LMotor_pin1 = 3;
const int LMotor_pin2 = 11;
const int RMotor_pin1 = 9;
const int RMotor_pin2 = 10;

//define ideal turning speed/motor voltage for line following
const int turnBack = 255;
const int turnForward = 100;

//define constants for LEDpins
const int red1 = 13;
const int green1 = 12;
const int blue1 = 8;
const int red2 = 6;
const int green2 = 5;
const int blue2 = 18;

//define booleans for right blinking, left blinking, timer/blink, brake, headlight, and mdoeSwitch
bool blinkr = false;
bool blinkl = false;
bool blink = false;
bool brake = false;
bool headlight = false;
bool backlight = false;
bool modeSwitch = false;

//define variables for blink timer and speed/motor voltage
int timer = 0;
int drive = 155;

//define constants for the receive and transfer data pins
const int rxPin = 0;
const int txPin = 1;

void setup() {
  pinMode(rxPin, INPUT); //set recieve pin as INPUT
  pinMode(txPin, OUTPUT); //set transmit pin as OUTPUT
  Serial.begin(9600); //set serial baud rate to 9600
  
  // set motor pins as OUTPUTS
  pinMode(LMotor_pin1, OUTPUT);
  pinMode(LMotor_pin2, OUTPUT);
  pinMode(RMotor_pin1, OUTPUT);
  pinMode(RMotor_pin2, OUTPUT);

  //set sensor pins as INPUT
  pinMode(Rightsensor, INPUT);
  pinMode(Leftsensor, INPUT);

  //set LEDpins output
  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(blue1, OUTPUT);
  pinMode(blue2, OUTPUT);
}

void loop() {
  while(Serial.available() > 0) { //While there is data to be read
    int data = Serial.read(); //stores data in variable "data"
    if (data == 49) { //if data recieved is 49/1 (FORWARD)
      //turn off all other LEDmodes
      blinkl = false;
      blinkr = false;
      brake = false;
      backlight = false;
      //turn on headlights
      headlight = true;
      
      //Left motor forward
      analogWrite(LMotor_pin1, drive);
      analogWrite(LMotor_pin2, 0);
      //Right motor forward
      analogWrite(RMotor_pin1, drive);
      analogWrite(RMotor_pin2, 0);
    } else if (data == 48) { //if data recieved is 48/0 (STOP)
      //turn off all other LEDmodes
      blinkl = false;
      blinkr = false;
      headlight = false;
      backlight = false;
      //BRAKE LIGHT
      brake = true;
      
      //Left motor stop
      analogWrite(LMotor_pin1, 0);
      analogWrite(LMotor_pin2, 0);
      //Right motor stop
      analogWrite(RMotor_pin1, 0);
      analogWrite(RMotor_pin2, 0);
    } 
    else if (data == 50) { //if data recieved is 50/2(DRIVE BACKWARDS)
      //turn off all other LEDmodes
      blinkl = false;
      blinkr = false;
      brake = false;
      headlight = false;
      //turn on backlights
      backlight = true;
      
      //Left motor back
      analogWrite(LMotor_pin1, 0);
      analogWrite(LMotor_pin2, drive);
      //Right motor back
      analogWrite(RMotor_pin1, 0);
      analogWrite(RMotor_pin2, drive);
    } 
    else if (data == 51) { //if data recieved is 51/3 (TURN LEFT)
      //turn off all other LEDmodes
      blinkr = false;
      brake = false;
      headlight = false;
      backlight = false;
      //turn on left blinker
      blinkl = true;
      
      //Left motor back
      analogWrite(LMotor_pin1, 0);
      analogWrite(LMotor_pin2, drive);
      //Right motor forward
      analogWrite(RMotor_pin1, drive);
      analogWrite(RMotor_pin2, 0);
    } 
    else if (data == 52) { //if data recieved is 52/4 (TURN RIGHT)
      //turn off all other LEDmodes
      blinkl = false;
      brake = false;
      headlight = false;
      backlight = false;
      //turn on right blinker
      blinkr = true;
      
      //Left motor forward
      analogWrite(LMotor_pin1, drive);
      analogWrite(LMotor_pin2, 0);
      //Right motor back
      analogWrite(RMotor_pin1, 0);
      analogWrite(RMotor_pin2, drive);
    }

    if (data == 53 && drive < 255) {//if data recieved is 53/5 (SPEED UP) and the drive speed isn't already at 255
      drive += 10; //increase drive speed/motor voltage
    }
    if (data == 54 && drive > 115) {//if data recieved is 54/6 (SLOW DOWN) and the drive speed isn't already at 115 
      drive -= 10; //decrease drive speed/motor voltage
    }

    if (data == 55) { //if data recieved is 55/7 (switch modes, (line following/bluetooth control))
      if (modeSwitch == false){ //if boolean is false
        modeSwitch = true; //set true (line following)
      } else { //if boolean is true
        modeSwitch = false; //set false (bluetooth control)
      }
    }
  }

  if (modeSwitch == true) { //if modeSwitch is true (line following)
    // read sensor values
    bool Left_sensorValue = digitalRead(Leftsensor);
    bool Right_sensorValue = digitalRead(Rightsensor);

    // if Left sensor is black and right is white
    if ((Left_sensorValue == 1) && (Right_sensorValue == 0)){
      blinkl = false;
      brake = false;
      headlight = false;
      backlight = false;

      blinkr = true;
      //Right motor back
      analogWrite(RMotor_pin1, 0);
      analogWrite(RMotor_pin2, turnBack); 
      //Left motor forward
      analogWrite(LMotor_pin1, turnForward);
      analogWrite(LMotor_pin2, 0);
    }
    // if Left sensor is white and right is black
    else if ((Left_sensorValue == 0) && (Right_sensorValue == 1)){
      blinkr = false;
      brake = false;
      headlight = false;
      backlight = false;

      blinkl = true;
      //Left motor back
      analogWrite(LMotor_pin1, 0);
      analogWrite(LMotor_pin2, turnBack);
      //Right motor forward
      analogWrite(RMotor_pin1, turnForward);
      analogWrite(RMotor_pin2, 0);
    }
    // if both sensors are white
    else if ((Left_sensorValue == 0) && (Right_sensorValue == 0)){
        blinkl = false;
        blinkr = false;
        brake = false;
        backlight = false;

        headlight = true;
        //Left motor forward
        analogWrite(LMotor_pin1, drive);
        analogWrite(LMotor_pin2, 0);
        //Right motor stop
        analogWrite(RMotor_pin1, drive);
        analogWrite(RMotor_pin2, 0);
    }
    //if both sensors are black
    else if ((Left_sensorValue == 1) && (Right_sensorValue == 1)){
        blinkl = false;
        blinkr = false;
        headlight = false;
        backlight = false;

        brake = true;
        //Left motor stop
        analogWrite(LMotor_pin1, 0);
        analogWrite(LMotor_pin2, 0);
        //Right motor stop
        analogWrite(RMotor_pin1, 0);
        analogWrite(RMotor_pin2, 0);
    }
  }
  
  if (blink == false && timer == 100) { //if blink is false and timer is 100
    blink = true; //set true
    timer = 0; //set 0
  } else if (blink == true && timer == 100) { //if blink is true and timer is 100
    blink = false; //set false
    timer = 0; //set 0
  }
  timer += 5; //timer increases by 5 every loop
  delay(10); // delay of 10 milliseconds per loop

  if (blink == true) { //if blink is true
    if (blinkr == true) { //if blinkr is true
      digitalWrite(red2, HIGH); //turn on red2 LED
      digitalWrite(green2, HIGH); //turn on green2 LED
      //turn off all else
      digitalWrite(red1, LOW);
      digitalWrite(green1, LOW);
      digitalWrite(blue1, LOW);
      digitalWrite(blue2, LOW);
    } else if (blinkl == true) { // if blinkl is true
      digitalWrite(red1, HIGH); //turn on red1 LED
      digitalWrite(green1, HIGH); //turn on green1 LED
      //turn off all else:
      digitalWrite(red2, LOW);
      digitalWrite(green2, LOW);
      digitalWrite(blue1, LOW);
      digitalWrite(blue2, LOW);
    }
  } else { //if blink is on off cycle:
    //turn off all LEDs
    digitalWrite(red1, LOW);
    digitalWrite(red2, LOW);
    digitalWrite(green1, LOW);
    digitalWrite(green2, LOW);
    digitalWrite(blue1, LOW);
    digitalWrite(blue2, LOW);
  }

  if (headlight == true) {
    //Turn on headlights
    digitalWrite(red1, LOW);
    digitalWrite(red2, LOW);
    digitalWrite(green1, HIGH);
    digitalWrite(green2, HIGH);
    digitalWrite(blue1, HIGH);
    digitalWrite(blue2, HIGH);
  } else if (brake == true) { 
    //turn on brakelights
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
    digitalWrite(green1, LOW);
    digitalWrite(green2, LOW);
    digitalWrite(blue1, LOW);
    digitalWrite(blue2, LOW);
  } else if (backlight == true){
    //turn on back lights
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
    digitalWrite(green1, HIGH);
    digitalWrite(green2, HIGH);
    digitalWrite(blue1, LOW);
    digitalWrite(blue2, LOW);
  }
}
