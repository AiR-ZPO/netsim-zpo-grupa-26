//
// Created by Pawel on 17.12.2020.
//
#include "package.hpp"

std::set<ElementID> Package::assigned_IDs;
std::set<ElementID> Package::freed_IDs;

Package::Package(){
    if (not freed_IDs.empty()){
        _id = ElementID(*freed_IDs.begin());
        freed_IDs.erase(freed_IDs.begin());
    } else if (not assigned_IDs.empty()){
        _id = ElementID(assigned_IDs.end()->get_id() + 1);
    }
    else{
        _id = ElementID(1);
    }
}