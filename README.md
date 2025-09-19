# Arduino Serial Simulator

Simuladores Arduino para comunicación serie con básculas y sistemas de pesaje. Optimizado para desarrollo con **Arduino IDE**.

## 🚀 Simuladores Disponibles

### **Simulador San Juan** (`simulador-01-sanJuan.ino`) ⭐
- **Protocolo:** STX/ETX con formato específico San Juan
- **Velocidad:** 9600 baud, 8N1
- **Ciclo completo:** Subida → Estabilización → Descenso → Reposo
- **Peso configurable:** Por defecto 1140 kg
- **Uso:** Testing de software de básculas San Juan

### **Simulador Coquimbito** (`simulador-02-coquimbito.ino`) 🆕
- **Protocolo:** ASCII con prefijos de estado (@/D/F)
- **Velocidad:** 1200 baud, 8N1
- **Estados:** No estabilizado (@), Estabilizado (D), Cero (F)
- **Peso configurable:** Por defecto 2260 kg
- **Uso:** Testing de software de básculas Coquimbito

### **Simulador Básico** (`simulador-basico.ino`)
- **Funciones:** LED, botón, sensor analógico
- **Salida:** Texto legible para debugging
- **Uso:** Verificación de hardware Arduino

## 🎯 Uso Rápido

### **Método 1: Doble-click en archivo .ino**
```
1. Abre simulador-01-sanJuan.ino (San Juan)
   O simulador-02-coquimbito.ino (Coquimbito)
2. Se abre automáticamente en Arduino IDE
3. Selecciona puerto COM
4. Click Upload
```

### **Método 2: Script automático**
```bash
# Para San Juan
cd programs/san-juan-scale
use_with_arduino_ide.bat

# Para Coquimbito
cd programs/coquimbito-scale
use_with_arduino_ide.bat
```

## 📁 Estructura del Proyecto

```
├── simulador-01-sanJuan.ino     # Simulador San Juan (listo para Arduino IDE)
├── simulador-02-coquimbito.ino  # Simulador Coquimbito (listo para Arduino IDE)
├── simulador-basico.ino         # Simulador básico Arduino
├── programs/                    # Código fuente organizado
│   ├── san-juan-scale/          # Documentación San Juan
│   │   ├── main.cpp            # Código fuente
│   │   ├── README.md           # Especificaciones técnicas
│   │   └── use_with_arduino_ide.bat
│   ├── coquimbito-scale/        # Documentación Coquimbito
│   │   ├── main.cpp            # Código fuente  
│   │   ├── README.md           # Especificaciones técnicas
│   │   └── use_with_arduino_ide.bat
│   ├── basic-simulator/         # Documentación básica
│   └── weighbridge-simulator/   # Simulador avanzado
└── README.md                    # Esta documentación
```

## ⚙️ Configuración Arduino IDE

### Configuración de Board:
- **Placa:** Arduino Uno (o compatible)
- **Puerto:** Detectado automáticamente (ej: COM3)
- **Velocidad:** 9600 baud para Monitor Serie

### Monitor Serie:
```
Configuración: 9600 baud, No line ending
Salida esperada: Tramas STX/ETX cada segundo
```

## 🎯 Simulador San Juan - Detalles

### Protocolo de Salida:
```
STX (0x02)
          1\r\n         # ID báscula
          [peso]\r\n    # Peso actual
          0\r\n         # Flag estatus
ETX (0x03)
```

### Fases del Ciclo:
1. **Subida Oscilante:** 0 → 1140 kg (incrementos aleatorios)
2. **Estabilización:** Mantiene peso final (10 ciclos)
3. **Descenso:** 1140 → 0 kg (decrementos aleatorios)
4. **Reposo:** Permanece en 0 kg

### Personalización:
```cpp
int finalWeight = 1140;  // Cambiar peso objetivo
```

## Getting Started

### Prerequisites

1. **VS Code** with **PlatformIO IDE** extension installed
2. **PlatformIO Core** (installed automatically with the extension)
3. **Arduino Framework** (downloaded automatically)

### Installation

1. Open this project in VS Code
2. Wait for PlatformIO to initialize and download dependencies
3. Select your target environment from the bottom status bar

## 📚 Documentación Técnica

Para especificaciones detalladas de cada simulador:

- **San Juan Scale:** `programs/san-juan-scale/README.md`
  - Formato de trama exacto
  - Configuración de puerto serie
  - Ejemplos de parsing regex
  - Integración con software externo

- **Basic Simulator:** `programs/basic-simulator/README.md`
  - Conexiones de hardware
  - Formato de salida
  - Casos de uso

## 🔧 Desarrollo

### Requisitos:
- **Arduino IDE 2.x** (recomendado)
- **Cable USB** para programación
- **Arduino Uno** o compatible

### Workflow:
1. Abre archivo `.ino` en Arduino IDE
2. Selecciona placa y puerto
3. Compila y sube
4. Abre Monitor Serie (9600 baud)

### Para Regex de Parsing:
```javascript
// Extraer peso de trama San Juan
const regex = /\x02[\s\S]*?\r\n\s*(\d+)\s*\r\n\s*0\s*\r\n\x03/;
const peso = data.match(regex)?.[1];
```

## 🚀 Contribuir

1. Fork del repositorio
2. Crea nueva rama para tu simulador
3. Añade archivo `.ino` en directorio raíz
4. Documenta en `programs/tu-simulador/`
5. Envía Pull Request

## 📄 Licencia

MIT License - Libre para uso comercial y personal.