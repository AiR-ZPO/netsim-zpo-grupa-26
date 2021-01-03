//
// Created by Pawel on 17.12.2020.
//

#ifndef NET_SIMULATION_TYPES_HPP
#define NET_SIMULATION_TYPES_HPP

#include<functional>
#include<iostream>

typedef int ElementID;

typedef int TimeOffset;

typedef int Time;

typedef std::function<double()> ProbabilityGenerator;
#endif //NET_SIMULATION_TYPES_HPP

//aliasy