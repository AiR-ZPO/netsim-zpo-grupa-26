//
// Created by Pawel on 17.12.2020.
//

#include "factory.hpp"
#include <vector>
#include <utility>

enum class NodeColor { UNVISITED, VISITED, VERIFIED };



void Factory::do_deliveries(Time t)
{
    for(auto i: _ramps_list)
    {
        i.deliver_goods(t);
    }
}
void Factory::do_work(int t)
{
    for(auto i: _workers_list)
    {
        i.do_work(t);
    }
}
void Factory::do_package_passing()
{
    for(auto i: _workers_list)
    {
        i.send_package();
    }
}

NodeCollection<Ramp>::iterator Factory::find_ramp_by_id(ElementID id)
{
    return std::find_if(std::begin(_storehouses_list), std::end(_storehouses_list), [id](auto& i) { return (i.get_id().get_id() == id.get_id()); } );
}
NodeCollection<Ramp>::const_iterator Factory::find_ramp_by_id(ElementID id)
{
    return std::find_if(std::begin(_ramp_list), std::end(_ramp_list), [id](const auto& i) { return (i.get_id().get_id() == id.get_id()); } );
}


NodeCollection<Worker>::iterator Factory::find_worker_by_id(ElementID id)
{
    return std::find_if(std::begin(_storehouses_list), std::end(_storehouses_list), [id](auto& i) { return (i.get_id().get_id() == id.get_id()); } );
}
NodeCollection<<Worker>::const_iterator Factory::find_worker_by_id(ElementID id)
{
    return std::find_if(std::begin(_workers_list), std::end(_workers_list), [id](const auto& i) { return (i.get_id().get_id() == id.get_id()); } );
}


NodeCollection<Storehouse>::iterator Factory::find_storehouse_by_id(ElementID id)
{
    return std::find_if(std::begin(_storehouses_list), std::end(_storehouses_list), [id](const auto& i) { return (i.get_id().get_id() == id.get_id()); } );
}
NodeCollection<Storehouse>::iterator Factory::find_storehouse_by_id(ElementID id)
{
    return std::find_if(std::begin(_storehouses_list), std::end(_storehouses_list), [id](auto& i) { return (i.get_id().get_id() == id.get_id()); } );
}
