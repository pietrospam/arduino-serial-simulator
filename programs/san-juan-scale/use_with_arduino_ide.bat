@echo off
echo ==========================================
echo   San Juan Scale - Arduino IDE Instructions
echo ==========================================
echo.

echo 📂 CODIGO ARDUINO YA PREPARADO
echo.
echo Este directorio contiene:
echo ✅ main.cpp - Codigo del simulador San Juan
echo ✅ README.md - Documentacion completa
echo.
echo 💡 METODO FACIL: Usar archivo .ino en directorio principal
echo.
echo 1. Ve al directorio principal del proyecto
echo 2. Abre: simulador-01-sanJuan.ino
echo 3. Se abrirá directamente en Arduino IDE
echo.

echo 🚀 ¿Ir al directorio principal y abrir Arduino IDE? (S/N)
set /p choice="Respuesta: "

if /i "%choice%"=="S" (
    echo.
    echo 📂 Navegando al directorio principal...
    cd ..\..
    echo.
    echo 🔍 Archivos Arduino disponibles:
    dir *.ino
    echo.
    echo 📝 Abriendo simulador-01-sanJuan.ino en Arduino IDE...
    start simulador-01-sanJuan.ino
    echo.
    echo ✅ Arduino IDE se debería abrir automáticamente
) else (
    echo.
    echo 📋 INSTRUCCIONES MANUALES para Arduino IDE:
    echo.
    echo 1. Abre Arduino IDE
    echo 2. Ve a Archivo ^> Abrir
    echo 3. Navega a: C:\Proyectos\arduino-serial-simulator\
    echo 4. Abre: simulador-01-sanJuan.ino
    echo 5. Selecciona Herramientas ^> Placa ^> Arduino Uno
    echo 6. Selecciona Herramientas ^> Puerto ^> tu puerto COM
    echo 7. Haz click en Upload (flecha)
    echo.
    echo 📡 CONFIGURACION DEL MONITOR SERIE:
    echo - Velocidad: 9600 baud
    echo - El programa mostrará tramas STX/ETX cada segundo
    echo.
)

echo.
echo 📊 CARACTERISTICAS DEL SIMULADOR:
echo - Protocolo: STX/ETX (0x02...0x03)
echo - Peso inicial: 0 kg
echo - Peso final: 1140 kg (configurable)
echo - Ciclo: Subida ^> Estable ^> Bajada ^> Reposo
echo - Frecuencia: 1 segundo
echo.
echo 🔧 Para modificar el peso final, edita la línea:
echo    int finalWeight = 1140;
echo.

pause