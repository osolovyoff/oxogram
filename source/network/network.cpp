//#include "network.h"
//
//#include <neuro/develop/logger/logger.h>
//
//Network::Network()
//    : _service()
//    , _socket(_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), PORT))
//{
//    receive();
//}
//
//void Network::send(const void * data, const size_t & length)
//{
//    if (data && length)
//        _socket.async_send_to(boost::asio::buffer(data, length), _endpoint,
//            [&](boost::system::error_code ec, std::size_t received_uint8_ts)
//    {
//        if (ec)
//            logger << Log::Type::network << logger.time_now() << CODEINFO << ec.message() << std::endl;
//    });
//}
//
//void Network::send(Package&& package)
//{
//    if (!package.empty() && _is_connected)
//        _socket.async_send_to(boost::asio::buffer(package.data(), package.size()), _endpoint,
//            [&](boost::system::error_code ec, std::size_t received_uint8_ts)
//    {
//        if (ec)
//            logger << Log::Type::network << logger.time_now() << CODEINFO << ec.message() << std::endl;
//    });
//}
//
//void Network::set_connected(bool state)
//{
//    _is_connected = state;
//    _endpoint = _unknown_endpoint;
//}
//
//std::string Network::get_endpoint() const
//{
//    using namespace std;
//    const string endpoint
//        = _endpoint.address().to_string()
//        + ':' + to_string(_endpoint.port());
//    return endpoint;
//}
//
//void Network::run()
//{
//    _service.run();
//}
//
//void Network::disconnect()
//{
//    _service.stop();
//}
//
//void Network::receive()
//{
//    _socket.async_receive_from(boost::asio::buffer(_buffer), _unknown_endpoint,
//        [&](boost::system::error_code ec, std::size_t uint8_ts_received)
//    {
//        if (ec)
//            logger << Log::Type::error << logger.time_now() << CODEINFO << ec.message() << std::endl;
//        else
//        {
//            if (uint8_ts_received)
//            {
//                const bool is_verificated = _unknown_endpoint == _endpoint;
//                const bool is_connect_index = PackageIndex(PackageGeneralIndex::connect) == PackageIndex((void*)_buffer.data());
//
//                if (is_verificated || is_connect_index)
//                    PackageObserver::broadcast(Package(_buffer.data(), uint8_ts_received));
//            }
//        }
//
//        receive();
//    });
//}