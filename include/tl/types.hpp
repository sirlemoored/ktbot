#ifndef TYPES_HPP
#define TYPES_HPP

#define _WIN32_WINNT 0x0601

#include <boost/system/error_code.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <nlohmann/json.hpp>

namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace asio = boost::asio;
namespace ssl = boost::asio::ssl;
namespace web = boost::beast::websocket;
using json = nlohmann::json;

namespace tl::kt
{

namespace net
{
    using stream    = beast::websocket::stream<beast::ssl_stream<beast::tcp_stream>>;
    using error_t   = boost::system::error_code;

    class BasicGateway;
    class Gateway;
}

namespace discord
{    struct opcode
    {
        static constexpr int dispatch         = 0;
        static constexpr int heartbeat        = 1;
        static constexpr int identify         = 2;
        static constexpr int presence         = 3;
        static constexpr int voice            = 4;
        static constexpr int resume           = 6;
        static constexpr int reconnect        = 7;
        static constexpr int guild_members    = 8;
        static constexpr int invalid_session  = 9;
        static constexpr int hello            = 10;
        static constexpr int heartbeat_ack    = 11;
    };

}
}

#endif