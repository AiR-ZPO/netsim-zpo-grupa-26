//
// Created by Pawel on 17.12.2020.
//

#ifndef NET_SIMULATION_HELPERS_HPP
#define NET_SIMULATION_HELPERS_HPP
#include <functional>
#include <random>

#include "types.hpp"

extern std::random_device rd;
extern std::mt19937 rng;

extern double default_probability_generator();

extern ProbabilityGenerator probability_generator;

#endif //NET_SIMULATION_HELPERS_HPP

//pomocnicze obiekty i funkcje globalne (np. generator liczb losowych)