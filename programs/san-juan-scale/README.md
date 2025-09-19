# San Juan Scale Simulator - README

## Descripción
Simulador de báscula San Juan que emula la transmisión serie de peso de un vehículo con protocolo STX/ETX específico.

## Configuración Serie

### Parámetros de Conexión
- **Velocidad (Baud Rate):** 9600
- **Bits de Datos:** 8
- **Paridad:** Ninguna (None)
- **Bits de Stop:** 1
- **Control de Flujo:** Ninguno

### Configuración del Terminal
```
9600,8,N,1
```

## Formato de Trama

### Estructura del Protocolo
```
STX (0x02)
[Línea 1: Espacios + "1"]
[Línea 2: Espacios + Peso en decimal]
[Línea 3: Espacios + "0"]
ETX (0x03)
```

### Detalle de la Trama
```
Byte    | Valor         | Descripción
--------|---------------|------------------
0x02    | STX           | Inicio de trama
"      1\r\n"          | ID báscula (10 espacios + "1")
"    1140\r\n"         | Peso (6 espacios + peso + CRLF)
"      0\r\n"          | Flag (10 espacios + "0" + CRLF)
0x03    | ETX           | Fin de trama
```

### Ejemplo de Trama Hexadecimal
```
02 20 20 20 20 20 20 20 20 20 20 31 0D 0A 
20 20 20 20 20 20 31 31 34 30 0D 0A 
20 20 20 20 20 20 20 20 20 20 30 0D 0A 03
```

### Ejemplo de Trama ASCII
```
[STX]          1[CR][LF]      1140[CR][LF]          0[CR][LF][ETX]
```

## Simulación de Peso

### Comportamiento del Simulador
1. **Peso Inicial:** 0 kg
2. **Peso Final:** 1140 kg (configurable)
3. **Incrementos:** 50-200 kg aleatorios
4. **Frecuencia:** Cada 1000 ms
5. **Estabilización:** Al alcanzar el peso final

### Fases de Simulación
```
Tiempo    | Peso     | Estado
----------|----------|------------------
0-2s      | 0        | Inicialización
2-10s     | 0→1140   | Simulación de carga
10s+      | 1140     | Peso estabilizado
```

## Mensajes de Debug

### Salida en Monitor Serie
```
Simulador bascula San Juan
[Pausa de 2 segundos]
[Tramas STX/ETX cada segundo]
```

## Conexiones Hardware

### Configuración Mínima
```
Arduino Uno
┌─────────────┐
│   USB       │ ──── PC (Monitor Serie)
│   Pin 0/1   │ ──── TX/RX (Serial)
│   GND       │ ──── Común
│   5V        │ ──── Alimentación
└─────────────┘
```

### Sin Hardware Adicional Requerido
- No requiere sensores externos
- No requiere conexiones adicionales
- Funciona solo con conexión USB

## Captura de Datos

### Herramientas Recomendadas
- **Arduino IDE:** Monitor Serie integrado
- **PuTTY:** Cliente terminal avanzado
- **RealTerm:** Captura hexadecimal
- **Terminal Windows:** Para pruebas básicas

### Configuración PuTTY
```
Connection Type: Serial
Serial Line: COM[X]
Speed: 9600
Data bits: 8
Stop bits: 1
Parity: None
Flow control: None
```

## Integración con Software

### Lectura del Protocolo
```cpp
// Pseudo-código para leer trama
if (Serial.read() == 0x02) {  // STX
    String line1 = Serial.readStringUntil('\n');  // ID
    String line2 = Serial.readStringUntil('\n');  // Peso
    String line3 = Serial.readStringUntil('\n');  // Flag
    if (Serial.read() == 0x03) {  // ETX
        int weight = line2.trim().toInt();
        // Procesar peso...
    }
}
```

### Ejemplo en Python
```python
import serial

ser = serial.Serial('COM3', 9600)
while True:
    if ser.read() == b'\x02':  # STX
        line1 = ser.readline()  # ID
        line2 = ser.readline()  # Peso
        line3 = ser.readline()  # Flag
        if ser.read() == b'\x03':  # ETX
            weight = int(line2.strip())
            print(f"Peso: {weight} kg")
```

## Casos de Uso

- ✅ Desarrollo de software de pesaje
- ✅ Pruebas de integración con sistemas San Juan
- ✅ Validación de protocolos de comunicación
- ✅ Simulación de cargas de vehículos
- ✅ Testing de aplicaciones de báscula
- ✅ Capacitación en protocolos industriales

## Modificaciones Posibles

### Cambiar Peso Final
```cpp
int finalWeight = 2500;  // Cambiar a peso deseado
```

### Modificar Velocidad de Simulación
```cpp
delay(500);  // Cambiar intervalo (ms)
```

### Personalizar Incrementos
```cpp
currentWeight += random(100, 300);  // Incrementos 100-300 kg
```