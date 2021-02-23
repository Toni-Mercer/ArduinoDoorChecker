/**
 * @author Antoni Mercer <https://github.com/Toni-Mercer/>
 * @license MIT <https://mit-license.org/>
 * This program is just to execute a To Be Continued JoJo's Audio on the PC. Via an exe that reads Serial communication.
 */

#define VALID_ITERATIONS 3

// inputs
#define DOOR_SATUS 1
#define DOOR_DISABLE 2
#define DOOR_ENABLE 3

// phisical connections
const int door = 2;
const int ledPin =  LED_BUILTIN;

// internal variables
int doorStatus = 0;
int iterations = 0;
bool alarmOn = true;
int operation = -1;
bool advised = false;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(door, INPUT);
}

void loop() {
  doorStatus = digitalRead(door);

  if (Serial.available() > 0) {
    // read the serial and parse the command
    operation = Serial.parseInt();
    switch(operation){
      case DOOR_SATUS:
        Serial.println(doorStatus);
        break;
      case DOOR_DISABLE:
        // Serial.println("alarm = false");
        alarmOn = false;
        break;
      case DOOR_ENABLE:
        // Serial.println("alarm = true");
        alarmOn = true;
        break;
    }
  }
    
  if (doorStatus == LOW){
    iterations++;
    // door is open increment iterations
    if (!advised && iterations > VALID_ITERATIONS){
        if (alarmOn) Serial.println("opening");
        advised = true;
        iterations = 0;
    }
  }

  if (doorStatus == HIGH) {
    digitalWrite(ledPin, HIGH);
    if (advised) {
      if (alarmOn) Serial.println("closing");
    }
    advised = false;
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(235); // really high delay to avoid switch bounce
}
