// Global states for the two LEDs
volatile bool led1State = LOW;
volatile bool led2State = LOW;

// Pin assignments
const int switchPin = 2;       // Slide switch
const int soundSensorPin = 3;  // Sound sensor (digital OUT)
const int led1Pin = 8;         // LED controlled by switch
const int led2Pin = 9;         // LED controlled by sound

void setup() {
  // Set pin modes
  pinMode(switchPin, INPUT_PULLUP);     // Using internal pull-up resistor
  pinMode(soundSensorPin, INPUT);       // Sensor gives digital output
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  Serial.begin(9600); // For monitoring actions

  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(switchPin), toggleLED1, FALLING);
  attachInterrupt(digitalPinToInterrupt(soundSensorPin), toggleLED2, RISING);
}

void loop() {
  // Write LED states based on ISR changes
  digitalWrite(led1Pin, led1State);
  digitalWrite(led2Pin, led2State);
}

// Interrupt Service Routine: Toggle LED1
void toggleLED1() {
  led1State = !led1State;
  Serial.println("Slide switch triggered – LED1 toggled");
}

// Interrupt Service Routine: Toggle LED2
void toggleLED2() {
  led2State = !led2State;
  Serial.println("Sound detected – LED2 toggled");
}

