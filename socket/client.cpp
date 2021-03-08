#include <stdio.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFERSIZE 100

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("usage: %s ip port\n", basename(argv[0]));
        exit(1);
    }

    int sockfd, num;
    char buf[BUFFERSIZE];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket() error\n");
        exit(1);
    }

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        printf("connect() error\n");
        exit(1);
    }

    if ((num = recv(sockfd, buf, BUFFERSIZE, 0)) == -1)
    {
        printf("recv() error\n");
        exit(1);
    }
    buf[num - 1] = '\0';
    
    printf("server message: %s\n", buf);
    printf("byebye\n");

    close(sockfd);

    return 0;
}