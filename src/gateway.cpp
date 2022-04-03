#include <tl/net/gateway.hpp>

namespace tl::kt
{

    net::Gateway::Gateway(asio::io_context& ioContext, const std::string& token) :
        m_IoContext{ioContext},
        m_BotToken{token},
        m_HeartbeatInterval{0},
        m_NextLayer{std::make_shared<BasicGateway>(ioContext)}
    {

    }


    void net::Gateway::asyncReadHello(net::error_t ec)
    {
        if (!NextLayer().Status(ec))
            m_NextLayer->Read(m_StatusBuffer, beast::bind_front_handler(&Gateway::asyncProcessHello, shared_from_this()));
    }

    void net::Gateway::asyncProcessHello(net::error_t ec, size_t bytesRead)
    {
        if (!NextLayer().Status(ec))
        {
            std::string response = beast::buffers_to_string(m_StatusBuffer.data());
            m_StatusBuffer.consume(bytesRead);
            json helloJson = json::parse(response);
            int opCode = helloJson["op"].get<int>();
            if (opCode == discord::opcode::hello)
            {
                int interval = helloJson["d"]["heartbeat_interval"].get<int>();
                m_HeartbeatInterval = asio::chrono::milliseconds{interval};

                asio::post(m_IoContext, beast::bind_front_handler(&Gateway::asyncSendIdentify, shared_from_this()));
            }
        }
    }

    void net::Gateway::asyncSendIdentify()
    {
            json identifyPayload = R"(
                {
                    "op": 2,
                    "d": {
                        "intents": 8,
                        "properties": {
                            "$os": "windows",
                            "$browser": "tracybot",
                            "$device": "tracybot"
                        }
                    }
                }

            )"_json;
            identifyPayload["d"]["token"] = m_BotToken;
            std::string dmp = identifyPayload.dump();
            m_NextLayer->Write(asio::buffer(dmp), beast::bind_front_handler(&Gateway::asyncReadIdentify, shared_from_this()));
    }

    void net::Gateway::asyncReadIdentify(net::error_t ec, size_t bytesWritten)
    {
        if (!NextLayer().Status(ec))
            m_NextLayer->Read(m_StatusBuffer, beast::bind_front_handler(&Gateway::asyncProcessIdentify, shared_from_this()));
    }

    void net::Gateway::asyncProcessIdentify(net::error_t ec, size_t bytesRead)
    {
        if (!NextLayer().Status(ec))
        {
            std::string response = beast::buffers_to_string(m_StatusBuffer.data());
            m_StatusBuffer.consume(bytesRead);
        }
    }

    net::error_t net::Gateway::Connect()
    {
        m_NextLayer->Connect();
        m_NextLayer->Run();
        return m_NextLayer->Status();
    }

    net::error_t net::Gateway::Identify()
    {
        m_NextLayer->Read(m_StatusBuffer, beast::bind_front_handler(&Gateway::asyncProcessHello, shared_from_this()));
        m_NextLayer->Run();
        
        std::cout << beast::buffers_to_string(m_StatusBuffer.data()) << "\n";
        return m_NextLayer->Status();
    }

}