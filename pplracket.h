#ifndef PPLRACKET_H
#define PPLRACKET_H

class PPLRacket
{
public:
    PPLRacket(){_width=60; _height=10; _basestep=5;}

    double getCenter(){return _center;}
    void   setCenter(int center){_center = center;}
    int getWidth(){return _width;}
    int getHeight(){return _height;}
    int getBaseStep(){return _basestep;}

private:
    int _center;
    int _width;
    int _height;
    int _basestep;
};

#endif // PPLRACKET_H
