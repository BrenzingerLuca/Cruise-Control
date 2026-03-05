#include <gtest/gtest.h>
#include "cruise_control/simulation.h"

// Test 1: Standard Acceleration (0 to 20 m/s)
TEST(SimulationTest, ReachesTargetFromZero) {
    // Parameters: dt=0.1, dur=500s, mass=1000, friction=50
    // PID: Kp=15.0, Ki=2.0, Kd=1.5 (strong enough to reach target)
    Simulation sim(0.1, 500.0, 50.0, 1000.0, 15.0, 2.0, 1.5, 20.0, 0.0);
    
    sim.run();
    const auto& results = sim.get_results();

    // Check if simulation actually ran
    ASSERT_FALSE(results.empty());

    // Check if final velocity is near target (within 0.1 m/s tolerance)
    double final_vel = results.back();
    EXPECT_NEAR(final_vel, 20.0, 0.1);
}

// Test 2: Staying at zero (0 to 0 m/s)
TEST(SimulationTest, StaysAtZeroWhenTargetIsZero) {
    Simulation sim(0.1, 10.0, 50.0, 1000.0, 5.0, 0.1, 0.01, 0.0, 0.0);
    
    sim.run();
    const auto& results = sim.get_results();

    // In a perfect world it stays exactly 0.0
    EXPECT_NEAR(results.back(), 0.0, 1e-9);
}

// Test 3: Deceleration (High velocity to Low velocity)
TEST(SimulationTest, DeceleratesToTarget) {
    // Start at 50 m/s, target is 20 m/s
    Simulation sim(0.1, 500.0, 50.0, 1000.0, 15.0, 2.0, 1.5, 20.0, 50.0);
    
    sim.run();
    const auto& results = sim.get_results();

    // Final velocity should be near 20.0
    EXPECT_NEAR(results.back(), 20.0, 0.1);
}

// Test 4: Dynamic check - Initial velocity is correctly stored
TEST(SimulationTest, StoresInitialVelocityAsFirstElement) {
    double start_v = 15.5;
    Simulation sim(0.1, 10.0, 50.0, 1000.0, 1.0, 0.0, 0.0, 20.0, start_v);
    
    sim.run();
    const auto& results = sim.get_results();

    ASSERT_GE(results.size(), 1);
    EXPECT_DOUBLE_EQ(results[0], start_v);
}