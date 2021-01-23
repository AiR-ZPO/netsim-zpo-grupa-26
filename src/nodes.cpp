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

void PackageSender::push_package(Package&& p)
{
    if (!opt)
    {
        opt.emplace(std::move(p));
    }
}

void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    double sum = 0.0;
    preference_[r] = 1;
    for (auto i = preference_.begin(); i != preference_.end(); i++){
        preference_[i->first] = 1.0 / preference_.size();
        sum = sum + i->second;
    }
    if (sum != 1.0)
        preference_[r] = preference_[r] + 1.0 - sum;

}
void ReceiverPreferences::remove_receiver(IPackageReceiver* r)
{
    preference_.erase(r);
    double sum = 0.0;
    for (auto i = preference_.begin(); i != preference_.end(); i++){
        sum += i->second;

    }
    if (sum != 1.0)
    {
        for (auto it = preference_.begin(); it != preference_.end(); it++)
        {
            it->second = it->second / sum;
        }
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    auto a = 0.0;
    auto r = probability_generator();

    for (auto& it : preference_) {
        if (r >= a)
        {
            if (r < a + it.second)
            {
                return it.first;
            }
        }
        a = a + it.second;
    }
    return nullptr;
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
