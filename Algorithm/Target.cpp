//
//  Target.cpp
//  Algorithm
//
//  Created by Cyril Trosset on 16/11/2013.
//  Copyright (c) 2013 Cyril Trosset. All rights reserved.
//

#include "Target.h"
#include <math.h>

Target::Target(double x,double y):_x(x),_y(y){};
Target::~Target(){};

double Target::x()
{
    return _x;
}
double Target::y()
{
    return _y;
}



bool Target::canBeSenseBy(Sensor *sensor)
{    
    double distance = ((_x - sensor->x()) * (_x - sensor->x())) + ((_y - sensor->y()) * (_y - sensor->y()));
    distance = sqrt(distance);
    
    return distance<=1;
}