@echo off
echo ==================================
echo Coquimbito Scale Simulator Upload
echo ==================================
echo.

REM Detectar puerto Arduino automáticamente
echo Detectando puerto Arduino...

for /f "tokens=*" %%a in ('powershell -Command "Get-WmiObject -Class Win32_PnPEntity | Where-Object {$_.Name -match 'Arduino'} | ForEach-Object {$_.Name -replace '.*\((COM\d+)\).*', '$1'}"') do (
    set ARDUINO_PORT=%%a
    goto :found
)

echo Error: No se encontro ningun Arduino conectado.
echo.
echo Verifica que:
echo 1. El Arduino este conectado via USB
echo 2. Los drivers esten instalados correctamente
echo 3. El Arduino sea reconocido en el Administrador de Dispositivos
echo.
pause
exit /b 1

:found
echo Arduino encontrado en puerto: %ARDUINO_PORT%
echo.

REM Verificar si el archivo main.cpp existe
if not exist "main.cpp" (
    echo Error: No se encontro el archivo main.cpp en el directorio actual.
    echo Asegurate de ejecutar este script desde la carpeta programs/coquimbito-scale/
    echo.
    pause
    exit /b 1
)

echo Preparando para subir codigo del simulador Coquimbito...
echo.
echo INSTRUCCIONES:
echo 1. Abre Arduino IDE 2.x
echo 2. Ve a Archivo ^> Abrir
echo 3. Navega a la carpeta del proyecto: %CD%
echo 4. Abre el archivo: main.cpp
echo 5. Cambia la extension a .ino si es necesario
echo 6. Selecciona Board: Arduino Uno
echo 7. Selecciona Port: %ARDUINO_PORT%
echo 8. Haz clic en Upload (Ctrl+U)
echo.
echo ALTERNATIVA RAPIDA:
echo - Abre: C:\Proyectos\arduino-serial-simulator\simulador-02-coquimbito.ino
echo - Upload directo desde la raiz del proyecto
echo.
echo CONFIGURACION DEL MONITOR SERIE:
echo - Velocidad: 1200 baud
echo - Terminador: Carriage Return (\r)
echo.
echo Protocolo Coquimbito:
echo - @XXXXXX\r = No estabilizado
echo - DXXXXXX\r = Estabilizado  
echo - F000000\r = Cero estabilizado
echo.

pause

REM Intentar abrir Arduino IDE automáticamente
echo Intentando abrir Arduino IDE...
start "" "C:\Program Files\Arduino IDE\Arduino IDE.exe" 2>nul
if errorlevel 1 (
    start "" "C:\Users\%USERNAME%\AppData\Local\Programs\Arduino IDE\Arduino IDE.exe" 2>nul
    if errorlevel 1 (
        echo No se pudo abrir Arduino IDE automaticamente.
        echo Abrelo manualmente y sigue las instrucciones anteriores.
    )
)

echo.
echo Script completado. Revisa las instrucciones anteriores.
pause