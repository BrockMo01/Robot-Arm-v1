#include <Arduino.h>
#include <Servo.h>

#define J1  2
#define J2  3
#define J3  4
#define J4  5

Servo joint1;
Servo joint2;
Servo joint3;
Servo joint4;

int curPos1;
int curPos2;
int curPos3;   
int curPos4;

void armMoveBy(int val1, int val2, int val3, int val4) {
  for(int i = curPos1; i != val1; i += (val1 > curPos1 ? 1 : -1)) {
    joint1.write(i);
    delay(15);
    Serial.print(joint1.read());
    Serial.print(", ");
  }
  for(int i = curPos2; i != val2; i += (val2 > curPos2 ? 1 : -1)) {
    joint2.write(i);
    delay(15);
  }
  for(int i = curPos3; i != val3; i += (val3 > curPos3 ? 1 : -1)) {
    joint3.write(i);
    delay(15);
  }
  for(int i = curPos4; i != val4; i += (val4 > curPos4 ? 1 : -1)) {
    joint4.write(i);
    delay(15);
  }

  curPos1 = val1;
  curPos2 = val2;
  curPos3 = val3;
  curPos4 = val4;

}

void setup() {
  Serial.begin(9600);
  
  // Initialize servos
  joint1.attach(J1);
  joint2.attach(J2);
  joint3.attach(J3);
  joint4.attach(J4);
  
  // Set initial positions (for example, all at 90 degrees)
  joint1.write(90);
  joint2.write(90);
  joint3.write(90);
  joint4.write(90);
  
  // Initialize current position trackers
  curPos1 = 90;
  curPos2 = 90;
  curPos3 = 90;
  curPos4 = 90;
}

void loop() {
  if(Serial.available() > 0) {
    // Store the previous positions in case of invalid input
    int prev1 = curPos1;
    int prev2 = curPos2;
    int prev3 = curPos3;
    int prev4 = curPos4;
    
    int pos1 = Serial.parseInt();
    int pos2 = Serial.parseInt();
    int pos3 = Serial.parseInt();
    int pos4 = Serial.parseInt();
    
    // Validate input (0 might be invalid unless explicitly sent)
    if(pos1 == 0 && pos2 == 0 && pos3 == 0 && pos4 == 0) {
      Serial.println("Invalid input - no movement made");
      return;
    }
    
    // Constrain values to valid servo range
    pos1 = constrain(pos1, 0, 180);
    pos2 = constrain(pos2, 0, 180);
    pos3 = constrain(pos3, 0, 180);
    pos4 = constrain(pos4, 0, 180);
    
    delay(25);
    Serial.println("Moving to: " + String(pos1) + ", " + String(pos2) + ", " + 
                  String(pos3) + ", " + String(pos4));
    
    armMoveBy(pos1, pos2, pos3, pos4);
  }
}



