#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

// Function to execute Nmap and capture results
/**
 * Executes an Nmap scan based on the selected scan type.
 * @param ip - The target IP or domain name.
 * @param startPort - The starting port for the scan (used for port-based scans).
 * @param endPort - The ending port for the scan (used for port-based scans).
 * @param scanType - The type of scan selected by the user.
 * @return A vector containing the raw output lines from Nmap.
 */
std::vector<std::string> runNmapScan(const std::string& ip, int startPort, int endPort, const std::string& scanType) {
    std::vector<std::string> results;
    std::ostringstream command;

    // Constructing the Nmap command based on user selection
    if (scanType == "SYN") {
        command << "nmap -sS -p " << startPort << "-" << endPort << " " << ip;
    }
    else if (scanType == "SERVICE") {
        command << "nmap -sS -sV -p " << startPort << "-" << endPort << " " << ip;
    }
    else if (scanType == "OS") {
        command << "nmap -sS -O " << ip;
    }
    else if (scanType == "AGGRESSIVE") {
        command << "nmap -A -p " << startPort << "-" << endPort << " " << ip;
    }
    else {
        std::cerr << "[-] Invalid scan type selected.\n";
        return results;
    }

    std::cout << "[DEBUG] Running: " << command.str() << std::endl;

    // Open a pipe to execute the command and capture the output
    FILE* pipe = _popen(command.str().c_str(), "r");
    if (!pipe) {
        std::cerr << "[-] Failed to execute Nmap.\n";
        return results;
    }

    // Read Nmap output line by line
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        results.emplace_back(buffer);
    }
    _pclose(pipe);

    return results;
}

// Function to parse Nmap output (extracting open ports and system details)
/**
 * Parses the raw Nmap output to extract relevant scan results.
 * Filters lines containing "open", "Running:", or "OS details:".
 * @param nmapOutput - The raw output from the Nmap command.
 * @return A vector containing only the relevant parsed lines.
 */
std::vector<std::string> parseNmapResults(const std::vector<std::string>& nmapOutput) {
    std::vector<std::string> filteredResults;

    for (const auto& line : nmapOutput) {
        if (line.find("open") != std::string::npos ||
            line.find("Running:") != std::string::npos ||
            line.find("OS details:") != std::string::npos) {
            filteredResults.push_back(line);
        }
    }

    return filteredResults;
}

// Function to scan a range of ports using Nmap and save results to a file
/**
 * Runs the Nmap scan, processes the output, and saves results to a file.
 * @param ip - The target IP or domain name.
 * @param startPort - The starting port for the scan (if applicable).
 * @param endPort - The ending port for the scan (if applicable).
 * @param scanType - The type of scan selected by the user.
 */
void scanRange(const std::string& ip, int startPort, int endPort, const std::string& scanType) {
    // Execute Nmap and get raw results
    std::vector<std::string> nmapOutput = runNmapScan(ip, startPort, endPort, scanType);

    // Parse results to extract relevant information
    std::vector<std::string> scanResults = parseNmapResults(nmapOutput);

    // Save results to a file
    std::ofstream outputFile("scan_results.txt");
    std::cout << "\n\n======= Scan Summary =======\n";
    for (const auto& result : scanResults) {
        std::cout << result;
        outputFile << result;
    }
    outputFile.close();
}

int main() {
    std::string target;
    int startPort = 0, endPort = 0;
    std::string scanType;

    // Get user input for the target IP or domain
    std::cout << "Enter target (IP or domain): ";
    std::cin >> target;

    // Display scan type menu
    std::cout << "Select scan type: \n"
        << "1) SYN Scan (-sS)\n"
        << "2) Service Detection (-sS -sV)\n"
        << "3) OS Detection (-sS -O)\n"
        << "4) Aggressive Scan (-A)\n"
        << "Enter choice (1-4): ";

    int choice;
    std::cin >> choice;

    // Map user input to corresponding scan type
    switch (choice) {
    case 1:
        scanType = "SYN";
        break;
    case 2:
        scanType = "SERVICE";
        break;
    case 3:
        scanType = "OS";
        break;
    case 4:
        scanType = "AGGRESSIVE";
        break;
    default:
        std::cerr << "[-] Invalid selection. Exiting.\n";
        return 1;
    }

    // If not an OS scan, prompt user for port range
    if (scanType != "OS") {
        std::cout << "Start port: ";
        std::cin >> startPort;
        std::cout << "End port: ";
        std::cin >> endPort;
    }

    // Start scanning process
    std::cout << "[INFO] Running " << scanType << " scan on " << target << std::endl;
    scanRange(target, startPort, endPort, scanType);
    std::cout << "[INFO] Scan complete! Results saved to scan_results.txt\n";

    return 0;
}
