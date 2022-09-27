#include "../include/gameEntity.h"


int Agent::TotalnumberOfAgent = 0;
int WeedCrop::TotalnumberOfCrops = 0;

WeedCrop::WeedCrop(int date)
{
    x = rand()%1000 + (rand()%100)/100;
    y = rand()%1000 + (rand()%100)/100;
    issuedDate = date;
    obtainedDate = -1;
    obtained = false;
    
    

    TotalnumberOfCrops++;
}

WeedCrop::~WeedCrop()
{

    TotalnumberOfCrops--;
    
}

Agent::Agent(bool randompos,double v_input , double Tr_input)
{
    if(randompos)
    {
        x = rand()%(BORDERSIZE-1) + (rand()%100)/100;
        y = rand()%(BORDERSIZE-1) + (rand()%100)/100;
    }
    else
    {
        x=500.0;
        y=500.0;
    }

  
    theta = ((rand()%360)*M_PI)/(180.0);
    if(theta > M_PI)
    {
        theta -=2*M_PI;
    }
    if(theta < -M_PI)
    {
        theta +=2*M_PI;
    }


    TotalnumberOfAgent++;
    Tr = Tr_input;
    v = v_input;
    id = TotalnumberOfAgent;

}



Agent::Agent(double x_input, double y_input, double v_input , double Tr_input )
{
    
    if( isPosOkay(x_input,y_input)==Border::ok)
    {
        x = x_input;
        y = y_input;
    }
    else
    {
        x = rand()%(BORDERSIZE-1) + (rand()%100)/100;
        y = rand()%(BORDERSIZE-1) + (rand()%100)/100;
    }
    TotalnumberOfAgent++;
    Tr = std::fabs(Tr_input);
    v = std::fabs(v_input);
    id = TotalnumberOfAgent;

}

Border Agent::isPosOkay(double x, double y)
{
    if( x > 0.0 && x < BORDERSIZE && y > 0.0 && y < BORDERSIZE )
    {
        return Border::ok;
    }
    else if( x <0.0)
    {
        if(y > 0.0 && y < BORDERSIZE)
        {
            return Border::O;
        }
        if(y < 0.0)
        {
            return Border::SO;
        }
        if(y > BORDERSIZE)
        {
            return Border::NO;
        }

    }
    else if( x > BORDERSIZE)
    {
        if(y > 0.0 && y < BORDERSIZE)
        {
            return Border::E;
        }
        if(y < 0.0)
        {
            return Border::SE;
        }
        if(y > BORDERSIZE)
        {
            return Border::NE;
        }
    }
    else if( y < 0.0)
    {

        return Border::S;

    }
    else if( y > BORDERSIZE)
    {
        return Border::N;
    }
    return Border::UNDEF;
}

void Agent::updatePos(double dt,double degRange)
{   
    int degRangeint = 1000*degRange;
    bool sgn = rand()%2;
    int thetaRandint = rand()%degRangeint;
    double thetaRand = ((((double)(thetaRandint))*(M_PI))/(1000.0*180.0));
    if(sgn == true)
    {
        thetaRand=-thetaRand;
    }
    double thetaTemp = thetaRand + theta;
    if(thetaTemp > M_PI)
    {
        thetaTemp -=2*M_PI;
    }
    if(thetaTemp < -M_PI)
    {
        thetaTemp +=2*M_PI;
    }
    double xtemp =  x+(v/3.6)*dt*cos(thetaTemp);
    double ytemp =  y+(v/3.6)*dt*sin(thetaTemp);
    if(isPosOkay(xtemp,ytemp)==Border::ok)
    {
        theta = thetaTemp;
        x = xtemp;
        y = ytemp;

    }
    else
    {
        theta += M_PI;
        if(theta > M_PI)
        {
            theta -=2*M_PI;
        }
        if(theta < -M_PI)
        {
            theta+=2*M_PI;
        }
        x =  x+(v/3.6)*dt*cos(theta);
        y =  y+(v/3.6)*dt*sin(theta);
        
    }
    if(isPosOkay(x,y)!=Border::ok)
    {
        x = BORDERSIZE/2;
        y = BORDERSIZE/2;
        theta = 0.0;
    }
    

}

Agent::~Agent()
{

    TotalnumberOfAgent--;
    
}