# PortScanner
C++-based Nmap front-end scanner

PortScanner
PortScanner is a command-line tool that utilizes Nmap to scan a target IP or domain for open ports and system information. It provides multiple scan options, making it a useful learning project for understanding network scanning techniques.

Features
Multiple Scan Modes:

SYN Scan (-sS) – Checks for open ports using a stealth scan.

Service Detection (-sS -sV) – Identifies services running on open ports.

OS Detection (-sS -O) – Attempts to determine the target's operating system.

Aggressive Scan (-A) – Combines multiple scanning techniques for detailed results.

User-Friendly CLI – Simple and interactive command-line interface.

Saves Scan Results – Outputs scan results to scan_results.txt.

Windows Compatibility – Designed to run on Windows systems with Nmap installed.

Installation
1. Install Nmap
Ensure Nmap is installed before running the program.

2. Clone the Repository

3. Build the Program
Using Visual Studio
Open PortScanner.sln in Visual Studio.
Set to Release Mode.
Click Build → Build Solution.


Legal Disclaimer
This tool is intended for educational purposes only.
Unauthorized scanning of networks without permission may be illegal in certain jurisdictions.
Use this tool only on networks that you own or have explicit permission to scan.

Contributing
Contributions are welcome. Feel free to submit issues, feature requests, or pull requests.

License
This project is licensed under the Apache License 2.0. See LICENSE for details.
