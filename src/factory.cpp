//
// Created by Pawel on 17.12.2020.
//

#include "factory.hpp"
#include "nodes.hpp"
#include <vector>
#include <utility>
#include <map>


enum class NodeColor { UNVISITED, VISITED, VERIFIED };

bool Factory::is_consistent()
{
    Color std::map<PackageSender*, NodeColor> = {};
    for(auto i: _ramps_list)
        Color[&i] = NodeColor::UNVISITED;
    for(auto i: _workers_list)
        Color[&i] = NodeColor::UNVISITED;

    try
    {
        for(auto i: _ramps_list)
        {
            is_way_from_sender_to_receiver(&i, Color[&i])
        }

    } catch (std::valueerror)
    {
        return false
    }
    return true


    is_way_from_sender_to_receiver(PackageSender* sender, NodeColor color)
    {
        if( Color[sender] == NodeColor::VERIFIED)
            return true
        Color[sender] == NodeColor::VISITED
        if (*sender.receiver_preferences_.get_preferences().size() == 0)
        {
            throw std::valueerror();
        }

        bool another_receiver = false
        preferences_t pref = *sender.receiver_preferences_.get_preferences();
        for(auto [key, value]: pref)
        {
            if(*key.get_receiver_type() == ReceiverType::STOREHOUSE)
            {
                another_receiver = true
            }
            else if(*key.get_receiver_type() == ReceiverType::WORKER)
            {
                IPackageReceiver* receiver_ptr = key;
                auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
                auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
                if( sendrecv_ptr == sender)
                {
                    continue;
                }
                another_receiver = true
                if(Color[sendrecv_ptr] == NodeColor::UNVISITED)
                {
                    is_way_from_sender_to_receiver(sendrecv_ptr,Color[sendrecv_ptr])
                }
            }
        }
        Color[sender] = NodeColor::VERIFIED
        if(another_receiver)
        {
            return true
        }
        else
        {
            throw std::valueerror();
        }

    }
}



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


void Factory::remove_receiver(collection: NodeCollection<Node>&, id: ElementID)
{
    (*collection).remove_by_id(id);
}

void Factory::add_ramp(Ramp&&)
{
    _rams_list.add(Ramp())
}

void Factory::remove_ramp(ElementID id)
{
    _ramps_list.remove_by_id(id);
}


void Factory::add_worker(Worker&&)
{
    _workers_list.add(Worker())
}

void Factory::remove_worker(ElementID id)
{
    _workers_list.remove_by_id(id);
}


void Factory::add_storehouse(Storehouse&&)
{
    _storehouses_list.add(Storehouse())
}

void Factory::remove_storehouse(ElementID id)
{
    _storehouses_list.remove_by_id(id);
}