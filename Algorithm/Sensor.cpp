//
//  Sensor.cpp
//  Algorithm
//
//  Created by Cyril Trosset on 16/11/2013.
//  Copyright (c) 2013 Cyril Trosset. All rights reserved.
//

#include "Sensor.h"

Sensor::Sensor(double x,double y, double cost):_x(x),_y(y),_cost(cost){};
Sensor::~Sensor(){};

double Sensor::getCost()
{
    return _cost;
}
double Sensor::x()
{
    return _x;
}
double Sensor::y()
{
    return _y;
}
