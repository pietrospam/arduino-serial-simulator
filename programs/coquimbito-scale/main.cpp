/*
  Simulador Báscula Coquimbito
  Formato de trama:
    @XXXXXX\r  -> No estabilizado
    DXXXXXX\r  -> Estabilizado (peso > 0)
    F000000\r  -> Estabilizado en cero
  Secuencia:
    1. Envía @000000 (10 veces en cero no estable)
    2. Sube oscilando con "@"
    3. Se estabiliza en el peso final (10 veces con "D")
    4. Baja con "@"
    5. Queda fijo en F000000
*/

int finalWeight = 2260;   // Peso final en kg
int currentWeight = 0;
int zeroCount = 0;
int stableCount = 0;

bool rising = false;
bool stabilized = false;
bool descending = false;
bool finished = false;

void setup() {
  Serial.begin(1200);
  Serial.println("Simulador bascula Coquimbito");
  delay(2000);
}

void loop() {
  if (finished) {
    // Queda fijo en cero estable
    sendFrame('F', 0);
    delay(1000);
    return;
  }

  if (!rising && zeroCount < 10) {
    // Inicio en cero no estabilizado
    sendFrame('@', 0);
    zeroCount++;
  } else if (!rising && zeroCount >= 10) {
    // Pasar a fase de subida
    rising = true;
  } else if (rising && !stabilized) {
    // Subida oscilante (con "@")
    currentWeight += random(50, 200);
    if (currentWeight >= finalWeight) {
      currentWeight = finalWeight;
      stabilized = true;
    }
    sendFrame('@', currentWeight);
  } else if (stabilized && !descending) {
    // Peso final estable (con "D")
    sendFrame('D', currentWeight);
    stableCount++;
    if (stableCount > 10) {
      descending = true;
    }
  } else if (descending) {
    // Descenso oscilante (con "@")
    if (currentWeight > 0) {
      currentWeight -= random(30, 100);
      if (currentWeight < 0) currentWeight = 0;
      sendFrame('@', currentWeight);
    } else {
      finished = true;
    }
  }

  delay(1000);
}

void sendFrame(char prefix, int weight) {
  char buffer[8];
  sprintf(buffer, "%06d", weight); // 6 dígitos con ceros
  Serial.print(prefix);
  Serial.print(buffer);
  Serial.print("\r");
}