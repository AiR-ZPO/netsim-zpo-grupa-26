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
                PackageList_.pop_front();
                break;
            case PackageQueueType::Lifo_:
                PackageList_.pop_back();
                break;
        }
}
