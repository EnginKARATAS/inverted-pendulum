#ifndef PYTHON_UTILS
#define PYTHON_UTILS

#include <Arduino.h>

struct stateVector
{
    double pendulumAngle;
    double cartPosition;
    double pendulumAngularVelocity = 6.0;
    double cartVelocity = 5.0;
};


float encoderCountToAngleDegrees(long encoderCount);
float encoderCountToCartPositionInches(long cartEncoderCount, double encoderPPR);
void sendStateVectorToPython(stateVector state);


float encoderCountToAngleRadians(long encoderCount, double encoderPPR)
{
    return (encoderCount / encoderPPR) * (2.0 * PI);
}

float encoderCountToCartPositionInches(long cartEncoderCount, double encoderPPR) {
    float idlerPulleyRadius = 0.189;                                            // inches
    float cartAngle = encoderCountToAngleRadians(cartEncoderCount, encoderPPR); // radians
    return idlerPulleyRadius * cartAngle;
}

float encoderCountToPendulumAngleRadians(long encoderCount, double encoderPPR) {
    // Since we use the <Encoder.h> library which initializes the encoder to zero at the start,
    // we need to correct the value because we start at a pendulum angle of +180 degrees.
    return PI + encoderCountToAngleRadians(encoderCount, encoderPPR);
}

void sendStateVectorToPython(stateVector state)
{
    Serial.print(state.pendulumAngle);
    Serial.print(",");
    Serial.print(state.cartPosition);
    Serial.print(",");
    Serial.print(state.pendulumAngularVelocity);
    Serial.print(",");
    Serial.print(state.cartVelocity);
    Serial.println();
}

#endif