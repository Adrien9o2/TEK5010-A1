#pragma once
#include <time.h>
#include <cstdlib>
#include <cmath>
#include <boost/geometry.hpp>
#include <vector>

/*! \file gameEntity.h
    \brief Define Crops and Agents CLASS
    
  
*/
#define DEFAULT_SPEED 10.0
#define DEFAULT_TR 5.0
#define BORDERSIZE 1000


typedef enum _border
{
    ok,
    N,
    S,
    E,
    O,
    NE,
    NO,
    SE,
    SO,
    UNDEF
}Border;


class WeedCrop
{
    private:
        double x;
        double y;
        int issuedDate;
        int obtainedDate;
        bool obtained;
    public:
        WeedCrop(int date);
        ~WeedCrop();
        static int TotalnumberOfCrops;
        double getX(void){return x;};
        double getY(void){return y;};
        void acquireCrop(int date){obtainedDate=date; obtained = true;};
        int getDateIssued(void){return issuedDate;};
        int getDateObtained(void){return obtainedDate;};
        bool getObtainedState(void){return obtained;}

};




class Agent
{
    private:
        double x;
        double y;
        double theta;
        double Tr;
        double v;
        int id;
        
    public:
        Agent(bool randompos,double v_input = DEFAULT_SPEED , double Tr_input = DEFAULT_TR);
        Agent(double x_input, double y_input, double v_input = DEFAULT_SPEED, double Tr_input = DEFAULT_TR );
        ~Agent();
        Border isPosOkay(double x, double y);
        static int TotalnumberOfAgent;
        void updatePos(double dt, double degRange =5.0);
        double getX(void){return x;};
        double getY(void){return y;};
        double getTr(void){return Tr;};
        
        
};



