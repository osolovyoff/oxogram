//#pragma once                
//#ifndef package_observer_h__
//#define package_observer_h__
//
//#include <mutex>
//#include <unordered_map>
//
//#include <vrtek/pkg/package/package.h>
//
//class PackageObserver
//{
//    using Listener = std::function<void(Package&&)>;
//
//public:
//    void subscribe(const PackageIndex pi, Listener fn);
//    void broadcast(Package&& package) const;
//
//private:
//    std::mutex                                 _mutex;
//    std::unordered_map<PackageIndex, Listener> _listeners;
//};
//
//#endif// !package_observer_h__