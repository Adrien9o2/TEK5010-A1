#include "../include/sdlDDR.h"
#include <iostream>
#include <vector>
#include <algorithm>


/*! \file main.cpp
    \brief Acquire user inputs and launch simulation
    
  
*/


mainSdlInput input = {1,1,5.0,10.0,1,true,true,100};


int nagentGenerator()
{
    static int i = 1;
    static int count = 4385;
    if(i++ > 20)
        count = 4385;
    count = count*1.1;
    return count;
}


int main(int argc, char* argv[]) {



	
   
	
	
    printf("\n");
    printf("*-------------------------------------------------------------* \n");
    printf("Welcome To Particle Simulator - TEK5010 - Assignement 1 \n");
    printf("*-------------------------------------------------------------* \n");
    printf(" \n");
    printf(" \n");
    printf(" \n");
    // printf("Enter number of Agents (int) : \n");
    // std::cin>>(input.N);
    printf("Enter number of Crops (int) : \n");
    std::cin>>(input.Nc);
    printf("\n \n Enter radius Tr (double) : \n");
    std::cin>>(input.Tr);
    printf("\n  Enter Agents'speed km/h (double) : \n");
    std::cin>>(input.v);
    printf("\n render image (bool) : \n");
    std::cin>>(input.renderImage);
    if( input.renderImage == false)
    {
        printf("Wait for how many collected Crop (int) ? \n\n");
        std::cin>>(input.numberOfCropsCollectedBeforeStop);
    }
    else
    {
        printf("\n \n Enter Simulation Time multiplier (int) : \n");
        std::cin>>(input.timeMult);
        printf("\n \n Skip frames if slower than realtime*time_multiplier (bool) : \n");
        std::cin>>(input.keepRatioTime);
    }

    





    


    

   

    /* ------------------------- */

            // SESSION SDL
   std::vector<int> tab (20);
   std::generate (tab.begin(), tab.end(), nagentGenerator);
   for(auto it : tab)
   {
        input.N = it;
        mainsdl(input);
   }
   
   /* ------------------------- */

    SDL_Quit();
	return EXIT_SUCCESS;
}
