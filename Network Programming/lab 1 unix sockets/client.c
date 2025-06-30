#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define SOCKET_PATH "/tmp/unnix_socket"

int main() {
    int client_fd;
    struct sockaddr_un server_addr;

    if ((client_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(client_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    char buffer[1024];
    int client_id = 1;
    while (1) {
        printf("Enter message for client %d ('close' to disconnect): ", client_id);
        fgets(buffer, sizeof(buffer), stdin);

        if (strncmp(buffer, "close", 5) == 0) {
            break;
        }

        send(client_fd, buffer, strlen(buffer), 0);
        recv(client_fd, buffer, sizeof(buffer), 0);
        printf("Server response: %s\n", buffer);
    }

    close(client_fd);
    return 0;
}