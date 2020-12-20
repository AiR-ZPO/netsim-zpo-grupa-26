//
// Created by Mateusz on 2020-12-17.
//

#ifndef NET_SIMULATION_PACKAGE_HPP
#define NET_SIMULATION_PACKAGE_HPP
#include "types.hpp"

#include <set>

class Package{
public:
    Package();
    Package(ElementID id) : _id(id) {};
    Package(Package&&) = default;
    Package& operator = (Package&&) = default;
    ElementID get_id() const { return _id; }

private:
    ElementID _id;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
};

#endif //NET_SIMULATION_PACKAGE_HPP

