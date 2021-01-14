//
// Created by Pawel on 17.12.2020.
//

#include "factory.hpp"

#include <vector>
#include <utility>
#include <map>


enum class NodeColor { UNVISITED, VISITED, VERIFIED };

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors)
{
    if(node_colors[sender] == NodeColor::VERIFIED)
    {
        return true;
    }
    node_colors[sender] = NodeColor::VISITED;
    if (sender->receiver_preferences_.get_preferences().size() == 0)
    {
        throw std::logic_error("Nadawca nie posiada żadnego połączenia wyjściowego.");
    }

    bool another_receiver = false;
    ReceiverPreferences::preferences_t pref = sender->receiver_preferences_.get_preferences();
    for(auto [key, value]: pref)
    {
        if(key->get_receiver_type() == ReceiverType::STOREHOUSE)
        {
            another_receiver = true;
        }
        else if(key->get_receiver_type() == ReceiverType::WORKER)
        {
            IPackageReceiver* receiver_ptr = key;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if( sendrecv_ptr == sender)
            {
                continue;
            }
            another_receiver = true;
            if(node_colors[sendrecv_ptr] == NodeColor::UNVISITED)
            {
                has_reachable_storehouse(sendrecv_ptr, node_colors);
            }
        }
    }
    node_colors[sender] = NodeColor::VERIFIED;
    if(another_receiver)
    {
        return true;
    }
    else
    {
        throw std::logic_error("Nadawca nie posiada żadnego połączenia wyjściowego.");
    }

}


bool Factory::is_consistent()
{
    std::map<const PackageSender*, NodeColor> Color = {};
    for(auto& i: _ramps_list)
    {
        Color[&i] = NodeColor::UNVISITED;
    }

    for(auto& i: _workers_list)
    {
        Color[&i] = NodeColor::UNVISITED;
    }

    try
    {
        for(const auto& i: _ramps_list)
        {
            has_reachable_storehouse(&i, Color);
        }

    }
    catch (std::logic_error &)
    {
        return false;
    }
    return true;

}



void Factory::do_deliveries(Time t)
{
    for(auto& i: _ramps_list)
    {
        i.deliver_goods(t);
    }
}
void Factory::do_work(int t)
{
    for(auto& i: _workers_list)
    {
        i.do_work(t);
    }
}
void Factory::do_package_passing()
{
    for(auto& i: _workers_list)
    {
        i.send_package();
    }
}

NodeCollection<Ramp>::iterator Factory::find_ramp_by_id(ElementID id)
{
    return std::find_if(std::begin(_ramps_list), std::end(_ramps_list), [id]( auto& i) { return (i.get_id() == id); } );
}
NodeCollection<Ramp>::const_iterator Factory::find_ramp_by_id(ElementID id) const
{
    return std::find_if(std::begin(_ramps_list), std::end(_ramps_list), [id](auto& i) { return (i.get_id() == id); } );
}


NodeCollection<Worker>::iterator Factory::find_worker_by_id(ElementID id)
{
    return std::find_if(std::begin(_workers_list), std::end(_workers_list), [id](auto& i) { return (i.get_id() == id); } );
}
NodeCollection<Worker>::const_iterator Factory::find_worker_by_id(ElementID id) const
{
    return std::find_if(std::begin(_workers_list), std::end(_workers_list), [id](const auto& i) { return (i.get_id() == id); } );
}


NodeCollection<Storehouse>::iterator Factory::find_storehouse_by_id(ElementID id)
{
    return std::find_if(std::begin(_storehouses_list), std::end(_storehouses_list), [id](const auto& i) { return (i.get_id() == id); } );
}
NodeCollection<Storehouse>::const_iterator Factory::find_storehouse_by_id(ElementID id) const
{
    return std::find_if(std::begin(_storehouses_list), std::end(_storehouses_list), [id](auto& i) { return (i.get_id() == id); } );
}




void Factory::add_ramp(Ramp&& ramp)
{
    _ramps_list.add(std::move(ramp));
}

void Factory::remove_ramp(ElementID id)
{
    _ramps_list.remove_by_id(id);
}


void Factory::add_worker(Worker&& worker)
{
    _workers_list.add(std::move(worker));
}

void Factory::remove_worker(ElementID id)
{
    _workers_list.remove_by_id(id);
}


void Factory::add_storehouse(Storehouse&& storehouse)
{
    _storehouses_list.add(std::move(storehouse));
}

void Factory::remove_storehouse(ElementID id)
{
    _storehouses_list.remove_by_id(id);
}