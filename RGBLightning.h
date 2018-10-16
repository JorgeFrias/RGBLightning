/*
  RGBLightning.h - Library for setting smoothly RGB non directionable led strips.
  Created by Jorge Frias, September 29, 2018.
*/


#ifndef RGBLightning_h
#define RGBLightning_h

#include "Arduino.h"
#include "math.h"

class RGBLightning
{
  public:
    /** Class constructor */
    RGBLightning(int pinRed, int pinGreen, int pinBlue);

    /** To be called in setup() */
    void begin();

    /**
     * Writes the given color at the LEDs inmediately 
     */
    void SetColor(int R, int G, int B);

    /** Makes the LEDs fade from the current color to the given one */
    void FadeColor(int R, int G, int B, int FadeTime);

  private:
    uint8_t _PinRed;
    uint8_t _PinGreen;
    uint8_t _PinBlue;

    int _Red;    		        // Current red component
    int _Green;			        // Current green component
    int _Blue;			        // Current blue component

    int _fadeStepsPerSecond;    // Fade transition fps


    /** Writes the given color at the LEDs */
    void WriteColor(int R, int G, int B);

    /** 
	 * Calculates the step for each fotogram for a given color component. 
	 * Is double because due to rounding the numbers, the error can grow
     */
    double FadeStep(int initialColorComp, int endColorComp, int nSteps);
};

#endif
