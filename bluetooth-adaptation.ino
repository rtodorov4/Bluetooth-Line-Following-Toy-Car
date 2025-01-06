#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);
#define LED 3

int state;

void setup() {
  pinMode(LED, OUTPUT);
  // pinMode(off, OUTPUT);
  Serial.begin(9600);
  Serial.println()
  BT.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    state = BT.read();
  }
  if (state == '0') {
    digitalWrite(LED, HIGH);
    BT.println("LED: ON");
  } else if (state == '1') {
    digitalWrite(LED, LOW);
    BT.println("LED: OFF");
  }
}