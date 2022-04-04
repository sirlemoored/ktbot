#ifndef NET_COMMON_HPP
#define NET_COMMON_HPP

#define _WIN32_WINNT 0x0601
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <nlohmann/json.hpp>


namespace asio      = boost::asio;
namespace beast     = boost::beast;
namespace http      = boost::beast::http;
namespace ssl       = boost::asio::ssl;
namespace web       = boost::beast::websocket;
using json          = nlohmann::json;


namespace tl::kt::net
{

    using stream_t  = beast::websocket::stream<beast::ssl_stream<beast::tcp_stream>>;
    using error_t   = boost::system::error_code;

    class BasicGateway;
    class Gateway;
}

#endif 