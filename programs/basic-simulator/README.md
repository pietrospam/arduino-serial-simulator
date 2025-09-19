# Basic Simulator - README

## Descripción
Simulador básico de Arduino con interacción LED/botón y lecturas de sensores periódicas.

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

### Mensajes de Inicio
```
Arduino Serial Simulator Started
Press button to toggle LED
```

### Eventos de Botón
```
LED ON
LED OFF
```

### Datos de Sensores (cada 1 segundo)
```
Analog: [valor], Voltage: [voltaje]V
```

### Ejemplo de Salida Completa
```
Arduino Serial Simulator Started
Press button to toggle LED
Analog: 512, Voltage: 2.50V
LED ON
Analog: 498, Voltage: 2.43V
Analog: 523, Voltage: 2.55V
LED OFF
Analog: 501, Voltage: 2.45V
```

## Conexiones Hardware

### Pines Utilizados
- **LED:** Pin 13 (LED integrado)
- **Botón:** Pin 2 (con pull-up interno)
- **Sensor Analógico:** Pin A0

### Diagrama de Conexión
```
Arduino Uno
┌─────────────┐
│    Pin 13   │ ──── LED (integrado)
│    Pin 2    │ ──── Botón + 10kΩ pull-up
│    Pin A0   │ ──── Sensor/Potenciómetro
│    GND      │ ──── Común
│    5V       │ ──── Alimentación
└─────────────┘
```

## Uso del Programa

1. **Cargar el programa** al Arduino
2. **Conectar Monitor Serie** a 9600 baud
3. **Observar lecturas** de sensores cada segundo
4. **Presionar botón** para alternar LED
5. **Verificar salida** en monitor serie

## Casos de Uso

- ✅ Verificación básica de funcionamiento del Arduino
- ✅ Pruebas de comunicación serie
- ✅ Calibración de sensores analógicos
- ✅ Pruebas de entrada digital con botón
- ✅ Validación de configuración de hardware