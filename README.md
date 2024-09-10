

---

# 🕵️‍♂️ Network Packet Sniffer

A powerful Python-based network packet sniffer built using raw sockets, designed to capture, parse, and analyze network traffic. This tool enables you to dig deep into network protocols like Ethernet, IPv4, and others to uncover packet-level details for debugging or learning purposes.

## 🌟 Features

- 📡 **Real-time Packet Capture**: Continuously sniffs network packets across various protocols.
- 📝 **Detailed Packet Information**: Extracts and displays Ethernet frame information (source/destination MAC, protocol type), IPv4 headers, and more.
- 🕸️ **Layered Network Analysis**: Supports Ethernet and IP-level protocol dissection.
- 🔍 **Flexible Packet Monitoring**: Listens to all incoming and outgoing traffic on the host machine.

## 🛠️ Installation & Setup

1. **Clone the repository**:
   ```bash
   git clone https://github.com/legendking-sudo/Network_Packet_Sniffer.git
   cd network-packet-sniffer
   ```

2. **Install dependencies**:
   - Ensure you have Python 3.x installed.
   - This script relies on Python's built-in `socket` module, so no additional dependencies are required.

3. **Run the sniffer**:
   ```bash
   sudo python3 main.py
   ```

   > **Note**: The script requires superuser privileges to capture network traffic using raw sockets.

## 🔍 Usage

Once the sniffer is running, it will continuously capture and print out details for each packet, such as:

- 🖥️ **Source and Destination MAC Addresses**
- 🌐 **Protocol Information**
- 🚀 **Packet Headers**

You'll see outputs like:

```
Ethernet Frame:
    Destination: 01:23:45:67:89:ab, Source: 11:22:33:44:55:66, Protocol: 8
IPv4 Packet:
    Source: 192.168.1.5, Destination: 93.184.216.34, TTL: 64
```

## 🚀 Project Structure

```
📂 network-packet-sniffer/
├── 📄 main.py        # Main sniffer logic and packet parsing
└── 📄 README.md      # This README file
```

## 📚 How It Works

1. **Raw Sockets**: The sniffer creates a raw socket that binds to the host's IP address and listens for all incoming traffic.
2. **Packet Dissection**: It reads raw data from the network interface, extracts Ethernet and IP-level packet information, and displays it in a human-readable format.
3. **Continuous Capture**: The sniffer runs in an infinite loop, capturing traffic as it arrives.

## ⚠️ Disclaimer

This project is intended for educational purposes only. Capturing network traffic may violate network privacy policies, so **ensure you have permission** before using it on any network.

## 🛡️ License

This project is licensed under the MIT License. See the [LICENSE](./LICENSE) file for details.

---

## 🧑‍💻 Author

- **Piyush Raj** - [GitHub](https://github.com/Legend-Raj)

---
