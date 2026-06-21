/**
 * @file uart.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include <boost/asio.hpp>
#include <string>

namespace Renode::UART
{

using TcpSocket = boost::asio::ip::tcp::socket;

bool wait_for_connection(int timeout_ms = 5000);
TcpSocket connect(boost::asio::io_context &io);
std::string read_all_available(TcpSocket &sock);

} // namespace Renode::UART