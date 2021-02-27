#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

// 设置非阻塞
static void setnonblocking(int sockfd)
{
    int flag = fcntl(sockfd, F_GETFL, 0);
    if (flag < 0)
    {
        perror("fcntl F_GETFL fail");
        return;
    }
    if (fcntl(sockfd, F_SETFL, flag | O_NONBLOCK) < 0)
    {
        perror("fcntl F_SETFL fail");
    }
}

//读,定长
int readn(int fd, void *vptr, size_t n)
{
    /* see man 2 read */
    size_t nleft;
    int nread;
    char *ptr;

    ptr = (char *)vptr;
    nleft = n;
    while (nleft > 0)
    {
        nread = (int)read(fd, ptr, nleft);
        if (nread < 0)
        {
            if (errno == EINTR)
                nread = 0; /* call read() again */
            else
                return -1; /* maybe errno == EAGAIN */
        }
        else if (0 == nread)
        {
            break; /* EOF */
        }
        nleft -= nread;
        ptr += nread;
    }
    return (n - nleft); /* return >= 0 */
}

//写,定长
int writen(int fd, const void *vptr, size_t n)
{
    /* see man 2 write */
    size_t nleft;
    int nwritten;
    const char *ptr;

    ptr = (char *)vptr;
    nleft = n;
    while (nleft > 0)
    {
        nwritten = write(fd, ptr, nleft);
        if (nwritten <= 0)
        {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0; /* call write() again */
            else
                return (-1); /* error */
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    return (n);
}

int main()
{
    // socket
    struct sockaddr_in servaddr;
    short port = 9527;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(port);
    setnonblocking(sockfd);
    if (connect(sockfd, (sockaddr *)&servaddr, sizeof(sockaddr_in)) < 0)
    {
        if (errno != EINPROGRESS)
        {
            perror("connect fail");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }

    const char *sendbuf = "hello server!";
    for (;;)
    {

        // write
        int len = writen(sockfd, sendbuf, strlen(sendbuf));
        if (len < 0 && errno != EAGAIN)
        {
            break;
        }
        if (len > 0)
        {
            printf("fd:%d, write len:%d\n", sockfd, len);
        }

        // read
        char recvbuf[1024 + 1] = {0};
        int res = readn(sockfd, recvbuf, 1024);
        if (res < 0 && errno != EAGAIN)
        {
            break;
        }
        else if (0 == res)
        {
            break;
        }

        if (strlen(recvbuf) > 0)
        {
            printf("fd:%d, read len:%ld\n", sockfd, strlen(recvbuf));
        }

        sleep(1);
    }
    perror("close by");
    close(sockfd);
}