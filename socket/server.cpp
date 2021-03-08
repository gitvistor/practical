#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BACKLOG 1
#define MSGLEN 16
char msg[MSGLEN] = "welcome";

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("usage: %s ip port\n", basename(argv[0]));
        exit(1);
    }

    int listenfd, connectfd;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket() error.");
        exit(1);
    }

    int opt = 1;

    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in server, client;

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    if (bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("bind() error");
        exit(1);
    }

    if (listen(listenfd, BACKLOG) == -1)
    {
        perror("listen() error.\n");
        exit(1);
    }

    socklen_t addrlen = sizeof(client);

    while (1)
    {
        if ((connectfd = accept(listenfd, (struct sockaddr *)&client, &addrlen)) == -1)
        {
            perror("accept() error\n");
            exit(1);
        }

        printf("got a client, ip: %s, port: %d\n",
               inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        send(connectfd, msg, MSGLEN, 0);

        printf("colse after send a msg\n");
        close(connectfd);
    }

    close(listenfd);

    return 0;
}