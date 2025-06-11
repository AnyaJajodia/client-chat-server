#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "util.h"


int client_socket = -1;
char username[MAX_NAME_LEN + 1];
char inbuf[BUFLEN + 1];
char outbuf[MAX_MSG_LEN + 1];

int prompt_displayed = 0;

void print_prompt() {
    if (!prompt_displayed && isatty(STDIN_FILENO)) {
        printf("[%s]: ", username);
        fflush(stdout);
        prompt_displayed = 1;
    }
}

int handle_stdin() {
    prompt_displayed = 0;
    if (!fgets(outbuf, sizeof(outbuf), stdin)) return 0;

    size_t len = strlen(outbuf);
    if (outbuf[len - 1] == '\n') {
        outbuf[len - 1] = '\0';
    } else {
        fprintf(stderr, "Sorry, limit your message to 1 line of at most %d characters.\n", MAX_MSG_LEN);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        print_prompt();
        return 0;
    }

    if (strlen(outbuf) == 0) {
        print_prompt();
        return 0;
    }

    if (send_with_length(client_socket, outbuf, strlen(outbuf) + 1) == -1) {
        fprintf(stderr, "Error: Failed to send message. %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (strcmp(outbuf, "bye") == 0) {
        printf("Goodbye.\n");
        close(client_socket);
        exit(EXIT_SUCCESS);
    }

    print_prompt();
    return 0;
}

int handle_client_socket() {
    prompt_displayed = 0;
    int bytes = recv_with_length(client_socket, inbuf, sizeof(inbuf));

    if (bytes == -1 && errno != EINTR) {
        fprintf(stderr, "Warning: Failed to receive incoming message.\n");
        return 0;
    }

    if (bytes == 0) {
        fprintf(stderr, "\nConnection to server has been lost.\n");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    if (strcmp(inbuf, "bye") == 0) {
        printf("\nServer initiated shutdown.\n");
        close(client_socket);
        exit(EXIT_SUCCESS);
    }

    printf("\n%s\n", inbuf);
    print_prompt();
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server IP> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) != 1) {
        fprintf(stderr, "Invalid IP address: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    int port = atoi(argv[2]);
    if (port < 1024 || port > 65535) {
        fprintf(stderr, "Invalid port number: %d\n", port);
        return EXIT_FAILURE;
    }

    printf("Enter your username: ");
    while (1) {
        if (fgets(username, sizeof(username), stdin) == NULL) {
            fprintf(stderr, "Error: Failed to read username. %s\n", strerror(errno));
            return EXIT_FAILURE;
        }

        int too_long = 0;
        if (strchr(username, '\n') == NULL) {
            too_long = 1;
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
        } else {
            username[strcspn(username, "\n")] = '\0';
        }

        if (too_long || strlen(username) > MAX_NAME_LEN) {
            printf("Sorry, limit your username to %d characters.\n", MAX_NAME_LEN);
            printf("Enter your username: ");
            continue;
        }

        if (strlen(username) == 0) {
            printf("Enter your username: ");
            continue;
        }

        break;
    }

    printf("Hello, %s. Let's try to connect to the server.\n", username);

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        fprintf(stderr, "Error: Failed to create socket. %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        fprintf(stderr, "Error: Failed to connect to server. %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    int bytes = recv_with_length(client_socket, inbuf, sizeof(inbuf));
    if (bytes == 0) {
        fprintf(stderr, "Error: Server closed the connection unexpectedly.\n");
        return EXIT_FAILURE;
    } else if (bytes == -1) {
        fprintf(stderr, "Error: Failed to receive welcome message. %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    printf("\n%s\n\n", inbuf);

    if (send_with_length(client_socket, username, strlen(username) + 1) == -1) {
        fprintf(stderr, "Error: Failed to send username. %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    print_prompt();

    fd_set fds;
    while (1) {
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(client_socket, &fds);
        int maxfd = client_socket > STDIN_FILENO ? client_socket : STDIN_FILENO;

        if (select(maxfd + 1, &fds, NULL, NULL, NULL) == -1 && errno != EINTR) {
            fprintf(stderr, "Error: select() failed. %s\n", strerror(errno));
            return EXIT_FAILURE;
        }

        if (FD_ISSET(STDIN_FILENO, &fds)) {
            handle_stdin();
        }

        if (FD_ISSET(client_socket, &fds)) {
            handle_client_socket();
        }
    }

}
//final commit 