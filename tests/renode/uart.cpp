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
#include <winsock.h>

namespace Renode::UART
{

static constexpr int uart_port{12345};

SOCKET connect()
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(uart_port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (sockaddr *)&addr, sizeof(addr));
    return sock;
}

bool wait_for_connection(int timeout_ms)
{
    auto start = std::chrono::steady_clock::now();

    while (true)
    {
        SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(uart_port);
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (connect(s, (sockaddr *)&addr, sizeof(addr)) == 0)
        {
            closesocket(s);
            return true; // Renode is ready
        }

        closesocket(s);

        if (std::chrono::steady_clock::now() - start > std::chrono::milliseconds(timeout_ms))
            return false;

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

std::string read_all_available(SOCKET sock)
{
    std::string out;

    // make socket non-blocking
    u_long mode = 1;
    ioctlsocket(sock, FIONBIO, &mode);

    char buf[256];
    while (true)
    {
        int n = recv(sock, buf, sizeof(buf), 0);
        if (n > 0)
        {
            out.append(buf, n);
        }
        else
        {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
                break; // no more data
            break;     // other error
        }
    }

    // restore blocking mode
    mode = 0;
    ioctlsocket(sock, FIONBIO, &mode);

    return out;
}

} // namespace Renode::UART