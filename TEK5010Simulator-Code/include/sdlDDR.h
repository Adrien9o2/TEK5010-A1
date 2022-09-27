#ifndef SDLDDRH
#define SDLDDRH

#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


typedef struct _mainSdlInput
{
    int N;
    int Nc;
    double v;
    double Tr;
    int timeMult;
    bool keepRatioTime;
    bool renderImage;
    unsigned int numberOfCropsCollectedBeforeStop;
} mainSdlInput;



void mainsdl(mainSdlInput input);
void SDL_ExitWithError(const char *message);



#endif
