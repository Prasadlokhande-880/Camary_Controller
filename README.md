# Camary Controller: Servo and Buzzer with Python OpenCV

This project is designed to control a camera mounted on two servos (X-axis and Y-axis) and a buzzer using Arduino and Python with OpenCV for face detection. The system adjusts the servo angles to center the detected face and activates the buzzer when a face is detected.


https://github.com/user-attachments/assets/361c5faa-908d-4851-a457-a1ef1967ecb2


## Features
- Real-time face detection using Python and OpenCV.
- Automatic adjustment of servo angles to track the detected face.
- Buzzer activation upon face detection.
- Smooth servo motion with adjustable step size.

## Components Required
1. Arduino board (e.g., Uno, Mega, Nano, etc.)
2. Two servo motors
3. Buzzer
4. Webcam
5. Jumper wires
6. Power supply

## Wiring Diagram
| Component       | Arduino Pin |
|-----------------|-------------|
| X-axis Servo    | 9           |
| Y-axis Servo    | 10          |
| Buzzer          | 8           |

### Circuit Explanation:
- Connect the control wires of the X and Y axis servos to pins 9 and 10 respectively.
- Connect the buzzer's positive pin to pin 8 and the negative pin to GND.
- Power the servos and the buzzer through the Arduino.

## Installation and Setup
### Arduino Setup
1. Connect the hardware as per the wiring diagram.
2. Upload the provided Arduino code to your board using the Arduino IDE.
3. Ensure the baud rate in the Serial Monitor is set to `9600`.

### Python Setup
1. Install Python on your system.
2. Install the required Python libraries:
   ```bash
   pip install opencv-python pyserial
   ```
3. Run the Python script for face detection and serial communication.

## Usage
The Arduino program responds to specific commands received via serial communication from the Python script:

### Commands
| Command | Function              |
|---------|-----------------------|
| `U`     | Move Y-axis servo up  |
| `D`     | Move Y-axis servo down|
| `L`     | Move X-axis servo left|
| `R`     | Move X-axis servo right|
| `F`     | Trigger the buzzer    |

### Face Tracking Workflow
1. The Python script uses OpenCV to detect a face in the camera feed.
2. Based on the face's position, the script calculates the direction to move the servos (e.g., `U`, `D`, `L`, `R`).
3. The script sends the appropriate commands to the Arduino via serial communication.
4. When a face is detected, the script also sends the `F` command to trigger the buzzer.

### Example Python Script
```python
import cv2
import serial
import time

# Initialize serial communication with Arduino
arduino = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)  # Wait for connection

# Initialize OpenCV face detector
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

    for (x, y, w, h) in faces:
        # Calculate center of the face
        center_x = x + w // 2
        center_y = y + h // 2

        # Send commands based on face position
        if center_x < 200:
            arduino.write(b'L')  # Move left
        elif center_x > 440:
            arduino.write(b'R')  # Move right

        if center_y < 150:
            arduino.write(b'U')  # Move up
        elif center_y > 330:
            arduino.write(b'D')  # Move down

        # Trigger the buzzer
        arduino.write(b'F')

    cv2.imshow('Face Tracker', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
arduino.close()
```

## Customization
- Modify the `step` variable in the Arduino code to adjust the step size for smoother or faster servo movements.
- Adjust the OpenCV face detection parameters (e.g., `scaleFactor`, `minNeighbors`) for better detection accuracy.
- Update the buzzer beep duration in the Arduino code by changing the `delay` value in the `if (input == 'F')` block.

## Repository Name
**camary-controller**

## License
This project is open-source and can be used or modified freely.

## Author
[Prasad Lokhande](mailto:prasadlokhande880@gmail.com)

