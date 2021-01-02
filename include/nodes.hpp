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

class IPackageReceiver
{
public:
    virtual void receive_package(Package&& p);
    virtual ElementID get_id();
};

class PackageSender {
public:
    PackageSender(PackageSender&&) = default;
    void send_package();
    std::optional<Package>& get_sending_buffer();
    void push_package(Package&&);
private:
};

class Storehouse: public IPackageQueue
{
public:
private:
};

class Ramp
{
public:
private:
};

class Worker: public IPackageQueue
{
public:
private:
};

class ReceiverPreferences
{
public:
private:
};

