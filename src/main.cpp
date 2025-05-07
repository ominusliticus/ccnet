// STL
#include <string>

// CCNet
#include "print.hpp"
#include "version.hpp"

auto 
version_string(
) -> std::string
{
    std::string major{ CCNet_VERSION_MAJOR };
    std::string minor{ CCNet_VERSION_MINOR };
    return "v" + major + "." + minor;
}

auto
banner(
) -> void
{
    print("CCNet: Chalker-Coddington Network");
    print("Version:", version_string());
}


auto
main(
    [[maybe_unused]] int    argc,
    [[maybe_unused]] char** argv
) -> int
{
    banner();
    print("Hello World!");
    return 0;
}
