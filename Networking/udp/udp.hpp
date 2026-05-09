#ifndef UDP_HPP
#define UDP_HPP

#include <vector>
#include <cstdint>
#include <sys/types.h>

int udp_socket();
int udp_bind(int sockfd, const char* ip, uint16_t port);
ssize_t udp_sendto(int sockfd, const std::vector<uint8_t>& buf, const char* ip, uint16_t port);
ssize_t udp_recvfrom(int sockfd, std::vector<uint8_t>& buf, char* ip, uint16_t* port);
int udp_close(int sockfd);

#endif // UDP_HPP
