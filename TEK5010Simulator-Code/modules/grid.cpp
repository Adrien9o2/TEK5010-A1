#include "../include/grid.h"

Grid::Grid(int numberOfAgents,int numberOfWeedCrop,double Vit, double Tr)
{
    for(int i = 0; i<numberOfAgents; i++)
    {
        agents.push_back(Agent(true,(double)Vit,(double)Tr));

    }
    for(int i = 0; i<numberOfWeedCrop; i++)
    {
        weedCrops.push_back(WeedCrop(0));
    }
    ConvertPos();
}

void Grid::ConvertPos()
{
    if(!weedPos.empty())
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
        toAddPos.x = std::min( std::max(toAddPos.x,0), WINDOW_SIZE);
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
        toAddPos.x = std::min( std::max(toAddPos.x,0), WINDOW_SIZE);
        toAddPos.y = std::min( std::max(toAddPos.y,0), WINDOW_SIZE);
        weedPos.push_back(toAddPos);
    }

}

void Grid::updateAgents(int date, double dt, double degRange )
{
    int toadd = 0;
    for(auto it = std::begin(agents);it!=std::end(agents);it++)
    {
        it->updatePos(dt,degRange);
            
        if( !weedCrops.empty())
        {

            for( auto it2 = std::begin(weedCrops); it2!=std::end(weedCrops); it2++)
            {
                    if( !weedCrops.empty())
                    {

                
                        double dist = sqrt(pow((it->getX()-it2->getX()),2)+pow((it->getY()-it2->getY()),2));
                        if( dist < it->getTr())
                        {

                                it2->acquireCrop(date);
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
        weedCrops.push_back(WeedCrop(date));
    }

}

Grid::~Grid()
{
}