#include <cstdlib>
#include <string>
#include <iostream>
#include <thread>

#include <tl/net/gateway.hpp>
#include <tl/discord/payload_base.hpp>

const std::string TOKEN = "";

int main(int argc, char** argv)
{

    json_t j = R"(
        {
            "x": 2,
            "y": {
                "i": 2,
                "j": 5
            }
        }
    )"_json;

    tl::kt::discord::Json jj;
    jj.GetVal(j, "y");

    // asio::io_context ioc;
    // auto gateway = std::make_shared<tl::kt::net::Gateway>(ioc, TOKEN);
    // tl::kt::net::error_t erc = gateway->Connect();
    // std::cout << erc.what() << '\n';
    // erc = gateway->Identify();
    // std::cout << erc.what() << '\n';
    return 0;
}