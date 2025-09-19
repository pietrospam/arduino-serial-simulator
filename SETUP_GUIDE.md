# Setup Arduino Development Environment

## 🚨 **Tu Problema Actual**
```
pip: command not found
```
**Causa:** Python no está instalado o no está en el PATH del sistema.

## ✅ **3 Soluciones Disponibles**

### **Opción A: Python + PlatformIO CLI (Para Programadores)**
1. **Descargar Python:**
   - Ve a https://python.org/downloads
   - Descarga Python 3.9 o superior
   - ⚠️ **IMPORTANTE:** Marca "Add Python to PATH" durante la instalación

2. **Instalar PlatformIO:**
   ```bash
   pip install platformio
   ```

3. **Usar scripts de upload:**
   ```bash
   cd programs/san-juan-scale
   .\upload_manual.bat
   ```

### **Opción B: Arduino IDE (Más Simple) ⭐ RECOMENDADA**
1. **Descargar Arduino IDE:**
   - Ve a https://arduino.cc/downloads
   - Descarga Arduino IDE 2.x
   - Instala normalmente

2. **Usar el programa:**
   ```bash
   cd programs/san-juan-scale
   .\use_with_arduino_ide.bat
   ```

3. **Pasos manuales:**
   - Abre Arduino IDE
   - Carga `main.cpp`
   - Selecciona puerto COM
   - Haz click Upload

### **Opción C: PlatformIO Extension en VS Code ⭐ MEJOR**
1. **Instalar extensión:**
   - En VS Code: `Ctrl+Shift+X`
   - Busca "PlatformIO IDE"
   - Instala la extensión

2. **Usar desde VS Code:**
   - Abre este workspace en VS Code
   - Selecciona environment: `uno_sanjuan`
   - Usa botones Build/Upload en la barra inferior

## 🎯 **Mi Recomendación**

**Para ti:** **Opción B (Arduino IDE)** es la más simple:

1. **Descarga Arduino IDE** desde https://arduino.cc/downloads
2. **Ejecuta esto:**
   ```bash
   cd C:\Proyectos\arduino-serial-simulator\programs\san-juan-scale
   .\use_with_arduino_ide.bat
   ```

## 🚀 **Script de Configuración Automática**

Ejecuta esto para guía paso a paso:
```bash
cd C:\Proyectos\arduino-serial-simulator
.\setup_environment.bat
```

## 📋 **Estado Actual de Tu Sistema**

❌ Python: No instalado  
❌ pip: No disponible  
❌ PlatformIO: No instalado  
✅ VS Code: Disponible  
✅ Código Arduino: Listo  

## 🔧 **Después de Instalar**

### Si instalaste Python + PlatformIO:
```bash
pio --version
cd programs/san-juan-scale
.\upload_manual.bat
```

### Si instalaste Arduino IDE:
```bash
cd programs/san-juan-scale
.\use_with_arduino_ide.bat
```

### Si usas VS Code + PlatformIO Extension:
- Abre workspace en VS Code
- Selecciona `uno_sanjuan` en la barra inferior
- Click en Upload button