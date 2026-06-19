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

#include <string>
#include <winsock.h>

namespace Renode::UART
{

SOCKET connect();

bool wait_for_connection(int timeout_ms = 5000);
std::string read_all_available(SOCKET sock);

} // namespace Renode::UART