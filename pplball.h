#ifndef PPLBALL_H
#define PPLBALL_H

#include <cstdlib>
#include <QTime>
#include <ctime>
class PPLBall
{
public:
    PPLBall()
    {
        srand(time(0));
        _xstep = 0.1*(rand() % 50)*(((rand() % 10)>=5) ? 1 : (-1));
        _ystep = 0.5*(((rand() % 10)>=5) ? 1 : (-1));
        _radius = 10.0;
        _basestep = 0.5;
        isDown = _ystep>0 ? true : false;
        isRight = _xstep>0 ? true : false;
    }

    void setX(double x){_x = x;}
    void setY(double y){_y = y;}
    void setXStep(double xs){_xstep = xs;}
    void setYStep(double ys){_ystep = ys;}

    double getX(){return _x;}
    double getY(){return _y;}
    double getXStep(){return _xstep;}
    double getYStep(){return _ystep;}
    double getRadius(){return _radius;}
    double getBaseStep(){return _basestep;}

    bool isDown;
    bool isRight;

private:
    double _x;
    double _y;
    double _xstep;
    double _ystep;
    double _radius;
    double _basestep;

};


#endif // PPLBALL_H
