#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")

// Helper to format MAC address
std::string format_mac(const unsigned char* mac) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (int i = 0; i < 6; ++i) {
        ss << std::setw(2) << (int)mac[i] << (i < 5 ? ":" : "");
    }
    return ss.str();
}

// Helper to format IP address
std::string format_ip(const unsigned char* ip) {
    std::stringstream ss;
    for (int i = 0; i < 4; ++i) {
        ss << (int)ip[i] << (i < 3 ? "." : "");
    }
    return ss.str();
}

// Simple hex dump function (like Python's format_multi_line)
void hex_dump(const unsigned char* data, size_t len, const std::string& prefix = "\t") {
    std::stringstream ss;
    for (size_t i = 0; i < len; ++i) {
        if (i % 16 == 0) ss << prefix;
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)data[i] << " ";
        if ((i + 1) % 16 == 0 || i + 1 == len) ss << "\n";
    }
    std::cout << ss.str();
}

// Structs for packet headers (for easier unpacking)
struct EthernetHeader {
    unsigned char dest_mac[6];
    unsigned char src_mac[6];
    unsigned short proto;
};

struct IPHeader {
    unsigned char ver_ihl;  // Version (4 bits) + IHL (4 bits)
    unsigned char tos;
    unsigned short total_len;
    unsigned short id;
    unsigned short flags_frag;
    unsigned char ttl;
    unsigned char proto;
    unsigned short checksum;
    unsigned char src_ip[4];
    unsigned char dest_ip[4];
};

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    SOCKET sniffer = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if (sniffer == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    // Get local host IP
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        std::cerr << "gethostname failed\n";
        closesocket(sniffer);
        WSACleanup();
        return 1;
    }
    struct hostent* local = gethostbyname(hostname);
    if (!local) {
        std::cerr << "gethostbyname failed\n";
        closesocket(sniffer);
        WSACleanup();
        return 1;
    }
    struct in_addr addr;
    memcpy(&addr, local->h_addr_list[0], sizeof(struct in_addr));

    sockaddr_in bind_addr;
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_port = 0;
    bind_addr.sin_addr.s_addr = addr.s_addr;

    if (bind(sniffer, (sockaddr*)&bind_addr, sizeof(bind_addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << "\n";
        closesocket(sniffer);
        WSACleanup();
        return 1;
    }

    // Enable promiscuous mode
    DWORD opt = 1;  // RCVALL_ON
    DWORD bytesReturned;
    if (WSAIoctl(sniffer, SIO_RCVALL, &opt, sizeof(opt), nullptr, 0, &bytesReturned, nullptr, nullptr) == SOCKET_ERROR) {
        std::cerr << "WSAIoctl failed: " << WSAGetLastError() << "\n";
        closesocket(sniffer);
        WSACleanup();
        return 1;
    }

    unsigned char buffer[65536];
    std::cout << "Sniffing started... Press Ctrl+C to stop.\n";

    while (true) {
        int recv_len = recvfrom(sniffer, (char*)buffer, sizeof(buffer), 0, nullptr, nullptr);
        if (recv_len > 0) {
            // Parse Ethernet header
            EthernetHeader* eth = (EthernetHeader*)buffer;
            unsigned short eth_proto = ntohs(eth->proto);

            std::cout << "\nEthernet Frame:\n";
            std::cout << "\tDestination MAC: " << format_mac(eth->dest_mac) << "\n";
            std::cout << "\tSource MAC: " << format_mac(eth->src_mac) << "\n";
            std::cout << "\tProtocol: " << eth_proto << "\n";

            if (eth_proto == 0x0800) {  // IPv4
                IPHeader* ip = (IPHeader*)(buffer + sizeof(EthernetHeader));
                unsigned char version = ip->ver_ihl >> 4;
                unsigned char ihl = (ip->ver_ihl & 0xF) * 4;
                std::cout << "\tIPv4 Packet:\n";
                std::cout << "\t\tVersion: " << (int)version << ", Header Length: " << (int)ihl << ", TTL: " << (int)ip->ttl << "\n";
                std::cout << "\t\tProtocol: " << (int)ip->proto << ", Source: " << format_ip(ip->src_ip) << ", Dest: " << format_ip(ip->dest_ip) << "\n";

                // TODO: Add TCP/UDP/ICMP parsing here (e.g., check ip->proto == 6 for TCP, unpack ports/flags, etc.)
                // For example, for TCP: unsigned char* transport = (unsigned char*)(buffer + sizeof(EthernetHeader) + ihl);
                // Then unpack ports, sequence, flags via bit shifts.

                // Dump remaining data
                unsigned char* data = buffer + sizeof(EthernetHeader) + ihl;
                size_t data_len = recv_len - (sizeof(EthernetHeader) + ihl);
                std::cout << "\t\tData:\n";
                hex_dump(data, data_len, "\t\t");
            } else {
                // Non-IPv4: Dump data
                unsigned char* data = buffer + sizeof(EthernetHeader);
                size_t data_len = recv_len - sizeof(EthernetHeader);
                std::cout << "\tData:\n";
                hex_dump(data, data_len, "\t");
            }
        } else if (recv_len < 0) {
            std::cerr << "recvfrom error: " << WSAGetLastError() << "\n";
        }
    }

    closesocket(sniffer);
    WSACleanup();
    return 0;
}
