/*
  Simulador de Báscula RS232
  Arduino UNO

  Envía continuamente tramas al puerto serie siguiendo un patrón de valores
  Cada paso mantiene la misma trama durante cierto tiempo, reescribiéndola continuamente.
*/

struct Step {
  const char* trama;        // texto de la trama
  unsigned long durationMs; // tiempo total en ms
  unsigned long intervalMs; // cada cuánto repetir el envío
};

// Secuencia de simulación
Step secuencia[] = {
  {"O000000", 3000, 200},   // 3s, repite cada 200ms
  {"G000000", 1000, 200},   // 1s
  {"E000000", 1000, 200},   // 1s
  {"A000680", 100, 50},     // 0.1s, muy rápido
  {"A000760", 500, 100},    // 0.5s
  {"A000740", 200, 50},
  {"A000780", 200, 50},
  {"A000820", 200, 50},
  {"A000820", 200, 50},
  {"A000820", 200, 50},
  {"A000800", 200, 50},
  {"A000820", 200, 50},
  {"E000820", 200, 50},
  {"E000820", 200, 50},
  {"A001020", 500, 100},
  {"A001340", 1000, 200},
  {"A001460", 2000, 200},
  {"E001480", 10000, 500},
  {"A001340", 1000, 200},
  {"A001020", 500, 100},
  {"E000820", 200, 50},
  {"O000000", 3000, 200},
  {"G000000", 1000, 200},
  {"E000000", 1000, 200}
};

const int numSteps = sizeof(secuencia) / sizeof(secuencia[0]);

void setup() {
  Serial.begin(1200); // ajustar según la báscula real
}

void loop() {
  for (int i = 0; i < numSteps; i++) {
    unsigned long start = millis();
    while (millis() - start < secuencia[i].durationMs) {
      Serial.print(secuencia[i].trama);
      Serial.print("\r");  // agregar LF si hace falta: "\r\n"
      delay(secuencia[i].intervalMs);
    }
  }
}
