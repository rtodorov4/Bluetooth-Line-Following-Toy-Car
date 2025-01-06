const int Rightsensor = 2;
const int Leftsensor = 4;
const int LMotor_pin1 = 3;
const int LMotor_pin2 = 11;
const int RMotor_pin1 = 9;
const int RMotor_pin2 = 10;
const int drive = 120;
const int turnBack = 255;
const int turnForward = 100;

void setup() {
  // set motor pins as OUTPUTS
  pinMode(LMotor_pin1, OUTPUT);
  pinMode(LMotor_pin2, OUTPUT);
  pinMode(RMotor_pin1, OUTPUT);
  pinMode(RMotor_pin2, OUTPUT);

  // set the QTI sensor pins as INPUTS:
  pinMode(Leftsensor, INPUT);
  pinMode(Rightsensor, INPUT);
}
void loop() {
  // read sensor values
  bool Left_sensorValue = digitalRead(Leftsensor);
  bool Right_sensorValue = digitalRead(Rightsensor);
  // if Left sensor is black and right is white
  if ((Left_sensorValue == 1) && (Right_sensorValue == 0)){
    //Right motor back
    analogWrite(RMotor_pin1, 0);
    analogWrite(RMotor_pin2, turnBack); 
    //Left motor forward
    analogWrite(LMotor_pin1, turnForward);
    analogWrite(LMotor_pin2, 0);
  }
 // if Left sensor is white and right is black
 else if ((Left_sensorValue == 0) && (Right_sensorValue == 1)){
    //Left motor back
    analogWrite(LMotor_pin1, 0);
    analogWrite(LMotor_pin2, turnBack);
    //Right motor forward
    analogWrite(RMotor_pin1, turnForward);
    analogWrite(RMotor_pin2, 0);
 }
 // if both sensors are white
 else if ((Left_sensorValue == 0) && (Right_sensorValue == 0)){
    //Left motor forward
    analogWrite(LMotor_pin1, drive);
    analogWrite(LMotor_pin2, 0);
    //Right motor stop
    analogWrite(RMotor_pin1, drive);
    analogWrite(RMotor_pin2, 0);
 }
 //if both sensors are black and it's not making a turn
 else if ((Left_sensorValue == 1) && (Right_sensorValue == 1) && (turn == false)){
    //Left motor stop
    analogWrite(LMotor_pin1, 0);
    analogWrite(LMotor_pin2, 0);
    //Right motor stop
    analogWrite(RMotor_pin1, 0);
    analogWrite(RMotor_pin2, 0);
  }
}