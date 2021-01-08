//
// Created by Pawel on 17.12.2020.
//

#ifndef NET_SIMULATION_NODES_HPP
#define NET_SIMULATION_NODES_HPP

#endif //NET_SIMULATION_NODES_HPP
/*
typ wyliczeniowy ReceiverType
klasy IPackageReceiver, Storehouse, ReceiverPreferences, PackageSender, Ramp, Worker
 */
#include "package.hpp"
#include "storage_types.hpp"
#include <map>
#include <iostream>
#include <memory>
#include "helpers.cpp"

enum class ReceiverType{
    WORKER, STOREHOUSE
};

class IPackageReceiver
{
public:
    virtual void receive_package(Package&& p) = 0;
    virtual ElementID get_id() const = 0;
    virtual ReceiverType get_receiver_type() = 0;

    virtual IPackageStockpile::const_iterator begin() const = 0;
    virtual IPackageStockpile::const_iterator cbegin() const = 0;
    virtual IPackageStockpile::const_iterator end() const = 0;
    virtual IPackageStockpile::const_iterator cend() const = 0;
};

class ReceiverPreferences
{

public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;

    explicit ReceiverPreferences(ProbabilityGenerator pg = default_probability_generator) : pg_(std::move(pg)) {}
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const preferences_t& get_preferences() const { return preference_;}
    const_iterator cbegin() const  { return preference_.cbegin(); }
    const_iterator cend() const  { return preference_.cend(); }
    const_iterator begin() const  { return preference_.cbegin(); }
    const_iterator end() const { return preference_.cend(); }

private:
    preferences_t preference_;
    ProbabilityGenerator pg_;
};

class PackageSender: public ReceiverPreferences {
public:
    PackageSender() = default;
    ReceiverPreferences receiver_preferences_;
    PackageSender(PackageSender&&) = default;
    void send_package();
    std::optional<Package>& get_sending_buffer() {return opt;}
protected:
    void push_package(Package&&);
private:
    std::optional<Package> opt;
};



class Storehouse: public IPackageStockpile, public IPackageReceiver
{
public:
    explicit Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueueType::Fifo_)) : _id(id), _d(std::move(d)) {}
    ElementID get_id() const override { return _id; }
    void receive_package(Package&& p) override { _d->push(std::move(p)); }
    ReceiverType get_receiver_type() override { return ReceiverType::STOREHOUSE; }

    IPackageStockpile::const_iterator begin() const override { return _d->cbegin(); }
    IPackageStockpile::const_iterator cbegin() const override { return _d->cbegin(); }
    IPackageStockpile::const_iterator end() const override { return _d->cend(); }
    IPackageStockpile::const_iterator cend() const override { return _d->cend(); }

private:
    ElementID _id;
    std::unique_ptr<IPackageStockpile> _d;
};

class Ramp: public PackageSender
{
public:
    Ramp(ElementID id, TimeOffset di) : _id(id), _di(di) {}
    ElementID get_id() const { return _id; }
    TimeOffset get_delivery_interval() const { return _di;}
    void deliver_goods(Time t);

private:
    ElementID _id;
    TimeOffset _di;
};

class Worker: public IPackageQueue, public IPackageReceiver, public PackageSender
{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : _id(id), _pd(pd), _t(0), _q(std::move(q)), _buf(std::nullopt) {}
    TimeOffset get_processing_duration() const { return _pd;}
    Time get_package_precessing_start_time() const { return _t; }
    ElementID get_id() const override { return _id; }
    void do_work(Time t); // Do omówienia!
    void receive_package(Package&& p) override { _q->push(std::move(p)); }
    ReceiverType get_receiver_type() override { return ReceiverType ::WORKER; }

    IPackageStockpile::const_iterator begin() const override { return _q->cbegin(); }
    IPackageStockpile::const_iterator cbegin() const override { return _q->cbegin(); }
    IPackageStockpile::const_iterator end() const override { return _q->cend(); }
    IPackageStockpile::const_iterator cend() const override { return _q->cend(); }

private:
    ElementID _id;
    TimeOffset _pd;
    Time _t;
    std::unique_ptr<IPackageQueue> _q;
    std::optional<Package> _buf;
};



