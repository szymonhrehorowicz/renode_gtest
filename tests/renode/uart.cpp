/**
 * @file uart.cpp
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "uart.h"
#include <chrono>
#include <thread>

namespace Renode::UART
{

static constexpr int uart_port = 12345;

bool wait_for_connection(int timeout_ms)
{
    auto start = std::chrono::steady_clock::now();

    while (true)
    {
        try
        {
            boost::asio::io_context io;
            boost::asio::ip::tcp::socket sock(io);

            boost::asio::ip::tcp::endpoint ep(boost::asio::ip::make_address("127.0.0.1"), uart_port);

            sock.connect(ep);
            return true; // Renode is ready
        }
        catch (...)
        {
            // Not ready yet
        }

        if (std::chrono::steady_clock::now() - start > std::chrono::milliseconds(timeout_ms))
        {
            return false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

TcpSocket connect(boost::asio::io_context &io)
{
    TcpSocket sock(io);

    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::make_address("127.0.0.1"), uart_port);

    sock.connect(ep);
    return sock;
}

std::string read_all_available(TcpSocket &sock)
{
    std::string out;
    char buf[256];

    boost::system::error_code ec;

    while (true)
    {
        std::size_t n = sock.read_some(boost::asio::buffer(buf), ec);

        if (!ec && n > 0)
        {
            out.append(buf, n);
        }
        else
        {
            break; // no more data or error
        }
    }

    return out;
}

} // namespace Renode::UART
