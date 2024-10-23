#include "platform_factory.hpp"

namespace engine::core
{
    std::unique_ptr<Factory> PlatformFactory::create()
    {
        return std::make_unique<win32::Factory>();
    }
}