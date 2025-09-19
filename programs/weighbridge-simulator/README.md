# Advanced Weighbridge Simulator - README

## Descripción
Simulador avanzado de báscula de camiones con soporte multi-protocolo, ciclo completo de vehículo y comandos interactivos.

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

## Protocolos Soportados

### 1. Protocolo STX/ETX (P1)
```
STX (0x02)
[Línea 1: "          1\r\n"]        # ID báscula
[Línea 2: "  [peso]\r\n"]           # Peso con espacios
[Línea 3: "          [flag]\r\n"]   # Flag estabilidad
ETX (0x03)
```

**Ejemplo:**
```
02 20 20 20 20 20 20 20 20 20 20 31 0D 0A 
20 20 20 20 20 20 32 35 38 30 0D 0A 
20 20 20 20 20 20 20 20 20 20 31 0D 0A 03
```

### 2. Protocolo ASCII (P2)
```
WEIGHT:[peso] STATUS:[estado] STATE:[fase]
```

**Ejemplo:**
```
WEIGHT:2580 STATUS:STABLE STATE:STABLE
WEIGHT:2567 STATUS:UNSTABLE STATE:STABILIZING
```

### 3. Protocolo Modbus RTU (P3)
```
MB:[peso_hex]:[flag_hex]
```

**Ejemplo:**
```
MB:A14:01    # Peso 2580 (0xA14), Estable (0x01)
MB:A07:00    # Peso 2567 (0xA07), Inestable (0x00)
```

## Modos de Operación

### Modo 1: Estático (M1)
- **Peso:** Fijo en valor objetivo
- **Estabilidad:** Siempre estable
- **Uso:** Pruebas básicas de comunicación

### Modo 2: Oscilante (M2)
- **Peso:** Objetivo ± oscilación aleatoria
- **Estabilidad:** Se estabiliza gradualmente
- **Uso:** Simulación de vibración de báscula

### Modo 3: Ciclo de Vehículo (M3)
- **Fases:** Vacío → Entrando → Estabilizando → Estable → Saliendo
- **Peso:** Simulación realista de pesaje
- **Uso:** Testing completo de aplicaciones

## Ciclo de Vehículo Detallado

### Fases del Ciclo
```
Fase          | Duración | Peso              | Estado
--------------|----------|-------------------|------------------
EMPTY         | 5s       | 0 ± ruido         | Báscula libre
ENTERING      | 3s       | 0 → peso_objetivo | Vehículo entrando
STABILIZING   | 4s       | objetivo ± oscil. | Estabilizando
STABLE        | 6s       | objetivo ± 5kg    | Peso estable
LEAVING       | 2s       | objetivo → 0      | Vehículo saliendo
```

### Mensajes de Estado
```
# Vehiculo detectado - Entrando
# Vehiculo en posicion - Estabilizando  
# Peso estabilizado
# Vehiculo saliendo
# Bascula libre
```

## Comandos Interactivos

### Comandos de Protocolo
```
Comando | Descripción
--------|----------------------------------
P1      | Cambiar a protocolo STX/ETX
P2      | Cambiar a protocolo ASCII
P3      | Cambiar a protocolo Modbus RTU
```

### Comandos de Modo
```
Comando | Descripción
--------|----------------------------------
M1      | Modo estático
M2      | Modo oscilante
M3      | Modo ciclo de vehículo
```

### Comandos de Configuración
```
Comando     | Descripción              | Ejemplo
------------|--------------------------|----------
W[peso]     | Establecer peso objetivo | W2500
HELP        | Mostrar ayuda completa   | HELP
```

### Ejemplo de Sesión Interactiva
```
> P2
# Protocolo: ASCII

> M1  
# Modo: Estatico

> W3000
# Peso objetivo: 3000

> WEIGHT:3000 STATUS:STABLE STATE:STABLE

> M3
# Modo: Ciclo Vehiculo
# Vehiculo detectado - Entrando
> WEIGHT:1250 STATUS:UNSTABLE STATE:ENTERING
```

## Salida de Datos

### Frecuencia de Transmisión
- **Intervalo:** 500 ms (2 Hz)
- **Configurable:** Modificar `updateInterval`

### Formato de Timestamp
```cpp
unsigned long timestamp = millis();
```

## Conexiones Hardware

### Configuración Básica
```
Arduino Uno/ESP32
┌─────────────┐
│   USB/UART  │ ──── PC/Sistema de pesaje
│   Pin A0    │ ──── Semilla random (opcional)
│   GND       │ ──── Común
│   VCC       │ ──── Alimentación
└─────────────┘
```

### Sin Hardware Adicional
- Simulador completamente software
- No requiere sensores externos
- Ideal para desarrollo y testing

## Integración de Software

### Lectura Protocolo STX/ETX
```cpp
enum FrameState { WAIT_STX, READ_DATA, WAIT_ETX };
FrameState state = WAIT_STX;

void parseFrame() {
    switch(state) {
        case WAIT_STX:
            if (Serial.read() == 0x02) state = READ_DATA;
            break;
        case READ_DATA:
            // Leer 3 líneas de datos
            break;
        case WAIT_ETX:
            if (Serial.read() == 0x03) processWeight();
            break;
    }
}
```

### Lectura Protocolo ASCII
```python
import re

def parse_ascii(line):
    pattern = r'WEIGHT:(\d+) STATUS:(\w+) STATE:(\w+)'
    match = re.match(pattern, line)
    if match:
        weight = int(match.group(1))
        status = match.group(2)
        state = match.group(3)
        return weight, status, state
    return None
```

### Lectura Protocolo Modbus
```cpp
void parseModbus(String data) {
    if (data.startsWith("MB:")) {
        int colon1 = data.indexOf(':', 3);
        int colon2 = data.indexOf(':', colon1 + 1);
        
        String weightHex = data.substring(3, colon1);
        String flagHex = data.substring(colon1 + 1, colon2);
        
        int weight = strtol(weightHex.c_str(), NULL, 16);
        int flag = strtol(flagHex.c_str(), NULL, 16);
    }
}
```

## Casos de Uso

### Desarrollo de Software
- ✅ Testing de aplicaciones de pesaje
- ✅ Validación de protocolos múltiples
- ✅ Simulación de escenarios reales
- ✅ Pruebas de estabilidad y timing

### Capacitación y Demostración
- ✅ Entrenamiento en protocolos industriales
- ✅ Demostración de ciclos de pesaje
- ✅ Ejemplos de integración
- ✅ Troubleshooting de comunicaciones

### Testing Automatizado
- ✅ Pruebas de regresión
- ✅ Validación de tolerancias
- ✅ Testing de comandos
- ✅ Verificación de protocolos

## Personalización

### Modificar Pesos de Simulación
```cpp
targetWeight = random(1500, 4000);  // Rango de pesos
baseWeight = 50;                    // Peso base/tara
```

### Ajustar Tiempos de Ciclo
```cpp
// En simulateVehicleCycle()
if (elapsed > 3000) {  // Cambiar duración de fases
```

### Añadir Nuevos Protocolos
```cpp
case PROTOCOL_CUSTOM:
    sendCustomProtocol();
    break;
```

### Configurar Oscilación
```cpp
int maxOscillation = max(10, 200 - (elapsed / 10));
currentWeight = targetWeight + random(-maxOscillation, maxOscillation + 1);
```

## Troubleshooting

### Problemas Comunes
1. **Sin respuesta a comandos:** Verificar terminación `\n`
2. **Datos corruptos:** Verificar velocidad serie
3. **Ciclo no funciona:** Verificar modo M3 activo
4. **Protocolo incorrecto:** Verificar comando P1/P2/P3

### Debug
```cpp
Serial.println("# DEBUG: Estado actual = " + String(vehicleState));
Serial.println("# DEBUG: Peso = " + String(currentWeight));
```