//
//  Target.h
//  Algorithm
//
//  Created by Cyril Trosset on 16/11/2013.
//  Copyright (c) 2013 Cyril Trosset. All rights reserved.
//

#ifndef __Algorithm__Target__
#define __Algorithm__Target__

#include <iostream>
#include <vector>
#include "Sensor.h"

#endif /* defined(__Algorithm__Target__) */

class Target
{
public:
    Target(double x,double y);
    ~Target();
    
    double x();
    double y();
    
    bool canBeSenseBy(Sensor *sensor);
    
private:
    double _x;
    double _y;
    
};
