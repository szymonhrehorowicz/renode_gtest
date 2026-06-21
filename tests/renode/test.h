/**
 * @file test.h
 * @author Szymon Hrehorowicz
 * @brief
 * @version 0.1
 * @date 2026-06-19
 *
 * @copyright Copyright (c) 2026
 *
 */

#pragma once

#include "renode.h"
#include "uart.h"
#include <boost/asio.hpp>
#include <gtest/gtest.h>

namespace Tests
{

class Renode_Test : public ::testing::Test
{
    using Base = ::testing::Test;

  protected:
    boost::asio::io_context io;

  public:
    void SetUp() override
    {
        Base::SetUp();

        Renode::start();

        if (!Renode::UART::wait_for_connection())
            throw std::runtime_error("Renode did not open UART socket");
    }

    void TearDown() override
    {
        Renode::stop();
        Base::TearDown();
    }
};

} // namespace Tests
