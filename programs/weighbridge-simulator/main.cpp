/*
  Simulador Báscula de Camiones Avanzado
  Simula el comportamiento real de una báscula de pesaje de vehículos
  con múltiples protocolos y modos de operación.
*/

#include <Arduino.h>

// Configuración del protocolo
enum ProtocolType {
  PROTOCOL_STX_ETX,    // STX...ETX
  PROTOCOL_ASCII,      // ASCII simple
  PROTOCOL_MODBUS      // Modbus RTU básico
};

enum WeightMode {
  MODE_STATIC,         // Peso fijo
  MODE_OSCILLATING,    // Oscilación realista
  MODE_VEHICLE_CYCLE   // Ciclo completo de vehículo
};

// Variables de configuración
ProtocolType currentProtocol = PROTOCOL_STX_ETX;
WeightMode currentMode = MODE_VEHICLE_CYCLE;

// Variables de peso
int targetWeight = 2580;     // Peso objetivo del vehículo
int currentWeight = 0;       // Peso actual
int baseWeight = 0;          // Peso base (tara)
bool vehiclePresent = false; // Estado del vehículo
bool stabilized = false;     // Estado de estabilización

// Timing
unsigned long lastUpdate = 0;
unsigned long cycleStartTime = 0;
const unsigned long updateInterval = 500; // 500ms entre lecturas

// Estados del ciclo de vehículo
enum VehicleState {
  EMPTY,              // Báscula vacía
  ENTERING,           // Vehículo entrando
  STABILIZING,        // Peso estabilizándose
  STABLE,             // Peso estable
  LEAVING             // Vehículo saliendo
};

VehicleState vehicleState = EMPTY;

void setup() {
  Serial.begin(9600);
  Serial.println("Simulador Bascula de Camiones - Avanzado");
  Serial.println("Protocolo: STX/ETX | Modo: Ciclo Vehiculo");
  randomSeed(analogRead(0));
  delay(2000);
}

void loop() {
  if (millis() - lastUpdate >= updateInterval) {
    lastUpdate = millis();
    
    updateWeightSimulation();
    sendWeightData();
  }
  
  // Verificar comandos por serial
  if (Serial.available()) {
    processSerialCommand();
  }
}

void updateWeightSimulation() {
  switch (currentMode) {
    case MODE_STATIC:
      currentWeight = targetWeight;
      stabilized = true;
      break;
      
    case MODE_OSCILLATING:
      if (!stabilized) {
        // Añadir oscilación realista
        int oscillation = random(-50, 51);
        currentWeight = targetWeight + oscillation;
        
        // Eventualmente se estabiliza
        if (random(100) < 5) { // 5% de probabilidad cada ciclo
          stabilized = true;
          currentWeight = targetWeight;
        }
      }
      break;
      
    case MODE_VEHICLE_CYCLE:
      simulateVehicleCycle();
      break;
  }
}

void simulateVehicleCycle() {
  unsigned long elapsed = millis() - cycleStartTime;
  
  switch (vehicleState) {
    case EMPTY:
      currentWeight = baseWeight + random(-10, 11); // Ruido de fondo
      if (elapsed > 5000) { // Después de 5 segundos, llega vehículo
        vehicleState = ENTERING;
        cycleStartTime = millis();
        Serial.println("# Vehiculo detectado - Entrando");
      }
      break;
      
    case ENTERING:
      // Peso aumenta gradualmente
      currentWeight = baseWeight + (elapsed * targetWeight) / 3000; // 3 segundos para entrar
      currentWeight += random(-100, 101); // Oscilación durante entrada
      
      if (elapsed > 3000) {
        vehicleState = STABILIZING;
        cycleStartTime = millis();
        Serial.println("# Vehiculo en posicion - Estabilizando");
      }
      break;
      
    case STABILIZING:
      // Oscilación que se reduce con el tiempo
      int maxOscillation = max(10, 200 - (elapsed / 10));
      currentWeight = targetWeight + random(-maxOscillation, maxOscillation + 1);
      
      if (elapsed > 4000) { // 4 segundos para estabilizar
        vehicleState = STABLE;
        cycleStartTime = millis();
        currentWeight = targetWeight;
        stabilized = true;
        Serial.println("# Peso estabilizado");
      }
      break;
      
    case STABLE:
      currentWeight = targetWeight + random(-5, 6); // Variación mínima
      
      if (elapsed > 6000) { // 6 segundos estable
        vehicleState = LEAVING;
        cycleStartTime = millis();
        stabilized = false;
        Serial.println("# Vehiculo saliendo");
      }
      break;
      
    case LEAVING:
      // Peso disminuye gradualmente
      currentWeight = targetWeight - (elapsed * targetWeight) / 2000; // 2 segundos para salir
      if (currentWeight < baseWeight) currentWeight = baseWeight;
      
      if (elapsed > 2000) {
        vehicleState = EMPTY;
        cycleStartTime = millis();
        currentWeight = baseWeight;
        Serial.println("# Bascula libre");
        
        // Cambiar peso objetivo para próximo vehículo
        targetWeight = random(1500, 4000);
      }
      break;
  }
}

void sendWeightData() {
  switch (currentProtocol) {
    case PROTOCOL_STX_ETX:
      sendSTXETXProtocol();
      break;
    case PROTOCOL_ASCII:
      sendASCIIProtocol();
      break;
    case PROTOCOL_MODBUS:
      sendModbusProtocol();
      break;
  }
}

void sendSTXETXProtocol() {
  Serial.write(0x02); // STX
  
  // Línea 1: ID báscula
  Serial.print("          1\r\n");
  
  // Línea 2: Peso
  char buffer[12];
  sprintf(buffer, "%10d", currentWeight);
  Serial.print(buffer);
  Serial.print("\r\n");
  
  // Línea 3: Flags (0=inestable, 1=estable)
  Serial.print("          ");
  Serial.print(stabilized ? "1" : "0");
  Serial.print("\r\n");
  
  Serial.write(0x03); // ETX
}

void sendASCIIProtocol() {
  Serial.print("WEIGHT:");
  Serial.print(currentWeight);
  Serial.print(" STATUS:");
  Serial.print(stabilized ? "STABLE" : "UNSTABLE");
  Serial.print(" STATE:");
  Serial.println(getStateString());
}

void sendModbusProtocol() {
  // Simulación básica de Modbus RTU
  // (En implementación real usaría CRC)
  Serial.print("MB:");
  Serial.print(currentWeight, HEX);
  Serial.print(":");
  Serial.println(stabilized ? "01" : "00");
}

String getStateString() {
  switch (vehicleState) {
    case EMPTY: return "EMPTY";
    case ENTERING: return "ENTERING";
    case STABILIZING: return "STABILIZING";
    case STABLE: return "STABLE";
    case LEAVING: return "LEAVING";
    default: return "UNKNOWN";
  }
}

void processSerialCommand() {
  String command = Serial.readStringUntil('\n');
  command.trim();
  command.toUpperCase();
  
  if (command == "P1") {
    currentProtocol = PROTOCOL_STX_ETX;
    Serial.println("# Protocolo: STX/ETX");
  } else if (command == "P2") {
    currentProtocol = PROTOCOL_ASCII;
    Serial.println("# Protocolo: ASCII");
  } else if (command == "P3") {
    currentProtocol = PROTOCOL_MODBUS;
    Serial.println("# Protocolo: Modbus");
  } else if (command == "M1") {
    currentMode = MODE_STATIC;
    Serial.println("# Modo: Estatico");
  } else if (command == "M2") {
    currentMode = MODE_OSCILLATING;
    stabilized = false;
    Serial.println("# Modo: Oscilante");
  } else if (command == "M3") {
    currentMode = MODE_VEHICLE_CYCLE;
    vehicleState = EMPTY;
    cycleStartTime = millis();
    Serial.println("# Modo: Ciclo Vehiculo");
  } else if (command.startsWith("W")) {
    targetWeight = command.substring(1).toInt();
    Serial.println("# Peso objetivo: " + String(targetWeight));
  } else if (command == "HELP") {
    Serial.println("# Comandos disponibles:");
    Serial.println("# P1=STX/ETX, P2=ASCII, P3=Modbus");
    Serial.println("# M1=Estatico, M2=Oscilante, M3=Ciclo");
    Serial.println("# W<peso>=Establecer peso objetivo");
    Serial.println("# HELP=Esta ayuda");
  }
}