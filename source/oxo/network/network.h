//#pragma once
//#include <functional>
//
////#include <boost/asio.hpp>
////
////#include <neuro/tasks/task.h>
////#include <neuro/tasks/network/observer/package_observer.h>
////
////#include <vrtek/pkg/package/package.h>
//
//class Network : public ITask, public PackageObserver
//{
//    static constexpr unsigned short PORT = 13666;
//    static constexpr unsigned short UDP_MAX_PKG_SIZE = 65507u;
//
//public:
//    explicit Network();
//    virtual ~Network() = default;
//
//public:
//    void send(const void* data = nullptr, const size_t& length = 0);
//    void send(Package&& package);
//
//    void        set_connected(bool state);
//    std::string get_endpoint() const;
//
//private:
//    virtual void run() override final;
//    virtual void disconnect() override final;
//
//    void receive();
//
//private:
//    boost::asio::io_service            _service;
//    boost::asio::ip::udp::socket       _socket;
//    boost::asio::ip::udp::endpoint     _endpoint;
//    boost::asio::ip::udp::endpoint     _unknown_endpoint;
//    std::array<char, UDP_MAX_PKG_SIZE> _buffer;
//
//private:
//    bool                               _is_connected = { false };
//};