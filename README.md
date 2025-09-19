# Arduino Serial Simulator

A PlatformIO-based Arduino project for simulating serial communication with various devices, particularly useful for testing weighbridge and scale systems.

## Features

- Serial data simulation with multiple modes
- Configurable data ranges and output formats
- Support for multiple Arduino platforms (Uno, ESP32, NodeMCU)
- Built-in LED and button interaction
- Periodic sensor reading simulation
- Unit testing framework

## Hardware Support

- **Arduino Uno** (ATmega328P)
- **ESP32 Development Board**
- **NodeMCU v2** (ESP8266)

## Project Structure

```
├── src/
│   └── main.cpp           # Main application code
├── include/
│   └── SerialSimulator.h  # Header files
├── lib/
│   └── SerialSimulator/   # Custom library
├── test/
│   └── test_main.cpp      # Unit tests
├── platformio.ini         # PlatformIO configuration
└── README.md              # This file
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

### Building the Project

1. **Using VS Code:**
   - Open Command Palette (Ctrl+Shift+P)
   - Run "PlatformIO: Build"
   - Or click the build icon in the bottom status bar

2. **Using Terminal:**
   ```bash
   pio run
   ```

### Uploading to Arduino

1. Connect your Arduino via USB
2. **Using VS Code:**
   - Open Command Palette (Ctrl+Shift+P)
   - Run "PlatformIO: Upload"
   - Or click the upload icon in the bottom status bar

2. **Using Terminal:**
   ```bash
   pio run --target upload
   ```

### Running Tests

```bash
pio test
```

## Usage

### Basic Operation

1. **LED Control:** Press the button connected to pin 2 to toggle the onboard LED
2. **Serial Output:** The device sends periodic sensor readings and weight simulation data
3. **Monitoring:** Open Serial Monitor (115200 baud) to view output

### Serial Commands

The simulator outputs data in the following formats:

```
Arduino Serial Simulator Started
Press button to toggle LED
LED ON/OFF
Analog: 512, Voltage: 2.50V
WEIGHT:25.67kg
```

### Simulation Modes

The `SerialSimulator` class supports three simulation modes:

1. **Random Values** (default): Generates random weights within specified range
2. **Sequential Values**: Incremental values from min to max
3. **Sine Wave**: Smooth sine wave pattern for realistic simulation

### Customization

Edit `src/main.cpp` to:
- Change pin assignments
- Modify simulation parameters
- Add custom serial protocols
- Adjust timing intervals

## Configuration

### Environment Selection

The `platformio.ini` file defines three environments:

- `uno`: Arduino Uno (ATmega328P)
- `esp32dev`: ESP32 Development Board
- `nodemcuv2`: NodeMCU v2 (ESP8266)

Switch environments using the PlatformIO environment selector in VS Code.

### Pin Configuration

Default pin assignments:
- LED: Pin 13 (built-in)
- Button: Pin 2 (with internal pull-up)
- Analog input: A0

## Development

### Adding Libraries

1. Add dependencies to `platformio.ini`:
   ```ini
   lib_deps = 
       ArduinoJson
       ESP32Servo
   ```

2. Or install via PlatformIO Library Manager

### Code Style

- Follow Arduino conventions
- Use meaningful variable names
- Comment complex logic
- Keep functions small and focused

### Testing

Write unit tests in the `test/` directory using the PlatformIO Unit Testing framework.

## Troubleshooting

### Common Issues

1. **Build Errors:**
   - Ensure PlatformIO extension is properly installed
   - Check that the correct board is selected
   - Verify all dependencies are downloaded

2. **Upload Errors:**
   - Check USB connection
   - Verify correct COM port selection
   - Ensure no other serial monitors are open

3. **Serial Monitor Issues:**
   - Set correct baud rate (9600)
   - Check board selection
   - Verify serial cable connection

### Getting Help

- Check PlatformIO documentation: https://docs.platformio.org/
- Arduino reference: https://www.arduino.cc/reference/
- ESP32 documentation: https://docs.espressif.com/

## License

This project is open source and available under the MIT License.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request