#include <cstdlib>
#include <string>
#include <iostream>
#include <thread>

#include <tl/net/gateway.hpp>

const std::string TOKEN = "NzI3NDcwNTQ4ODIwNDI2Nzc3.XvsTvg.m1kD8nH5zcoVLNiIChsK3cxvgfw";

int main(int argc, char** argv)
{
    asio::io_context ioc;
    auto gateway = std::make_shared<tl::kt::net::Gateway>(ioc, TOKEN);
    tl::kt::net::error_t erc = gateway->Connect();
    std::cout << erc.what() << '\n';
    erc = gateway->Identify();
    std::cout << erc.what() << '\n';
    return 0;
}