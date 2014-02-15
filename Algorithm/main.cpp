//
//  main.cpp
//  Algorithm
//
//  Created by Cyril Trosset on 16/11/2013.
//  Copyright (c) 2013 Cyril Trosset. All rights reserved.
//

#include <iostream>
#include <vector>
#include <dirent.h>
#include <sstream>
#include <string>
#include "Target.h"

#define PATH "/Users/cyriltrosset/Dropbox/IIT/CS 430/Algorithm/Algorithm/conf.txt"

using namespace std;

vector<string> split(const string &s, char delim); //Split a string with a delimiter

int main(int argc, const char * argv[])
{
    
    //OPEN THE CONF FILE
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    
    fp = fopen(PATH, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    int iLine = 0;
    
    vector<Sensor> sensors;
    vector<Target> targets;
    
    //READ LINE BY LINE
    while ((read = getline(&line, &len, fp)) != -1) {
        
        //REMOVE USEFUL CHAR
        string lineString = line;
        lineString.erase(remove(lineString.begin(), lineString.end(), '(' ), lineString.end() );
        lineString.erase(remove(lineString.begin(), lineString.end(), ')' ), lineString.end() );
        lineString.erase(remove(lineString.begin(), lineString.end(), '\n' ), lineString.end() );
        
        if(iLine==0) //FILLING SENSORS
        {
            vector<string> values = split(lineString, ',');
            for(int i=0;i<values.size();i+=3)//Sensor by sensor
            {
                //Add new sensor in vector
                Sensor sensor = Sensor(::atof(values[i].c_str()),::atof(values[i+1].c_str()),::atof(values[i+2].c_str()));
                sensors.push_back(sensor);
                
                int index = (int)sensors.size()-1;
                for(int j=index-1;j>=0;j--)//Add the sensor ordered
                {
                    if(sensors[j].x()>sensors[index].x())
                    {
                        swap(sensors[j],sensors[index]);
                        index = j;
                    }
                    else
                        break;
                }
            }
        }
        else if(iLine==1) //FILLING TARGETS
        {
            vector<string> values = split(lineString, ',');
            for(int i=0;i<values.size();i+=2)//Target by target
            {
                //Add new target in vector
                Target target = Target(::atof(values[i].c_str()),::atof(values[i+1].c_str()));
                targets.push_back(target);
            }
        }
        
        iLine++;
        
    }
    
    if (line)
        free(line);
    
    //Allocate memory
    float costs[targets.size()][sensors.size()];
    Sensor* solutions[targets.size()][sensors.size()][sensors.size()];
    
    //Set the memory values to 0
    for(int i=0;i<targets.size();i++)
    {
        for(int j=0;j<sensors.size();j++)
        {
            for(int k=0;k<sensors.size();k++)
                solutions[i][j][k] = 0;
        }
    }
    
    //Main function
    for(int i=0;i<targets.size();i++)
    {
        for(int j=0;j<sensors.size();j++)
        {
            if(sensors[j].x()-targets[i].x()>1) //Stop testing if sensors are too far
                break;
            
            if(targets[i].canBeSenseBy(&sensors[j])) //The target is in sensor's range
            {
                if(i==0)//First case
                {
                    int k=0;
                    while(solutions[i][j][k]!=0)
                    {
                        cout << solutions[i][j][k];
                        k++;
                    }
                    
                    solutions[i][j][k]=&sensors[j];
                    costs[i][j] = sensors[j].getCost();
                }
                else//Not first case
                {
                    /*GET MINIMUM COVER START*/
                    vector<Sensor*> currentCover;
                    float currentCost = 0;
                    vector<Sensor*> minimumCover;
                    float minimumCost = 999999999;
                    
                    // loop through all solutions for i-1
                    for(int m=0;m<sensors.size();m++)
                    {
                        if(solutions[i-1][m][0]!=0)
                        {
                            currentCover.clear();
                            currentCost = costs[i-1][m];
                            int k=0;
                            bool found = false;
                            while(1)
                            {
                                if(solutions[i-1][m][k]==0)
                                    break;
                                
                                if(&sensors[j]==solutions[i-1][m][k])
                                    found=true;
                                
                                // add solutions to currentCover
                                currentCover.push_back(solutions[i-1][m][k]);
                                
                                k++;
                            }
                            // if current sensor not found in solution, add it
                            if(!found)
                            {
                                currentCost+=sensors[j].getCost();
                                currentCover.push_back(&sensors[j]);
                            }
                            // maintain minimumCost
                            if(currentCost<minimumCost)
                            {
                                minimumCost = currentCost;
                                minimumCover=currentCover;
                            }
                        }
                    }
                    /* GET MINIMUM COVER END */
                    
                    int k=0;
                    while(solutions[i][j][k]!=0)
                        k++;
                    
                    for(int l=0;l<minimumCover.size();l++)
                    {
                        solutions[i][j][k++] = minimumCover[l];
                    }
                    //solutions[i][j][k] = &sensors[j];
                    
                    costs[i][j] = minimumCost;
                }
            }
            else
            {
                solutions[i][j][0] = 0;
                costs[i][j] = 0;
            }
            
        }
    }
    
    vector<Sensor*> minSet;
    float minCost = 9999999999;
    
    //Looking for the lowest cost
    for(int i=0;i<sensors.size();i++)
    {
        if(costs[targets.size()-1][i]<minCost && costs[targets.size()-1][i]>=0.000001)
        {
            minCost=costs[targets.size()-1][i];
            minSet.clear();
            
            int k=0;
            while(solutions[targets.size()-1][i][k]!=0)
            {
                minSet.push_back(solutions[targets.size()-1][i][k]);
                k++;
            }
        }
    }
    
    //Output
    cout << "Minimum cost : " << minCost << endl << endl;
    cout << "Sensors : " << endl;
    for(int i=0;i<minSet.size();i++)
        cout << "(" << minSet[i]->x() << "," << minSet[i]->y() << ") cost : " << minSet[i]->getCost() << endl;
    
    return 0;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
