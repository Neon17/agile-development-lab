#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define SOCKET_PATH "/tmp/unnix_socket"

void handle_client(int client_fd, int *client_count)
{
    char buffer[1024];
    while (1)
    {
        recv(client_fd, buffer, sizeof(buffer), 0);
        printf("Client %d message = %s\n", *client_count, buffer);

        if (strncmp(buffer, "close", 5) == 0)
        {
            close(client_fd);
            (*client_count)--;
            printf("Total Clients Connected = %d\n", *client_count);
            return;
        }

        if (strncmp(buffer, "hello", 5) == 0)
        {
            strcpy(buffer, "Hello, I am your chat assistant. How can I help you today?");
            send(client_fd, buffer, strlen(buffer), 0);
        }

        else if (strncmp(buffer, "are you feeling good?", 18) == 0)
        {
            strcpy(buffer, "Yes, I am feeling good. How can I help you today?");
            send(client_fd, buffer, strlen(buffer), 0);
        }
        else if (strncmp(buffer, "create me c++ program to print hello world", 37) == 0)
        {
            strcpy(buffer, "Sure, here's the code:\n\n#include <iostream>\n\nint main() {\n    std::cout << \"Hello, World!\" << std::endl;\n    return 0;\n}\n");
            send(client_fd, buffer, strlen(buffer), 0);
        }
        else {
            strcpy(buffer, "Hello Hi, I am your chat assistant. How can I help you today.");
            send(client_fd, buffer, strlen(buffer), 0);
        }
    }
}

int main()
{
    int server_fd, client_fd;
    struct sockaddr_un server_addr;
    socklen_t addr_size = sizeof(server_addr);
    int client_count = 0;

    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    unlink(SOCKET_PATH);
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    listen(server_fd, 5);
    printf("Server listening on %s\n", SOCKET_PATH);

    while (1)
    {
        client_fd = accept(server_fd, (struct sockaddr *)&server_addr, &addr_size);
        if (client_fd == -1)
        {
            perror("accept");
            continue;
        }

        client_count++;
        printf("Total Clients Connected = %d\n", client_count);

        handle_client(client_fd, &client_count);
    }

    close(server_fd);
    return 0;
}