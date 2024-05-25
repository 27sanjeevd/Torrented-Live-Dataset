#include <iostream>
#include <cstdlib>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

struct Node {
    std::string address;
    int port;

    Node(std::string a, int b) : address(a), port(b) {}
};

struct File {
    int numRows, numColumns;
    std::vector<Node> nodes;
};



enum class MessageType {
    JOIN_NETWORK = 1,
    CONTRIBUTE_SIZE = 2
};

struct MessageHeader {
    MessageType type;
    int dataSize;
};

struct JoinNetwork {
    int fileNum;
};

const int PORT = 8080;
const int BUFFER_SIZE = 1024;
int server_fd = 0;
std::unordered_map<int, File> fileData;
std::unordered_set<std::string, Node*> nodeList;


void server_run() {
    struct sockaddr_in client_addr = {0};
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    while (true) {
        int valread = recvfrom(server_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *) &client_addr, &addr_len);
        if (valread < 0) {
            perror("Receive failed");
            continue;
        }

        std::string client_address = inet_ntoa(client_addr.sin_addr), client_port = std::to_string(ntohs(client_addr.sin_port));
        MessageHeader* header = reinterpret_cast<MessageHeader*>(buffer);

        switch (header->type) {
            case MessageType::JOIN_NETWORK: {
                if (header->dataSize != sizeof(JoinNetwork)) {
                    std::cerr << "Invalid message size for file request" << std::endl;
                    return;
                }
            }

        }


    }
}



int start_server_socket() {
    int new_socket;
    struct sockaddr_in server_addr = {0};

    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << std::endl;
}



int main() {
    start_server_socket();


}