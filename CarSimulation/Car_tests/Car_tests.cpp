#define CATCH_CONFIG_MAIN
#include "../../../Catch/catch.hpp"
#include "../CarSimulation/Car.h"

SCENARIO("Car engine control") {
    GIVEN("A new car") {
        Car car;

        THEN("The engine should be off by default") {
            REQUIRE_FALSE(car.TurnOffEngine());
        }

        WHEN("The engine is turned on") {
            REQUIRE(car.TurnOnEngine());

            THEN("It should be possible to turn it off when in neutral and stationary") {
                REQUIRE(car.TurnOffEngine());
            }

            WHEN("The car is moving") {
                car.SetGear(1);
                car.SetSpeed(10);

                THEN("The engine cannot be turned off") {
                    REQUIRE_FALSE(car.TurnOffEngine());
                }
            }
        }
    }
}

SCENARIO("Car gear shifting") {
    GIVEN("A car with the engine on") {
        Car car;
        car.TurnOnEngine();

        THEN("The car should be able to shift to 1st gear") {
            REQUIRE(car.SetGear(1));
        }

        WHEN("The car is moving forward") {
            car.SetGear(1);
            car.SetSpeed(20);

            THEN("It cannot shift to reverse") {
                REQUIRE_FALSE(car.SetGear(-1));
            }

            THEN("It can shift to 2nd gear") {
                REQUIRE(car.SetGear(2));
            }
        }

        WHEN("The car is in reverse") {
            car.SetGear(-1);
            car.SetSpeed(5);

            THEN("It cannot shift to forward gear while moving") {
                REQUIRE_FALSE(car.SetGear(1));
            }
        }

        THEN("Invalid gear values should be rejected") {
            REQUIRE_FALSE(car.SetGear(6));
        }
    }
}

SCENARIO("Car speed control") {
    GIVEN("A car with the engine on and in first gear") {
        Car car;
        car.TurnOnEngine();
        car.SetGear(1);

        WHEN("The speed is set within the gear limit") {
            REQUIRE(car.SetSpeed(30));

            THEN("The speed should be updated correctly") {
                REQUIRE(car.SetSpeed(20));
            }
        }

        WHEN("The speed is set beyond the gear limit") {
            THEN("It should fail") {
                REQUIRE_FALSE(car.SetSpeed(40));
            }
        }

        WHEN("The gear is set to neutral") {
            car.SetGear(0);

            THEN("Acceleration should not be possible") {
                REQUIRE_FALSE(car.SetSpeed(40));
            }
        }
    }
}
