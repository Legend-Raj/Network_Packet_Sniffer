# 🕵️♂️ Network Packet Sniffer

A powerful network packet sniffer built in Python and C++, leveraging raw sockets to capture, parse, and analyze network traffic in real-time. This tool lets you dive deep into protocols like Ethernet, IPv4, ICMP, TCP, and UDP, making it ideal for debugging, learning networking concepts, or exploring cybersecurity basics.

## 🌟 Features

- 📡 **Real-Time Packet Capture**: Continuously monitors and captures incoming and outgoing network packets
- 📝 **Detailed Packet Parsing**: Breaks down Ethernet frames (source/destination MAC, protocol), IPv4 headers (TTL, source/destination IP), and transport layers like TCP flags, UDP ports, or ICMP types
- 🕸️ **Multi-Protocol Support**: Handles Ethernet, IPv4, ICMP, TCP, UDP, and more, with human-readable output for easy analysis
- 🔍 **Cross-Language Implementation**: Available in Python for simplicity and C++ for performance, with similar functionality across both
- 🚀 **Educational Focus**: Perfect for understanding the OSI model (Layers 2-4) through hands-on packet dissection

## 🛠️ Installation & Setup

### 1. Clone the Repository
```bash
git clone https://github.com/legendking-sudo/Network_Packet_Sniffer.git
cd Network_Packet_Sniffer
```

### 2. Prerequisites

#### Python Version
- **Python 3.x** (uses built-in modules like `socket`, `struct`, and `textwrap`—no external dependencies needed)
- Run as administrator/root for raw socket access

#### C++ Version
- A C++ compiler (e.g., g++ or Visual Studio)
- Winsock support on Windows or POSIX sockets on Linux/macOS
- Run as administrator/root for raw socket access

### 3. Running the Sniffer

#### Python Implementation
```bash
sudo python3 main.py
```

#### C++ Implementation
```bash
# On Windows
g++ Network_sniffer.cpp -o sniffer -lws2_32
sudo ./sniffer

# On Linux/macOS
g++ Network_sniffer.cpp -o sniffer
sudo ./sniffer
```

### ⚠️ Important Notes
- **Requires superuser privileges** to access raw sockets
- For best results, run in an IDE like PyCharm or VS Code
- **Wait at least 10 seconds** after starting for proper initialization
- **To generate traffic for testing**: Connect your PC to mobile data (tethering), then use internet on your mobile (e.g., open YouTube, send WhatsApp messages, or browse Google). This triggers packet movement that the sniffer can capture

## 🔍 Usage

Launch the script, and it will enter an infinite loop, printing detailed packet information to the console.

### Example Output
```
Ethernet Frame:
    - Destination: 01:23:45:67:89:AB, Source: 11:22:33:44:55:66, Protocol: 8

IPv4 Packet:
    - Version: 4, Header Length: 20, TTL: 64
    - Protocol: 6, Source: 192.168.1.5, Target: 93.184.216.34

TCP Segment:
    - Source Port: 54321, Destination Port: 80
    - Sequence: 123456789, Acknowledgement: 987654321
    - Flags: URG: 0, ACK: 1, PSH: 0, RST: 0, SYN: 1, FIN: 0
```

### Stopping the Sniffer
Use `Ctrl+C` to stop the packet capture. You can customize the tool by adding filters or logging capabilities for advanced use cases.

## 🚀 Project Structure

```
📂 Network_Packet_Sniffer/
├── 📄 main.py              # Python implementation with packet parsing logic
├── 📄 Network_sniffer.cpp  # C++ implementation for raw socket sniffing
└── 📄 README.md            # This documentation file
```

## 📚 How It Works

### 1. Socket Setup
Creates a raw socket bound to the host's IP, enabling promiscuous mode to capture all network traffic passing through the interface.

### 2. Packet Capture Loop
Receives raw data packets (up to 65KB) and processes them layer by layer using network protocol specifications.

### 3. Dissection Process

#### Ethernet Layer (Layer 2)
- Extracts source and destination MAC addresses
- Identifies the next protocol type (IPv4, IPv6, ARP, etc.)

#### IPv4 Layer (Layer 3)
- Parses IP version, header length, and Time To Live (TTL)
- Extracts source and destination IP addresses
- Identifies transport protocol (TCP, UDP, ICMP)

#### Transport Layer (Layer 4)
- **ICMP**: Extracts message type and code
- **TCP**: Parses port numbers, sequence numbers, acknowledgment numbers, and control flags
- **UDP**: Extracts source/destination ports and payload length

### 4. Output Formatting
Displays information in a structured, indented format with optional hex dumps for packet payloads, making it easy to understand the packet structure.

The C++ version mirrors this logic using Winsock/POSIX APIs with manual byte manipulation for enhanced performance.

## 🎓 Educational Value

This tool is excellent for:
- **Network Protocol Learning**: Understand how TCP/IP stack works in practice
- **Cybersecurity Education**: Learn about network traffic analysis and monitoring
- **Debugging Network Issues**: Identify connectivity problems and protocol-level errors
- **OSI Model Visualization**: See layers 2-4 of the OSI model in action

## 🔧 Customization Options

You can extend this tool by:
- Adding packet filtering based on IP addresses, ports, or protocols
- Implementing packet logging to files for later analysis
- Creating a GUI interface for easier use
- Adding support for IPv6 and other protocols
- Implementing statistical analysis of captured traffic

## ⚠️ Legal Disclaimer

**This tool is for educational and personal use only.** Network packet sniffing can raise privacy and legal concerns. Always ensure you have proper authorization before using this tool on any network. Key points:

- Only use on networks you own or have explicit permission to monitor
- Comply with local laws and regulations regarding network monitoring
- Respect privacy and confidentiality of network traffic
- Not intended for malicious purposes or unauthorized surveillance

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/amazing-feature`
3. **Commit your changes**: `git commit -m 'Add amazing feature'`
4. **Push to the branch**: `git push origin feature/amazing-feature`
5. **Open a Pull Request**

### Suggested Improvements
- IPv6 protocol support
- GUI interface development
- Packet filtering capabilities
- Performance optimizations
- Cross-platform compatibility enhancements

## 🐛 Troubleshooting

### Common Issues

**Permission Denied Error**
- Ensure you're running with administrator/root privileges
- On Linux: Use `sudo` before the command

**No Packets Captured**
- Wait at least 10 seconds after starting
- Generate network traffic by browsing the internet or using mobile tethering
- Check if your network interface supports promiscuous mode

**Compilation Errors (C++)**
- Ensure you have the correct libraries linked (`-lws2_32` on Windows)
- Verify your compiler supports C++11 or later

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

```
MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
```

## 🧑‍💻 Author

- **Piyush Raj** - [GitHub Profile](https://github.com/Legend-Raj)

## 🙏 Acknowledgments

- Thanks to the open-source community for networking libraries and documentation
- Inspired by classic network analysis tools like Wireshark and tcpdump
- Educational resources on network protocols and socket programming

## 📞 Support

If you encounter any issues or have questions:
1. Check the [Issues](https://github.com/legendking-sudo/Network_Packet_Sniffer/issues) section
2. Create a new issue with detailed information about your problem
3. Include your operating system, Python/C++ version, and error messages

---

⭐ **Star this repository if you found it helpful!** ⭐
