//
// Created by Pawel on 17.12.2020.
//

#ifndef NET_SIMULATION_STORAGE_TYPES_HPP
#define NET_SIMULATION_STORAGE_TYPES_HPP

#endif //NET_SIMULATION_STORAGE_TYPES_HPP

#include <list>
#include <iostream>


/*klasy IPackageStockpile, IPackageQueue, PackageQueue
typ wyliczeniowy PackageQueueType
 */
enum class PackageQueueType{
    Fifo_, Lifo_
};

class IPackageStockpile
{
public:
    using const_iterator = std::list<Package>::const_iterator;
    virtual void push(Package package);
    virtual bool empty() const;
    virtual std::size_t size() const;
    virtual ~IPackageStockpile() {}
    virtual const_iterator cbegin() const;
    virtual const_iterator cend() const;
    virtual const_iterator begin() const;
    virtual const_iterator end() const;
};

class IPackageQueue: public IPackageStockpile
{
public:
    virtual Package pop();
    virtual PackageQueueType get_queue_type();
    virtual ~IPackageQueue() {}
};

class PackageQueue: public IPackageQueue
{
public:
    PackageQueue(PackageQueueType type) : type_(type) {}
    void push(Package package) override;
    bool empty() const override { return PackageList_.empty(); }
    std::size_t size() const override { return PackageList_.size(); }
    Package pop() override;
    PackageQueueType get_queue_type() override {return type_;}
    const_iterator cbegin() const override { return PackageList_.cbegin(); }
    const_iterator cend() const override { return PackageList_.cend(); }
    const_iterator begin() const override { return PackageList_.cbegin(); }
    const_iterator end() const override{ return PackageList_.cend(); }
    ~PackageQueue() override {}
private:
    std::list <Package> PackageList_;
    PackageQueueType type_;
};