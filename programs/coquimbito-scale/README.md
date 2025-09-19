# Coquimbito Scale Simulator - README

## Descripción
Simulador de báscula Coquimbito que emula el protocolo específico con prefijos de estado y transmisión a 1200 baud.

## Configuración Serie

### Parámetros de Conexión
- **Velocidad (Baud Rate):** 1200
- **Bits de Datos:** 8
- **Paridad:** Ninguna (None)
- **Bits de Stop:** 1
- **Control de Flujo:** Ninguno

### Configuración del Terminal
```
1200,8,N,1
```

## Formato de Trama

### Estructura del Protocolo
```
[PREFIJO][XXXXXX]\r
```

Donde:
- **PREFIJO:** Un carácter que indica el estado
- **XXXXXX:** 6 dígitos del peso (con ceros a la izquierda)
- **\r:** Terminador de línea (CR)

### Estados del Prefijo
```
Prefijo | Estado              | Descripción
--------|---------------------|----------------------------------
@       | No estabilizado     | Peso cambiando/oscilando
D       | Estabilizado        | Peso estable y válido (> 0)
F       | Estabilizado en 0   | Peso estable en cero
```

### Ejemplos de Tramas
```
@000000\r    # Cero no estabilizado
@001250\r    # 1250 kg, oscilando
D002260\r    # 2260 kg, estabilizado
@001890\r    # 1890 kg, bajando
F000000\r    # Cero estabilizado (final)
```

## Simulación del Ciclo Completo

### Fases del Simulador
```
Fase            | Duración    | Prefijo | Peso        | Descripción
----------------|-------------|---------|-------------|------------------
Inicio          | 10 seg      | @       | 000000      | Cero no estable
Subida          | Variable    | @       | 0→2260      | Incrementos aleatorios
Estabilización  | 10 seg      | D       | 002260      | Peso final estable
Descenso        | Variable    | @       | 2260→0      | Decrementos aleatorios
Final           | Indefinido  | F       | 000000      | Cero estable permanente
```

### Timing Detallado
```
Tiempo    | Trama        | Estado
----------|--------------|------------------
0-10s     | @000000\r    | Inicialización
10-25s    | @XXXXXX\r    | Subida oscilante
25-35s    | D002260\r    | Peso estabilizado
35-50s    | @XXXXXX\r    | Descenso oscilante
50s+      | F000000\r    | Estado final
```

## Captura de Datos

### Herramientas Recomendadas
- **Arduino IDE:** Monitor Serie (configurar a 1200 baud)
- **PuTTY:** Configuración específica para 1200 baud
- **RealTerm:** Para captura y análisis
- **Terminal personalizado:** Para integración

### Configuración PuTTY
```
Connection Type: Serial
Serial Line: COM[X]
Speed: 1200
Data bits: 8
Stop bits: 1
Parity: None
Flow control: None
```

## Parsing y Regex

### Regex para Extraer Datos
```javascript
// Regex principal para cualquier trama Coquimbito
const coquimbitoRegex = /([FD@])(\d{6})\r/;

// Uso:
const match = data.match(coquimbitoRegex);
if (match) {
    const estado = match[1];      // 'F', 'D', o '@'
    const peso = parseInt(match[2]); // Peso numérico
}
```

### Regex Específicas por Estado
```javascript
// Solo pesos estabilizados (D o F)
const stableRegex = /([DF])(\d{6})\r/;

// Solo pesos válidos estabilizados (D, peso > 0)
const validWeightRegex = /D(\d{6})\r/;

// Solo estado no estabilizado
const unstableRegex = /@(\d{6})\r/;

// Cero estabilizado final
const finalZeroRegex = /F000000\r/;
```

### Parser Completo JavaScript
```javascript
class CoquimbitoWeightParser {
  constructor() {
    this.regex = /([FD@])(\d{6})\r/g;
    this.buffer = '';
  }

  parse(data) {
    this.buffer += data;
    const matches = [];
    let match;

    while ((match = this.regex.exec(this.buffer)) !== null) {
      const state = match[1];
      const weight = parseInt(match[2]);
      
      matches.push({
        timestamp: new Date(),
        state: this.getStateDescription(state),
        stateCode: state,
        weight: weight,
        isStable: (state === 'D' || state === 'F'),
        isValid: (state === 'D' && weight > 0),
        rawData: match[0]
      });
    }

    // Limpiar buffer procesado
    const lastIndex = this.regex.lastIndex;
    if (lastIndex > 0) {
      this.buffer = this.buffer.substring(lastIndex);
    }

    return matches;
  }

  getStateDescription(state) {
    switch(state) {
      case '@': return 'No estabilizado';
      case 'D': return 'Estabilizado';
      case 'F': return 'Cero estabilizado';
      default: return 'Desconocido';
    }
  }
}
```

## Integración con Software

### Ejemplo en C#
```csharp
using System.Text.RegularExpressions;

public class CoquimbitoParser 
{
    private Regex regex = new Regex(@"([FD@])(\d{6})\r");
    
    public WeightReading Parse(string data) 
    {
        var match = regex.Match(data);
        if (match.Success) 
        {
            return new WeightReading 
            {
                State = match.Groups[1].Value[0],
                Weight = int.Parse(match.Groups[2].Value),
                IsStable = (match.Groups[1].Value == "D" || match.Groups[1].Value == "F"),
                Timestamp = DateTime.Now
            };
        }
        return null;
    }
}
```

### Ejemplo en Python
```python
import re
from datetime import datetime

class CoquimbitoParser:
    def __init__(self):
        self.pattern = re.compile(r'([FD@])(\d{6})\r')
    
    def parse(self, data):
        matches = []
        for match in self.pattern.finditer(data):
            state = match.group(1)
            weight = int(match.group(2))
            
            matches.append({
                'timestamp': datetime.now(),
                'state': state,
                'weight': weight,
                'is_stable': state in ['D', 'F'],
                'is_valid': state == 'D' and weight > 0,
                'description': self._get_state_desc(state)
            })
        
        return matches
    
    def _get_state_desc(self, state):
        return {
            '@': 'No estabilizado',
            'D': 'Estabilizado', 
            'F': 'Cero estabilizado'
        }.get(state, 'Desconocido')
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

## Casos de Uso

### Desarrollo de Software
- ✅ Testing de aplicaciones de pesaje Coquimbito
- ✅ Validación de parsing de protocolo
- ✅ Simulación de ciclos completos de pesaje
- ✅ Pruebas de estados de estabilización

### Testing y Validación
- ✅ Verificación de tolerancias de peso
- ✅ Testing de detección de estados
- ✅ Validación de timing de estabilización
- ✅ Pruebas de integración con sistemas

### Capacitación
- ✅ Entrenamiento en protocolo Coquimbito
- ✅ Demostración de ciclos de pesaje
- ✅ Ejemplos de parsing de datos
- ✅ Troubleshooting de comunicación

## Personalización

### Cambiar Peso Final
```cpp
int finalWeight = 3500;  // Cambiar a peso deseado
```

### Modificar Velocidad de Simulación
```cpp
delay(500);  // Cambiar intervalo (ms)
```

### Ajustar Incrementos
```cpp
// En fase de subida
currentWeight += random(100, 300);  // Incrementos 100-300 kg

// En fase de descenso  
currentWeight -= random(50, 150);   // Decrementos 50-150 kg
```

### Cambiar Velocidad Serie
```cpp
Serial.begin(2400);  // Cambiar baudrate si es necesario
```

## Troubleshooting

### Problemas Comunes
1. **Velocidad incorrecta:** Verificar 1200 baud en monitor serie
2. **Datos corruptos:** Verificar conexión USB
3. **Ciclo no progresa:** Verificar timing de delays
4. **Parser no funciona:** Verificar terminador \r

### Mensajes de Debug
```cpp
// Añadir para debugging
Serial.print("DEBUG: Estado=");
Serial.print(rising ? "subida" : "inicio");
Serial.print(" Peso=");
Serial.println(currentWeight);
```

## Comparación con Otros Protocolos

### vs San Juan Scale
- **Coquimbito:** ASCII con prefijos, 1200 baud
- **San Juan:** STX/ETX binario, 9600 baud

### vs Protocolos Comunes
- **Ventaja:** Estados explícitos con prefijos
- **Ventaja:** Parsing simple con regex
- **Desventaja:** Velocidad más lenta (1200 baud)