//
// Created by Pawel on 17.12.2020.
//

#ifndef NET_SIMULATION_TYPES_HPP
#define NET_SIMULATION_TYPES_HPP
class ElementID {
public:
    ElementID() = default;
    ElementID(int id) : _id(id) {}

    int get_id() const { return _id; }

private:
    int _id;
};
#endif //NET_SIMULATION_TYPES_HPP

//aliasy