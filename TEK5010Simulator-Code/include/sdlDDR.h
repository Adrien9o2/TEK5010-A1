#ifndef SDLDDRH
#define SDLDDRH

#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/*! \file sdlDDR.h
    \brief Define input structure generated in main by user
    
  
*/

typedef struct _mainSdlInput
{
    int N; //Number of Agents
    int Nc; // Number of crops
    double v; // Speed of Agents
    double Tr; // Detection Radius
    int timeMult; // (Visual) Simulation time multiplier
    bool keepRatioTime; // Option to Keep Visual simulation synchronized with realTime*timeMult
    bool renderImage; // Option to toggle Visualization, exit sim by closing window
    unsigned int numberOfCropsCollectedBeforeStop; //In case of no visualization, the number of Crops to obtained before stopping simulation
} mainSdlInput;



void mainsdl(mainSdlInput input);
void SDL_ExitWithError(const char *message);



#endif
