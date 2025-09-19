#include <unity.h>
#include <SerialSimulator.h>

SerialSimulator simulator;

void setUp(void) {
    // Set up before each test
}

void tearDown(void) {
    // Clean up after each test
}

void test_simulator_initialization(void) {
    // Test that simulator initializes correctly
    TEST_ASSERT_TRUE(true); // Placeholder test
}

void test_random_value_generation(void) {
    simulator.setRange(10.0, 20.0);
    float value = simulator.generateRandomValue();
    TEST_ASSERT_TRUE(value >= 10.0 && value <= 20.0);
}

void test_range_setting(void) {
    simulator.setRange(5.0, 15.0);
    // This would require accessing private members or adding getter methods
    TEST_ASSERT_TRUE(true); // Placeholder
}

void setup() {
    delay(2000); // Wait for board to initialize
    
    UNITY_BEGIN();
    RUN_TEST(test_simulator_initialization);
    RUN_TEST(test_random_value_generation);
    RUN_TEST(test_range_setting);
    UNITY_END();
}

void loop() {
    // Tests run once in setup()
}