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
#define BORDERSIZE 3162


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
        long long int issuedDate;
        long long int obtainedDate;
        bool obtained;
    public:
        WeedCrop(long long int date);
        ~WeedCrop();
        static int TotalnumberOfCrops;
        double getX(void){return x;};
        double getY(void){return y;};
        void acquireCrop(long long int date){obtainedDate=date; obtained = true;};
        long long int getDateIssued(void){return issuedDate;};
        long long int getDateObtained(void){return obtainedDate;};
        bool getObtainedState(void){return obtained;}
        double getSearchRectangleBasePointX(double theta) {return x*cos(theta) + y*sin(theta);};
        double getSearchRectangleBasePointY(double theta) {return y*cos(theta) - x*sin(theta) ;};

};




class Agent
{
    private:
        double x;
        double y;
        double lastx;
        double lasty;
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
        double getVmeterPerSecond(void){ return v/3.6;};
        double getTheta(void){return theta;}
        double getSearchRectangleBasePointX() {return lastx*cos(theta) + lasty*sin(theta);};
        double getSearchRectangleBasePointY() {return lasty*cos(theta) - lastx*sin(theta) - Tr;};
        
        
};



