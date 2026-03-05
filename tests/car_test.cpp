#include <gtest/gtest.h>
#include "cruise_control/car.h"

// Test 1: Basic Velocity Update
TEST(CarPhysicsTest, UpdatesVelocityCorrectly) {
    Car car(1000.0, 50.0);
    double v_init = 10.0;
    double acc = 2.0;
    double dt = 0.5;

    // Expected: 10.0 + (2.0 * 0.5) = 11.0
    EXPECT_DOUBLE_EQ(car.update_vel(v_init, acc, dt), 11.0);
}

// Test 2: Acceleration from standstill
TEST(CarPhysicsTest, CalculatesAccelerationFromStandstill) {
    Car car(1000.0, 50.0);
    double force = 1000.0;
    double v_current = 0.0;

    // Expected: (1000 - 50*0) / 1000 = 1.0
    double acc = car.calculate_acc(v_current, force);
    EXPECT_DOUBLE_EQ(acc, 1.0);
}

// Test 3: Friction and Deceleration (Coasting)
TEST(CarPhysicsTest, CalculatesDecelerationDueToFriction) {
    Car car(1000.0, 50.0);
    double force = 0.0;     // No engine force
    double v_current = 20.0; // Moving at 20 m/s

    // Expected: (0 - 50*20) / 1000 = -1.0
    double acc = car.calculate_acc(v_current, force);
    EXPECT_DOUBLE_EQ(acc, -1.0);
}

// Test 4: Zero Acceleration
TEST(CarPhysicsTest, ReachesEquilibriumAtTerminalVelocity) {
    Car car(1000.0, 50.0);
    double force = 1000.0;
    double v_current = 20.0;

    // Expected: (1000 - 50*20) / 1000 = 0.0
    double acc = car.calculate_acc(v_current, force);
    
    // Using NEAR because floating point math can be tricky at zero
    EXPECT_NEAR(acc, 0.0, 1e-9);
}