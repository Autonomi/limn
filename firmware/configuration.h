// .-.. .. -- -.
// Written for Limn at Autonomi by Prashant S. <prashant@ducic.ac.in>
// License: MIT

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/**
 * Defines the Configurable variables.
 */

// X Axis
#define X_ENB 0         // X Enable Pin
#define X_STP 0         // X STEP Pin
#define X_DIR 0         // X DIRECTION Pin
#define X_LIM 0         // X Limit Switch Pin

#define X_CAL 10        // Number of steps needed for 10 mm movement
#define X_MAX 200       // Maximum X movement allowed (mm)
#define X_D_F true      // X_DIRECTION_FORWARD Allows to adjust X-stepper motor direction.

// Y Axis
#define Y_ENB 0         // Y Enable Pin
#define Y_STP 0         // Y STEP Pin
#define Y_DIR 0         // Y DIRECTION Pin
#define Y_LIM 0         // Y Limit Switch Pin

#define Y_CAL 10        // Number of steps needed for 10 mm movement
#define Y_MAX 200       // Maximum Y movement allowed (mm)
#define Y_D_F true      // Y_DIRECTION_FORWARD Allows to adjust Y-stepper motor direction.

// Z Axis (Final Adjustments, Optional)
#define Z_ENB 0         // Z Enable Pin
#define Z_STP 0         // Z STEP Pin
#define Z_DIR 0         // Z DIRECTION Pin
#define Z_LIM 0         // Z Limit Switch Pin

#define Z_CAL 10        // Number of steps needed for 10 mm movement
#define Z_MAX 200       // Maximum Z movement allowed (mm)
#define Z_D_F true      // Z_DIRECTION_FORWARD Allows to adjust Z-stepper motor direction.

// Print Head (Actuator)
#define P_ENB 0         // Print Head Enable Pin
#define P_STP 0         // Print Head STEP Pin
#define P_DIR 0         // Print Head DIRECTION Pin
#define P_LIM 0         // Print Head Limit Switch Pin

#define P_CAL 10        // Number of steps needed for 10 mm movement
#define P_MAX 200       // Maximum Print Head movement allowed (mm)
#define P_D_F true      // P_DIRECTION_FORWARD Allows to adjust P-stepper motor direction.

// Pulse delays
#define X_Y_PULSE   10
#define Z_PULSE     50
#define P_PULSW     10

#endif