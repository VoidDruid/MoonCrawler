#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <mutex>

#include "NetworkLinuxPAL.h"

using namespace MoonCrawler;
void NetworkLinuxPAL::sendData(const char* data) const {
    if(not m_isInitialized) {
        return;
    }
    std::cout << "[NetworkLinuxPAL] sendData: " << data << std::endl;
    switch(m_state) {
        case State::Client:
            sendto(m_sockfd, (const char *) data, strlen(data),
                   0, (const struct sockaddr *) &m_servaddr,
                   sizeof(m_servaddr));
            break;
        case State::Server: {
            auto len = sizeof(m_cliaddr);
            sendto(m_sockfd, (const char *) data, strlen(data),
                   0, (const struct sockaddr *) &m_cliaddr,
                   len);
            break;
        }
    }
}

void NetworkLinuxPAL::initServer(std::filesystem::path configFile) {
    //TODO
}

void NetworkLinuxPAL::initServer(const std::string &host, unsigned short port) {
    {
        std::lock_guard<std::mutex> lock(m_shutdownMutex);
        m_isRunning = true;
    }
    // Creating socket file descriptor
    m_state = State::Server;
    if ((m_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&m_servaddr, 0, sizeof(m_servaddr));
    memset(&m_cliaddr, 0, sizeof(m_cliaddr));

    // Filling server information
    m_servaddr.sin_family    = AF_INET; // IPv4
    m_servaddr.sin_addr.s_addr = INADDR_ANY;
    m_servaddr.sin_port = htons(port);

    // Bind the socket with the server address
    if (bind(m_sockfd, (const struct sockaddr *)&m_servaddr,
              sizeof(m_servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(m_cliaddr);
    m_isInitialized = true;
    m_isConnected = true;
    while(true) {
        {
            std::lock_guard<std::mutex> lock(m_shutdownMutex);
            if(not m_isRunning) {
                break;
            }
        }
        n = recvfrom(m_sockfd, (char *) m_buffer.data(), MAX_BUFFER_SIZE,
                     MSG_WAITALL, (struct sockaddr *) &m_cliaddr,
                     reinterpret_cast<socklen_t *>(&len));
        m_buffer[n] = '\0';
        m_callback(m_instance, m_buffer.data());
        std::cout << "[NetworkLinuxPAL] received data: " << m_buffer.data() << std::endl;
        if(n == 0) {
            break;
        }
    }
}

void NetworkLinuxPAL::initClient(std::filesystem::path configFile) {
    //TODO
}

void NetworkLinuxPAL::initClient(const std::string &host, uint64_t port) {
    {
        std::lock_guard<std::mutex> lock(m_shutdownMutex);
        m_isRunning = true;
    }
    m_state = State::Client;
    // Creating socket file descriptor
    if ((m_sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&m_servaddr, 0, sizeof(m_servaddr));

    // Filling server information
    m_servaddr.sin_family = AF_INET;
    m_servaddr.sin_port = htons(port);
    m_servaddr.sin_addr.s_addr = INADDR_ANY;

    m_isInitialized = true;
    m_isConnected = true;
    while(true) {
        {
            std::lock_guard<std::mutex> lock(m_shutdownMutex);
            if(not m_isRunning) {
                break;
            }
        }
        int n, len;
        n = recvfrom(m_sockfd, (char *) m_buffer.data(), MAX_BUFFER_SIZE,
                     MSG_WAITALL, (struct sockaddr *) &m_servaddr,
                     reinterpret_cast<socklen_t *>(&len));
        m_buffer[n] = '\0';
        m_callback(m_instance, m_buffer.data());
        std::cout << "[NetworkLinuxPAL] received data: " << m_buffer.data() << std::endl;
        if(n == 0) {
            break;
        }
    }
}

void NetworkLinuxPAL::setReceiveCallback(void *instance, INetworkPAL::DataReceiveCallback callback) {
    m_callback = std::move(callback);
    m_instance = instance;
}

NetworkLinuxPAL::~NetworkLinuxPAL() {
    close(m_sockfd);
}

bool NetworkLinuxPAL::isConnected() const {
    return m_isConnected;
}

void NetworkLinuxPAL::shutdown() {

    m_isRunning = false;
}
