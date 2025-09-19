/*
  Simulador Báscula San Juan
  Emula transmisión serie de peso de un vehículo.
  Secuencia:
  1. Sube oscilando desde 0 hasta el peso final.
  2. Se estabiliza en el peso final (10 veces).
  3. Desciende gradualmente a 0.
  4. Queda en 0.
*/

#define STX 0x02
#define ETX 0x03

int finalWeight = 1140;   // Peso final en kg
int currentWeight = 0;    // Peso inicial
int stableCount = 0;      // Contador de estabilización
bool stabilized = false;  // Estado de estabilización
bool descending = false;  // Estado de descenso

void setup() {
  Serial.begin(9600);
  Serial.println("Simulador bascula San Juan");
  delay(2000); // Pausa antes de iniciar
}

void loop() {
  if (!stabilized && !descending) {
    // Fase de subida oscilante
    currentWeight += random(50, 200);
    if (currentWeight >= finalWeight) {
      currentWeight = finalWeight;
      stabilized = true;
    }
  } else if (stabilized && !descending) {
    // Fase estable
    stableCount++;
    if (stableCount > 10) {
      descending = true;
    }
  } else if (descending) {
    // Fase de descenso gradual
    if (currentWeight > 0) {
      currentWeight -= random(30, 100);
      if (currentWeight < 0) currentWeight = 0;
    }
  }

  // Enviar la trama con el formato capturado
  Serial.write(STX);

  // Línea 1: espacios + "1"
  Serial.print("          1\r\n");

  // Línea 2: espacios + peso
  Serial.print("          ");
  Serial.print(currentWeight);
  Serial.print("\r\n");

  // Línea 3: espacios + "0"
  Serial.print("          0\r\n");

  Serial.write(ETX);

  delay(1000); // cada segundo
}
