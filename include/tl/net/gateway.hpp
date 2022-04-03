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
            std::shared_ptr<BasicGateway>   m_BasicGateway;

        private:

            void asyncReadHello(beast::error_code ec);
            void asyncProcessHello(beast::error_code ec, size_t bytesRead);
            void asyncSendIdentify();
            void asyncReadIdentify(beast::error_code ec, size_t bytesWritten);
            void asyncProcessIdentify(beast::error_code ec, size_t bytesRead);  

        public:

            Gateway(asio::io_context&, const std::string& token);

        public:

            beast::error_code Connect();
            beast::error_code Identify();
            beast::error_code Hello();
            void              BeginHeartbeat();
            void              BeginRead();

            BasicGateway& NextLayer() { return *m_BasicGateway; }

    };

}
}

#endif 