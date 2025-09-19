#include <Arduino.h>

// Pin definitions
const int LED_PIN = 13;
const int BUTTON_PIN = 2;

// Variables
bool ledState = false;
bool lastButtonState = false;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Initial message
  Serial.println("Arduino Serial Simulator Started");
  Serial.println("Press button to toggle LED");
}

void loop() {
  // Read button state
  bool currentButtonState = digitalRead(BUTTON_PIN);
  
  // Check for button press with debouncing
  if (currentButtonState != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentButtonState == LOW && lastButtonState == HIGH) {
      // Button pressed (inverted logic due to INPUT_PULLUP)
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      
      Serial.print("LED ");
      Serial.println(ledState ? "ON" : "OFF");
    }
  }
  
  lastButtonState = currentButtonState;
  
  // Send periodic data for simulation
  static unsigned long lastSensorRead = 0;
  const unsigned long sensorInterval = 1000; // 1 second
  
  if (millis() - lastSensorRead >= sensorInterval) {
    lastSensorRead = millis();
    
    // Simulate sensor readings
    int analogValue = analogRead(A0);
    float voltage = analogValue * (5.0 / 1023.0);
    
    Serial.print("Analog: ");
    Serial.print(analogValue);
    Serial.print(", Voltage: ");
    Serial.print(voltage, 2);
    Serial.println("V");
  }
}