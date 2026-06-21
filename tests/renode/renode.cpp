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
#include <boost/process.hpp>
#include <stdexcept>
#include <string>

namespace Renode
{

static boost::process::child process;

void start()
{
    try
    {
        process = boost::process::child("renode", "--disable-xwt", "test.resc",
                                        boost::process::std_out > boost::process::null,
                                        boost::process::std_err > boost::process::null);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error(std::string("Failed to start Renode: ") + e.what());
    }
}

void stop()
{
    if (process.running())
    {
        process.terminate();
    }
}

bool is_running()
{
    return process.running();
}

} // namespace Renode
