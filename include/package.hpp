//
// Created by Mateusz on 2020-12-17.
//

#ifndef NET_SIMULATION_PACKAGE_HPP
#define NET_SIMULATION_PACKAGE_HPP

#endif //NET_SIMULATION_PACKAGE_HPP


class IPackageStockpile
{
public:
    virtual push(Package&&): void {}
    virtual empty(): bool {query}
    virtual size(): size_type {query}
    virtual ~IPackageStockpile() {}
};

class IPackageQueue: public IPackageStockpile
{
public:
    virtual pop(): Package {}
    virtual get_queue_type(): PackageQueueType {query}
    virtual ~IPackageQueue() {}
};