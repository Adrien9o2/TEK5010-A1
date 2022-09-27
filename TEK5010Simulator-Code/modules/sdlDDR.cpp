#include "../include/sdlDDR.h"
#include "../include/gameEntity.h"
#include "../include/grid.h"
#include "time.h"
#include <iostream>


#define REFRESHTIME 16
#define MAX_SKIP 10


/*
int main(int argc, char** argv)
{
    mainsdl(0);
}
*/


void mainsdl(mainSdlInput input)
{

    srand(time(NULL));
    Grid agrid(input.N,input.Nc);
     

    

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;



    float dt = 1.0;
    int dt_int_ms = 1000;
    int delay_sim = (dt_int_ms)/input.timeMult;
    int simTime = 0;


    
    if(input.renderImage)
    {
        float refreshtimef = REFRESHTIME;
        int refreshtime = refreshtimef;
        int ticks1;
        int ticks2;
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
            SDL_ExitWithError("Initialisation SDL");
        IMG_Init(IMG_INIT_PNG);
        SDL_Surface *icon = IMG_Load("icon.png");
        SDL_Surface * imagebg = IMG_Load("backg.png");
        SDL_Surface * agent_surface = IMG_Load("saucer.png");
        SDL_Surface * weedcrop_surface = IMG_Load("weedcrop.png");

    



        //Création fenêtre
        if (SDL_CreateWindowAndRenderer(WINDOW_SIZE, WINDOW_SIZE, 0, &window, &renderer) != 0)
            SDL_ExitWithError("Creation fenetre et rendu echouee");



        SDL_SetWindowTitle(window, "TEK5010 - Assignement 1");
        SDL_SetWindowIcon(window, icon);





        SDL_Texture * texturebg = SDL_CreateTextureFromSurface(renderer, imagebg);
        SDL_Texture * textureAgent = SDL_CreateTextureFromSurface(renderer, agent_surface);
        SDL_Texture * textureWeedCrop = SDL_CreateTextureFromSurface(renderer, weedcrop_surface);


        

        

        int reftime_since_begin = SDL_GetTicks();
        int reftime = SDL_GetTicks();
        int reftime2 = SDL_GetTicks();
        SDL_bool program_launched = SDL_TRUE;
        SDL_RenderCopy(renderer, texturebg, NULL, NULL);
        int render = 0;
        bool nowait = false;        
        


            //Lancement SDL


        while (program_launched)
        {
            ticks1 = SDL_GetTicks() +refreshtime;
            
            
        

            

            SDL_Event event;
            if (SDL_PollEvent(&event))
            {
                switch (event.type)
                {

                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;

                
                default:
                    break;
                }
            }

            reftime2 = SDL_GetTicks();
            if( reftime2-reftime > delay_sim)
            {
            
                agrid.updateAgents((simTime+dt_int_ms),dt);
                simTime+=dt_int_ms;
                agrid.ConvertPos();
                SDL_Rect workingRect {0,0,AGENTWEEDWIDHT,AGENTHEIGHT};
                if(input.keepRatioTime && render < MAX_SKIP && reftime2-reftime_since_begin > ((float)((float)delay_sim*((float)(simTime/dt_int_ms)))) + 4*delay_sim )
                {
                    render += 1;
                    std::cout << "Time steps :" <<  (reftime2-reftime_since_begin)/delay_sim << ", " << simTime/dt_int_ms << std::endl;
            
                }
                else if ( render >= MAX_SKIP || render==0)
                {
                    
                    SDL_RenderCopy(renderer, texturebg, NULL, NULL);
                    for( auto it : agrid.agentPos)
                    {
                        workingRect.x = it.x;
                        workingRect.y = it.y;
                        SDL_RenderCopy(renderer,textureAgent,NULL,&workingRect);
                        
                    }
                    workingRect = {0,0,AGENTWEEDWIDHT,WEEDHEIGHT};
                    for( auto it : agrid.weedPos)
                    {
                        workingRect.x = it.x;
                        workingRect.y = it.y;
                        SDL_RenderCopy(renderer,textureWeedCrop,NULL,&workingRect);
                        
                    }
                    if(render > MAX_SKIP)
                    {
                        nowait = true;
                        render = 0;
                    }
                    else
                    {
                        render = 0;
                        nowait = false;
                    }
                    
                    
                }
                

                reftime = SDL_GetTicks();
                reftime2 = SDL_GetTicks();
            }



        

        
            ticks2 = SDL_GetTicks();


            
            if(ticks2 < ticks1 && render==0 && nowait==false)
            {
                if(reftime2-reftime < (delay_sim - (ticks1-ticks2)) )
                {
                    SDL_Delay(ticks1-ticks2);
                } 
                else if ( input.keepRatioTime == false)
                {
                    SDL_Delay(ticks1-ticks2);
                }
            }







            if(render==0)
            {
                SDL_RenderPresent(renderer);
            }
                
            
        

        
        }
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_FreeSurface(icon);
        SDL_FreeSurface(agent_surface);
        SDL_FreeSurface(weedcrop_surface);

        IMG_Quit();

    }
    else
    {
        while(agrid.obtainedWeedCrops.size() < input.numberOfCropsCollectedBeforeStop)
        {
            agrid.updateAgents((simTime+dt_int_ms),dt);
            simTime+=dt_int_ms;

        }

    }
    

    std::cout<<"--------Simulation END--------\n"<<std::endl;

    std::cout<<"Results : "<<std::endl;
    std::cout<<"Simulation time : "<<simTime/1000.0<<" s"<<std::endl;
    std::cout<<"NumberOfCropsFound : "<<agrid.obtainedWeedCrops.size()<<std::endl;
    double avg = 0.0;
    double variance = 0.0;
    if(agrid.obtainedWeedCrops.size() !=0)
    {
        for(auto it : agrid.obtainedWeedCrops)
        {
            avg+=(it.getDateObtained()-it.getDateIssued())/1000.0;
        }
        avg/=agrid.obtainedWeedCrops.size();
        for(auto it : agrid.obtainedWeedCrops)
        {
            variance+=pow(avg-(it.getDateObtained()-it.getDateIssued())/1000.0,2);
        }
        variance = sqrt(variance/agrid.obtainedWeedCrops.size());

        std::cout<<"Average Time for a crop to be found : "<<avg<<std::endl;
        std::cout<<"Asscociated Variance  : "<<variance<<std::endl;


    }



    /*------------------------------------------------------------*/


 



}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}


