//
// Created by Pawel on 17.12.2020.
//
#include "nodes.hpp"
#include "helpers.hpp"
#include <numeric>
void PackageSender::send_package()
{
    if (opt)
    {
        IPackageReceiver* rec = receiver_preferences_.choose_receiver();
        rec->receive_package(std::move(opt.value()));
        opt.reset();
    }
}

void PackageSender::push_package(Package&&)
{
    if (!opt)
    {
        opt.emplace(Package());
    }
}

void ReceiverPreferences::add_receiver(IPackageReceiver* r)
{
    preference_[r] = default_probability_generator();
    int sum = std::accumulate(preference_.begin(), preference_.end(), 0);
    for (auto it = preference_.begin(); it != preference_.end(); ++it){
        it->second = it->second/sum;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r)
{
    int sum = std::accumulate(preference_.begin(), preference_.end(), 0);
    preference_.erase(r);
    for (auto it = preference_.begin(); it != preference_.end(); ++it){
        it->second = it->second/sum;
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver()
{
    double r = default_probability_generator();
    int size = preference_.size();
    double a = 0.0;
    auto b = preference_.begin();
    for (int i = 1; i<=size; i++)
    {
        if (r >= a and r < b->second)
        {
            break;
        }
        else
        {
            a += b->second;
            b->second += (b++)->second;
        }
    }
    return preference_.begin()->first;
}

void Ramp::deliver_goods(Time t) {
    if (_di == 1){
        push_package(Package());
    }
    else{
        if (t % _di == 1){
            push_package(Package());
        }
    }
}

void Worker::do_work(Time t) {
    if (not _buf and not _q->empty() and _pd == 1){
        _t = t;
        push_package(_q->pop());
    }
    else if (not _buf and not _q->empty() and _pd != 1){
        _t = t;
        _buf.emplace(_q->pop());
    }
    else if (_t + (_pd - 1) == t and _buf){
        push_package(std::move(*_buf));
        _buf.reset();
    }
}