//
// Created by Pawel on 17.12.2020.
//

#ifndef NET_SIMULATION_FACTORY_HPP
#define NET_SIMULATION_FACTORY_HPP
#include "nodes.hpp"
#include <vector>
#include <utility>
#include <list>
#include "types.hpp"
#include <algorithm>
/*szablon klasy NodeCollection
klasa Factory
funkcje do zapisu i odczytu struktury fabryki z pliku
*/


class Factory
{
private:
    NodeCollection<Ramp> _ramps_list;
    NodeCollection<Worker> _workers_list;
    NodeCollection<Storehouse> _storehouses_list;
public:
    Factory(T node_list): _node_list(node_list) {};

    bool is_consistent(); // TODO: Do sprawdzenia!
    void do_deliveries(Time t);
    void do_package_passing();
    void do_work(Time t);
    void remove_receiver(collection: NodeCollection<Node>&, id: ElementID);

    void add_ramp(Ramp&&);
    void remove_ramp(ElementID id);
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id);
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id);
    NodeCollection<Ramp>::const_iterator ramp_cbegin() { return _ramps_list.cbegin; }
    NodeCollection<Ramp>::const_iterator ramp_cend() { return _ramps_list.cend(); }

    void add_worker(Worker&&) {};
    void remove_worker(ElementID id);
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) {};
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id);
    NodeCollection<Worker>::const_iterator worker_cbegin() { return _workers_list.cbegin(); }
    NodeCollection<Worker>::const_iterator worker_cend() { return _workers_list.cend; }

    void add_storehouse(Storehouse&&);
    void remove_storehouse(ElementID id);
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id);
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id);
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() { return _storehouses_list.cbegin(); }
    NodeCollection<Storehouse>::const_iterator storehouse_cend() { return _storehouses_list.cend(); }
};


template <class T>
class NodeCollection
{

private:
    container_t _node_list;
public:
    using container_t = typename std::vector<T>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    NodeCollection(container_t node_list) : _node_list(node_list) {};

    const_iterator cbegin() const { return _node_list.cbegin(); }
    const_iterator cend() const { return _node_list.cend(); }
    iterator begin() const { return _node_list.begin(); }
    iterator end() const { return _node_list.end(); }


    void add(T&& node) { _node_list.emplace_back(std::move(node)); }

    void remove_by_id(ElementID id) {}
    iterator find_by_id(ElementID id) {}
    const_iterator find_by_id(ElementID id) {}
};


iterator find_by_id(ElementID id)
{
    return std::find_if(std::begin(_node_list), std::end(_node_list), [id](auto& i) { return (i.get_id().get_id() == id.get_id()); } );
}


const_iterator find_by_id(ElementID id)
{
    return std::find_if(std::begin(_node_list), std::end(_node_list), [id](const auto& i) { return (i.get_id().get_id() == id.get_id()); } );
}


void remove_by_id(ElementID id)
{
    NodeCollection::const_iterator it = find_by_id(id);
    if (it != _node_list.end())
    {
        _node_list.erase(it);
    }

}
#endif //NET_SIMULATION_FACTORY_HPP
