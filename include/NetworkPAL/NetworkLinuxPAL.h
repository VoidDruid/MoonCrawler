#pragma once

#include "INetworkPAL.h"
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
namespace MoonCrawler {
class NetworkLinuxPAL : public INetworkPAL {
    public:
    void initServer(std::filesystem::path configFile) override;
    void initServer(const std::string& host, unsigned short port) override;
    void initClient(std::filesystem::path configFile) override;
    void initClient(const std::string& host, uint64_t port) override;
    void sendData(const char* data) const override;
    void setReceiveCallback(void* instance, DataReceiveCallback callback) override;

    private:
    int m_sockfd{};
    bool m_isInitialized{false};
    bool m_isConnected{false};
    struct sockaddr_in m_servaddr, m_cliaddr;
    static constexpr uint16_t MAX_BUFFER_SIZE = 1024;
    std::array<uint8_t, MAX_BUFFER_SIZE> m_buffer{};
    DataReceiveCallback m_callback{};
    void* m_instance{};
};
}