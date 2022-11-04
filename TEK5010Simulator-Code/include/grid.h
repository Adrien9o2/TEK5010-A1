#pragma once
#include "gameEntity.h"
#include <algorithm>


/*! \file grid.h
    \brief Define Grid class, wich contains all agents, crops,
    provide update fonctions, and utility for visualization
    
  
*/


#define WINDOW_SIZE 720
#define AGENTWEEDWIDHT 16
#define AGENTHEIGHT 9
#define WEEDHEIGHT 19
 
typedef struct _pos
{
    int x;
    int y;
}pos;

class Grid
{
    private:
        
        std::vector<WeedCrop> weedCrops;
        int numberOfAgents;
        int numberOfWeedCrop;        
    public:
        std::vector<pos> agentPos;
        std::vector<Agent> agents;
        std::vector<pos> weedPos;
        std::vector<WeedCrop> obtainedWeedCrops;
        Grid(int numberOfAgents=1,int numberOfWeedCrop=1, double Vit= 10.0, double Tr = 5.0);
        ~Grid();
        void updateAgents(long long int date, double dt, double degRange = 5.0);
        void ConvertPos();
};


