#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    printf("Starting the server...\n");
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        fprintf(stderr, "Failed to create socket.\n");
        return EXIT_FAILURE;
    }
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(8080)
    };

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        fprintf(stderr, "Failed to bind socket.\n");
        close(server_fd);
        return EXIT_FAILURE;
    }

    listen(server_fd, 3);

    printf("Listening for incoming connections on port 8080...\n");

    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            fprintf(stderr, "Failed to accept connection.\n");
            continue;
        }

        char buffer[1024] = {0};
        read(client_fd, buffer, sizeof(buffer) - 1);
        printf("Received message: %s\n", buffer);

        const char *response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 13\r\n"
            "\r\n"
            "Hello, World!";

        write(client_fd, response, strlen(response));

        close(client_fd);
    }

    close(server_fd);
    return EXIT_SUCCESS;
}