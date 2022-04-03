#include <tl/net/basic_gateway.hpp>

namespace tl::kt
{

    net::BasicGateway::BasicGateway(asio::io_context& ioContext) :
        m_IoContext {ioContext},
        m_SSLContext {ssl::context::tlsv13_client},
        m_Stream {asio::make_strand(m_IoContext), m_SSLContext},
        m_Status{}
    {

    }

    void net::BasicGateway::asyncConnect(net::error_t ec, asio::ip::tcp::resolver::results_type results)
    {
        if (!(m_Status = ec))
            beast::get_lowest_layer(m_Stream).async_connect(results, beast::bind_front_handler(&BasicGateway::asyncHandshakeSSL, shared_from_this()));
    }

    void net::BasicGateway::asyncHandshakeSSL(net::error_t ec, asio::ip::tcp::resolver::results_type::endpoint_type endpoint)
    {
        
        if (!(m_Status = ec))
            m_Stream.next_layer().async_handshake(ssl::stream_base::client, beast::bind_front_handler(&BasicGateway::asyncHandshakeWS, shared_from_this()));
    }

    void net::BasicGateway::asyncHandshakeWS(net::error_t ec)
    {
        if (!(m_Status = ec))
            m_Stream.async_handshake("gateway.discord.gg", "/?v=9&encoding=json", [self = shared_from_this()](net::error_t ec){
                self->m_Status = ec;
            });
            // m_Stream.async_handshake("gateway.discord.gg", "/?v=9&encoding=json", beast::bind_front_handler(&BasicGateway::async_read_hello, shared_from_this()));
    }

    void net::BasicGateway::Connect()
    {
        asio::ip::tcp::resolver resolver{m_IoContext};
        resolver.async_resolve("gateway.discord.gg", 
                                "443",
                                beast::bind_front_handler(&BasicGateway::asyncConnect, shared_from_this()));

    }

    void net::BasicGateway::Disconnect(web::close_code code)
    {
    }

    void net::BasicGateway::Run() const
    {
        m_IoContext.run();
        m_IoContext.reset();
    }

    asio::io_context& net::BasicGateway::Context() const
    {
        return m_IoContext;
    }

    net::error_t net::BasicGateway::Status() const
    {
        return m_Status;
    }

    net::error_t net::BasicGateway::Status(net::error_t ec)
    {
        m_Status = ec;
        return m_Status;
    }

}