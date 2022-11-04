#include "../include/grid.h"

/*! \file grid.cpp
    \brief Implement Grid class, wich contains all agents, crops,
    provide update fonctions, and utility for visualization
    
  
*/

Grid::Grid(int numberOfAgents,int numberOfWeedCrop,double Vit, double Tr)
{
    //INITIALIZATION
    for(int i = 0; i<numberOfAgents; i++)
    {
        agents.push_back(Agent(true,(double)Vit,(double)Tr));

    }
    for(int i = 0; i<numberOfWeedCrop; i++)
    {
        weedCrops.push_back(WeedCrop(0));
    }
    ConvertPos();//used for visualization
}

void Grid::ConvertPos() // Convert x/y position to picture position for visualization
{
    if(!weedPos.empty())//empty the vector wich contains previous position
        weedPos.clear();
    if(!agentPos.empty())    
        agentPos.clear();
    for( Agent agent: agents)
    {
        double x = (double)((double)(agent.getX())*WINDOW_SIZE)/BORDERSIZE-AGENTWEEDWIDHT/2; 
        double y = 720-(double)((double)(agent.getY())*WINDOW_SIZE)/BORDERSIZE-AGENTHEIGHT/2;
        int xint = x;
        int yint = y;
        pos toAddPos  {xint,yint};
        toAddPos.x = std::min( std::max(toAddPos.x,0), WINDOW_SIZE); //ensuring position stay in window
        toAddPos.y = std::min( std::max(toAddPos.y,0), WINDOW_SIZE);
        agentPos.push_back(toAddPos);
    }
    for( WeedCrop weed: weedCrops)
    {
        double x = (double)(((double)weed.getX())*WINDOW_SIZE)/BORDERSIZE-AGENTWEEDWIDHT/2;
        double y = 720-(double)((double)(weed.getY())*WINDOW_SIZE)/BORDERSIZE-AGENTHEIGHT/2;
        int xint = x;
        int yint = y;
        pos toAddPos  {xint,yint};
        toAddPos.x = std::min( std::max(toAddPos.x,0), WINDOW_SIZE); //ensuring position stay in window
        toAddPos.y = std::min( std::max(toAddPos.y,0), WINDOW_SIZE);
        weedPos.push_back(toAddPos);
    }

}

void Grid::updateAgents(long long int date, double dt, double degRange ) //Perform one simulation step
{
    int toadd = 0; // Number of Crops to add at the end of the update
    for(auto it = std::begin(agents);it!=std::end(agents);it++)
    {
        it->updatePos(dt,degRange); // Update position of agent it according movement policy
            
        if( !weedCrops.empty()) 
        {

            for( auto it2 = std::begin(weedCrops); it2!=std::end(weedCrops); it2++) //Check if weedcrop it2 is near agent it1
            {
                    if( !weedCrops.empty())
                    {

                
                        double dist = sqrt(pow((it->getX()-it2->getX()),2)+pow((it->getY()-it2->getY()),2));
                        double xbasepoint = it->getSearchRectangleBasePointX();
                        double ybasepoint = it->getSearchRectangleBasePointY();
                        double theta = it->getTheta();
                        double cropx = it2->getSearchRectangleBasePointX(theta);
                        double cropy = it2->getSearchRectangleBasePointY(theta);
                        double v = it->getVmeterPerSecond();
                        double Tr = it->getTr();
                        bool checkRectangle = false;
                        if( cropx > xbasepoint && cropx < xbasepoint + dt*v )
                        {
                            if(cropy > ybasepoint && cropy < ybasepoint + Tr )
                            {
                                checkRectangle = true;
                            }
                        }
                        if( dist < Tr || checkRectangle ) // if dist < Tr => Remove Crops it2
                        {

                                it2->acquireCrop(date); //Register acquired date to calculate performances
                                obtainedWeedCrops.push_back(*it2);
                                weedCrops.erase(it2);
                                toadd++;
                                if(it2 != std::begin(weedCrops))
                                    it2--;
                                if(weedCrops.empty())
                                {
                                    break;
                                }

                                
                            
                        } 
                    }
            }
        }

    }
    for(int i = 0; i< toadd; i++)
    {
        weedCrops.push_back(WeedCrop(date)); // Add as many crops as found
    }

}

Grid::~Grid()
{
}