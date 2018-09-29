/*
  RGBLightning.h - Library for setting smoothly RGB non directionable led strips.
  Created by Jorge Frias, September 29, 2018.
*/


#ifndef RGBLightning_h
#define RGBLightning_h

#include "Arduino.h"
#include "Math.h"

class RGBLightning
{
  public:
    /* Writes the given color at the LEDs */
    void WriteColor(int R, int G, int B);

    /* Makes the LEDs fade from the current color to the given one */
    void FadeColor(int R, int G, int B, int FadeTime);

  private:
    /* 
	Calculates the step for each fotogram for a given color component. 
	Is double because due to rounding the numbers, the error can grow
    */
    double FadeStep(int initialColorComp, int endColorComp, int nSteps);
};

#endif
