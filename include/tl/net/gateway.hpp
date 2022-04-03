#ifndef GATEWAY_HPP
#define GATEWAY_HPP

#include <tl/types.hpp>
#include <tl/net/basic_gateway.hpp>

namespace tl::kt
{
namespace net
{

    class Gateway : public std::enable_shared_from_this<Gateway>
    {
        private:

            asio::io_context&               m_IoContext;
            std::string                     m_BotToken;
            std::chrono::milliseconds       m_HeartbeatInterval;

            BasicGateway::buffers_t         m_StatusBuffer;
            std::shared_ptr<BasicGateway>   m_NextLayer;

        private:

            void asyncReadHello(net::error_t ec);
            void asyncProcessHello(net::error_t ec, size_t bytesRead);
            void asyncSendIdentify();
            void asyncReadIdentify(net::error_t ec, size_t bytesWritten);
            void asyncProcessIdentify(net::error_t ec, size_t bytesRead);  

        public:

            Gateway(asio::io_context&, const std::string& token);

        public:

            net::error_t      Connect();
            net::error_t      Identify();
            net::error_t      Hello();
            void              BeginHeartbeat();
            void              BeginRead();

            BasicGateway& NextLayer() { return *m_NextLayer; }

    };

}
}

#endif 