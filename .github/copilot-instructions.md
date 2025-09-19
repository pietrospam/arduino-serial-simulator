# Arduino Development Workspace Instructions

This workspace is configured for Arduino development with the following guidelines:

## Development Environment
- Target platform: Arduino (AVR, ESP32, ESP8266, etc.)
- Language: C/C++ for embedded systems
- Build system: PlatformIO or Arduino CLI
- Hardware simulation capabilities

## Code Style Guidelines
- Use standard Arduino conventions
- Keep functions small and focused
- Use meaningful variable names
- Comment complex logic
- Follow embedded C++ best practices

## Project Structure
- `src/` - Main source code
- `lib/` - Custom libraries
- `include/` - Header files
- `test/` - Unit tests
- `docs/` - Documentation

## Hardware Considerations
- Always consider memory constraints
- Optimize for power consumption when relevant
- Use appropriate data types for embedded systems
- Handle interrupts carefully
- Consider real-time constraints

## Testing
- Write unit tests for complex logic
- Test on actual hardware when possible
- Use serial debugging for troubleshooting
- Monitor memory usage

## Documentation
- Document pin assignments
- Include wiring diagrams when relevant
- Explain hardware dependencies
- Provide setup instructions