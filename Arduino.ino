#include <Servo.h>

Servo servoX;  // Servo for X-axis
Servo servoY;  // Servo for Y-axis

int x = 90;    // Initial X servo angle
int y = 90;    // Initial Y servo angle

const int buzzerPin = 8; // Buzzer connected to pin 8

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  
  servoX.attach(9);    // Attach X servo to pin 9
  servoY.attach(10);   // Attach Y servo to pin 10
  
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  digitalWrite(buzzerPin, LOW); // Ensure buzzer is off initially
  
  servoX.write(x);     // Set initial position for X servo
  servoY.write(y);     // Set initial position for Y servo
  delay(0);
}

void loop() {
  if (Serial.available()) {  // Check if data is in the serial buffer
    char input = Serial.read();  // Read the input character
    
    int step =5;  // Step size to control servo speed

    // Adjust Y-axis servo
    if (input == 'U' && y + step <= 180) {  // Move up
      y += step;
      servoY.write(y);
    } 
    else if (input == 'D') {  // Move down
      y -= step;
      servoY.write(y);
    }

    // Adjust X-axis servo
    if (input == 'L') {  // Move left
      x -= step;
      servoX.write(x);
    } 
    else if (input == 'R') {  // Move right
      x += step;
      servoX.write(x);
    } 
    
    // If face is detected, the Python script will send 'F' (Face detected)
    if (input == 'F') { 
      digitalWrite(buzzerPin, HIGH); // Turn the buzzer on
      delay(200); // Buzzer beep duration
      digitalWrite(buzzerPin, LOW); // Turn the buzzer off
    }
  }
}
