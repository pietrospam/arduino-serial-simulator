#ifndef SERIAL_SIMULATOR_H
#define SERIAL_SIMULATOR_H

#include <Arduino.h>

class SerialSimulator {
private:
    unsigned long lastUpdate;
    int simulationMode;
    float minValue;
    float maxValue;
    
public:
    SerialSimulator(float min = 0.0, float max = 100.0);
    void begin();
    void update();
    void setRange(float min, float max);
    void setMode(int mode);
    float generateRandomValue();
    void sendData(const String& data);
};

#endif