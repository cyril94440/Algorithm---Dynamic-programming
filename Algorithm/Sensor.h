//
//  Sensor.h
//  Algorithm
//
//  Created by Cyril Trosset on 16/11/2013.
//  Copyright (c) 2013 Cyril Trosset. All rights reserved.
//

#ifndef __Algorithm__Sensor__
#define __Algorithm__Sensor__

#include <iostream>

#endif /* defined(__Algorithm__Sensor__) */

class Sensor
{
public:
    Sensor(double x,double y, double cost);
    ~Sensor();
    
    double getCost();
    
    double x();
    double y();
    
private:
    double _x;
    double _y;
    double _cost;
};
