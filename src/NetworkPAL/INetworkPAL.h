#pragma once

#include <filesystem>
#include <functional>
#include <span>

namespace MoonCrawler {

class INetworkPAL {
    public:
    using DataReceiveCallback = std::function<void(void*, const char*)>;
    virtual void initServer(std::filesystem::path configFile) = 0;
    virtual void initServer(const std::string& host, unsigned short port) = 0;
    virtual void initClient(std::filesystem::path configFile) = 0;
    virtual void initClient(const std::string& host, uint64_t port) = 0;
    virtual void sendData(const char* data) const = 0;
    virtual void setReceiveCallback(void* instance, DataReceiveCallback callback) = 0;
    [[nodiscard]] virtual bool isConnected() const = 0;
};
}