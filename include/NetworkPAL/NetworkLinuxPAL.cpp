#include "NetworkLinuxPAL.h"

using namespace MoonCrawler;
#include <string>
void NetworkLinuxPAL::sendData(const char* data) const {
    if(not m_isInitialized) {
        return;
    }

    auto len = sizeof(m_cliaddr);
    sendto(m_sockfd, (const char *)data, strlen(data),
           0, (const struct sockaddr *) &m_cliaddr,
           len);
    printf("Hello message sent.\n");
}

void NetworkLinuxPAL::initServer(std::filesystem::path configFile) {
    //TODO
}
constexpr auto MAXLINE = 1024;
void NetworkLinuxPAL::initServer(const std::string &host, unsigned short port) {
    char buffer[MAXLINE];

    // Creating socket file descriptor
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

    len = sizeof(m_cliaddr);  //len is value/resuslt
    m_isInitialized = true;
    m_isConnected = true;
    while(true) {
        n = recvfrom(m_sockfd, (char *) buffer, MAXLINE,
                     MSG_WAITALL, (struct sockaddr *) &m_cliaddr,
                     reinterpret_cast<socklen_t *>(&len));
        buffer[n] = '\0';
        printf("Client : %s\n", buffer);
        m_callback(m_instance, buffer);
        if(n == 0) {
            printf("Client disconnected\n");
            break;
        }
    }
}

void NetworkLinuxPAL::initClient(std::filesystem::path configFile) {
    //TODO
}

void NetworkLinuxPAL::initClient(const std::string &host, uint64_t port) {

}

bool NetworkLinuxPAL::isConnected() const {
    return m_isConnected;
}

void NetworkLinuxPAL::setReceiveCallback(void *instance, INetworkPAL::DataReceiveCallback callback) {
    m_callback = std::move(callback);
    m_instance = instance;
}
