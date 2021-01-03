//
// Created by Pawel on 17.12.2020.
//
#include "package.hpp"
#include "storage_types.hpp"
#include <utility>
void PackageQueue::push(Package package)
{
    PackageList_.emplace_back(std::move(package));
}

Package PackageQueue::pop()
{
    switch (type_)
    {
        case PackageQueueType::Fifo_:
        {
            Package package(PackageList_.begin()->get_id());
            PackageList_.pop_front();
            return package;
        }
        case PackageQueueType::Lifo_:
        {
            Package package((PackageList_.end()--)->get_id());
            PackageList_.pop_back();
            return package;
        }
        default:
        {
            throw std::invalid_argument( "received negative value" );
        }
    }
}
