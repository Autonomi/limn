#include "configuration.h"
#include "Arduino.h"

#ifndef STEPPER_CPP
#define STEPPER_CPP

/**
 * Encapsulates the Stepper Motor Functions.
 */
class Stepper {
private:

public:
    /**
     * Initializes the Arduino Mega Pins.
     * @return boolean
     */
    static bool init () {
        pinMode(X_ENB, OUTPUT);
        pinMode(X_STP, OUTPUT);
        pinMode(X_DIR, OUTPUT);

        pinMode(Y_ENB, OUTPUT);
        pinMode(Y_STP, OUTPUT);
        pinMode(Y_DIR, OUTPUT);

        pinMode(Z_ENB, OUTPUT);
        pinMode(Z_STP, OUTPUT);
        pinMode(Z_DIR, OUTPUT);

        pinMode(P_ENB, OUTPUT);
        pinMode(P_STP, OUTPUT);
        pinMode(P_DIR, OUTPUT);

        digitalWrite(X_ENB, LOW);
        digitalWrite(X_STP, LOW);
        digitalWrite(X_DIR, LOW);

        digitalWrite(Y_ENB, LOW);
        digitalWrite(Y_STP, LOW);
        digitalWrite(Y_DIR, LOW);

        digitalWrite(Z_ENB, LOW);
        digitalWrite(Z_STP, LOW);
        digitalWrite(Z_DIR, LOW);

        digitalWrite(P_ENB, LOW);
        digitalWrite(P_STP, LOW);
        digitalWrite(P_DIR, LOW);

        return true;
    }

    static bool enable_x() {
        digitalWrite(X_ENB, LOW);
    }

    static bool disable_x () {
        digitalWrite(X_ENB, LOW);
    }

    static bool step_x_y () {
        //
    }

};

#endif