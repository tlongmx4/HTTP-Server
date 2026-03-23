#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int start_listening() {
    printf("Listening for incoming connections...\n");
    // Simulate listening for connections
    return 0; // Return 0 to indicate success
}

int main() {
    printf("Starting the server...\n");
    if (start_listening() != 0) {
        fprintf(stderr, "Failed to listen for connection.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}