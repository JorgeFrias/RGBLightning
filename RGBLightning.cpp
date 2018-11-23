/*
  RGBLightning.cpp - Library for setting smoothly RGB non directionable led strips.
  Created by Jorge Frias, September 29, 2018.
*/

#include "Arduino.h"
#include "math.h"
#include "RGBLightning.h"

/**
 * int resolution: Resolution of the piout of the board (255, 1024, 2046...)
 */
RGBLightning::RGBLightning(int pinRed, int pinGreen, int pinBlue, BoardResolution boardResolution)
{
    _PinRed = pinRed;
    _PinGreen = pinGreen;
    _PinBlue = pinBlue;
    _BoardResol = boardResolution;
}

void RGBLightning::begin()
{
    _Red	= 0;    		        // Current red component
    _Green	= 0;			        // Current green component
    _Blue	= 0;			        // Current blue component

    _fadeStepsPerSecond = 30;	    // Fade transition fps

    pinMode(_PinRed, OUTPUT);
    pinMode(_PinGreen, OUTPUT);
    pinMode(_PinBlue, OUTPUT);

    if(_BoardResol == r1024)
        analogWriteRange(254);          // Reduce the range to ESP286 boards
}

/**
 * Writes the given color at the LEDs
 * Private Function, only use with other code witch updates the global variables
 */
void RGBLightning::WriteColor(int R, int G, int B)
{
    // Invert: for the strip 0 is full color
    analogWrite(_PinRed, 255 - R);
    analogWrite(_PinGreen, 255 - G);
    analogWrite(_PinBlue, 255 - B);

    Serial.println("setting color");
    Serial.print("_PinRed: ");
    Serial.println(_PinRed);
    Serial.print("Value: ");
    Serial.println(R);
}

/**
 * Writes the given color at the LEDs inmediately 
 */
void RGBLightning::SetColor(int R, int G, int B)
{
    _Red = R;
    _Green = G;
    _Blue = B;
    WriteColor(R, G, B);
}

/**
 * Calculates the step for each fotogram for a given color component. 
 * Is double because due to rounding the numbers, the error can grow
 */
double RGBLightning::FadeStep(int initialColorComp, int endColorComp, int nSteps)
{
    double diference = endColorComp - initialColorComp;
    double step = diference / nSteps;
    return step;
}

/**
 * Makes the LEDs fade from the current color to the given one 
 */
void RGBLightning::FadeColor(int R, int G, int B, int FadeTime)
{
    if (FadeTime <= 0 )
    {
        SetColor(R, G, B);
    }
    
    /* Do not update the global variables until is finished! */
    int nSteps;
    int photogramLapse;

    // Fading calcs
    double fotogramsPerMs = _fadeStepsPerSecond / 1000.0; // Frecuency in ms
    photogramLapse = (int)ceil(1 / fotogramsPerMs);       // Period = 1/frecuency
    nSteps = (int)ceil(FadeTime / photogramLapse);        // Steps

    // Color steps for each component
    double rStep = FadeStep(_Red, R, nSteps);
    double gStep = FadeStep(_Green, G, nSteps);
    double bStep = FadeStep(_Blue, B, nSteps);

    // Variables with the current color
    double actualR = _Red;
    double actualG = _Green;
    double actualB = _Blue;

    // Updating process
    for (int i = 0; i < nSteps; i++)
    {
        actualR += rStep;
        actualG += gStep;
        actualB += bStep;
        WriteColor((int)actualR, (int)actualG, (int)actualB);
        delay(photogramLapse); // Sleep the time of this frame
    }

    // Last update because of rounding can be diferent
    _Red = R;
    _Green = G;
    _Blue = B;
    WriteColor(R, G, B);
}