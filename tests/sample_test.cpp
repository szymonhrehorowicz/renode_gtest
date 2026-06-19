#include "renode/test.h"

namespace Tests
{

TEST_F(Renode_Test, Sanity)
{
    ASSERT_EQ(1, 1);
}

TEST_F(Renode_Test, Regular)
{
    SOCKET uart = Renode::UART::connect();

    // give firmware time to print
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    std::string data = Renode::UART::read_all_available(uart);

    ASSERT_NE(data.find("Hello World!\n"), std::string::npos) << "UART output did not contain expected string.\n"
                                                              << "Received:\n"
                                                              << data;
}

} // namespace Tests
