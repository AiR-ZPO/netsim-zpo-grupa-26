//
// Created by Pawel on 17.12.2020.
//
#include "storage_types.hpp"
#include <utility>
void PackageQueue::push(Package&&)
{
    PackageList_.emplace_back(std::move(Package&&));
}

Package PackageQueue::pop()
{

    switch (type_)
    {
        case PackageQueueType::Fifo_:
            PackageList_.pop_front();
            break;
        case PackageQueueType::Lifo_:
            PackageList_.pop_back();
            break;
    }
}