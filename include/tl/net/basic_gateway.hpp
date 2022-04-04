#ifndef NET_BASIC_GATEWAY_HPP
#define NET_BASIC_GATEWAY_HPP

#include <tl/net/common.hpp>

#include <chrono>
#include <iostream>
#include <memory>
#include <utility>

namespace tl::kt::net
{


    // A low-level intermediate between Discord gateway and the Bot.
    // Contains connection-oriented methods (I/O, handshake etc.).
    // Does not maintain the connection; its role comes down to a 
    // basic communication interface.
    class BasicGateway : public std::enable_shared_from_this<BasicGateway>
    {

        // Member types
        public:

            using buffers_t = beast::multi_buffer;
            friend class Gateway;

        private:
            
            asio::io_context&           m_IoContext;
            ssl::context                m_SSLContext;
            net::stream_t                 m_Stream;
            net::error_t                m_Status;


        private:
            void asyncConnect(net::error_t ec, asio::ip::tcp::resolver::results_type results);
            void asyncHandshakeSSL(net::error_t ec, asio::ip::tcp::resolver::results_type::endpoint_type endpoint);
            void asyncHandshakeWS(net::error_t ec);

        public:

            BasicGateway(asio::io_context&);
            BasicGateway(const BasicGateway&)             = delete;
            BasicGateway(BasicGateway&&)                  = default;
            BasicGateway& operator=(const BasicGateway&)  = delete;
            BasicGateway& operator=(BasicGateway&&)       = default;
            ~BasicGateway()                               = default;
            
            void Connect();
            void Disconnect(web::close_code);
            
            template <typename Buffer, typename Callback> 
            void Read(Buffer&, Callback&&);
            
            template <typename Buffer, typename Callback> 
            void Write(Buffer&, Callback&&);

            void Run() const;
            asio::io_context& Context() const;
            net::error_t Status() const;
            net::error_t Status(net::error_t ec);

    };


    template <typename Buffer, typename Callback>
    void net::BasicGateway::Read(Buffer& buffer, Callback&& f)
    {
        m_Stream.async_read(buffer, std::forward<Callback>(f));
    }

    template <typename Buffer, typename Callback>
    void net::BasicGateway::Write(Buffer& buffer, Callback&& f)
    {
        m_Stream.async_write(buffer, std::forward<Callback>(f));
    }


} // namespace tl::kt::net

#endif