#include "SerialSimulator.h"

SerialSimulator::SerialSimulator(float min, float max) {
    minValue = min;
    maxValue = max;
    simulationMode = 1;
    lastUpdate = 0;
}

void SerialSimulator::begin() {
    Serial.begin(9600);
    randomSeed(analogRead(0));
    Serial.println("Serial Simulator initialized");
}

void SerialSimulator::update() {
    unsigned long currentTime = millis();
    
    if (currentTime - lastUpdate >= 1000) { // Update every second
        lastUpdate = currentTime;
        
        switch (simulationMode) {
            case 1: // Random values
                {
                    float value = generateRandomValue();
                    sendData("WEIGHT:" + String(value, 2) + "kg");
                }
                break;
            case 2: // Sequential values
                {
                    static float currentValue = minValue;
                    sendData("WEIGHT:" + String(currentValue, 2) + "kg");
                    currentValue += 1.0;
                    if (currentValue > maxValue) currentValue = minValue;
                }
                break;
            case 3: // Sine wave simulation
                {
                    float value = minValue + (maxValue - minValue) * 
                                 (sin(currentTime / 1000.0) + 1.0) / 2.0;
                    sendData("WEIGHT:" + String(value, 2) + "kg");
                }
                break;
        }
    }
}

void SerialSimulator::setRange(float min, float max) {
    minValue = min;
    maxValue = max;
}

void SerialSimulator::setMode(int mode) {
    simulationMode = mode;
    Serial.println("Simulation mode changed to: " + String(mode));
}

float SerialSimulator::generateRandomValue() {
    return minValue + (float)random(0, 1000) / 1000.0 * (maxValue - minValue);
}

void SerialSimulator::sendData(const String& data) {
    Serial.println(data);
}