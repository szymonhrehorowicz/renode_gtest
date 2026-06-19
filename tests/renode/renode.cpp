/**
 * @file renode.cpp
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "renode.h"
#include <stdexcept>
#include <string>
#include <windows.h>

namespace Renode
{

static PROCESS_INFORMATION process;

void start()
{
    STARTUPINFOA si{};
    si.cb = sizeof(si);

    BOOL ok = CreateProcessA(nullptr, (LPSTR) "renode --disable-xwt test.resc", nullptr, nullptr, FALSE,
                             CREATE_NO_WINDOW, nullptr, nullptr, &si, &process);

    if (!ok)
    {
        DWORD err = GetLastError();
        throw std::runtime_error("Failed to start Renode, error: " + std::to_string(err));
    }
}

void stop()
{
    TerminateProcess(process.hProcess, 0);
    CloseHandle(process.hProcess);
    CloseHandle(process.hThread);
}

bool is_running()
{
    DWORD code = 0;
    if (GetExitCodeProcess(process.hProcess, &code))
        return code == STILL_ACTIVE;
    return false;
}

} // namespace Renode