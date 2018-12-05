
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include <signal.h>

#define  EHCO_PORT         9999
#define  MAX_CLIENT_NUM    10

void handle(int arg)
{
    printf("sigpipe\n");
}

int main()
{
    signal(SIGPIPE, handle);//SIGPIPE信号的处理

    int socketfd;
    socketfd = socket(AF_INET, SOCK_STREAM, 0);       
    if (socketfd == - 1)
    {
        printf("errno=%d ", errno);
        exit(1);    
    }
    else     
    {
        printf("socket create successfully ");        
    }

    struct sockaddr_in sa;
    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(EHCO_PORT);
    sa.sin_addr.s_addr = htons(INADDR_ANY);
    bzero(&(sa.sin_zero), 8);

    if (bind(socketfd, (struct sockaddr *)&sa, sizeof(sa)) != 0)
    {
        printf("bind failed ");
        printf("errno=%d ", errno);
        exit(1);  
    }
    else     
    {
        printf("bind successfully ");     
    }
    //listen
    if (listen(socketfd , MAX_CLIENT_NUM) != 0)
    {
        printf("listen error ");
        exit(1);      
    }
    else     
    {
        printf("listen successfully ");  
    }

    int clientfd;
    struct sockaddr_in clientAdd;
    char buff[101];
    socklen_t len = sizeof(clientAdd);
    int closing = 0;

    if((clientfd = accept(socketfd, (struct sockaddr *)&clientAdd, & len)) > 0)
    {
        int n = recv(clientfd, buff, 100, 0 );
        write(STDOUT_FILENO, buff, n);
        send(clientfd, buff, n, 0);

        int option = 0;
        int quit = 0;
        int send_ret;
        int recv_ret;
        
        while(quit == 0)
        {
            std::cout<<std::endl;
            std::cout<<"0 : close"<<std::endl;
            std::cout<<"1 : send"<<std::endl;
            std::cout<<"2 : recv"<<std::endl;
            std::cout<<"3 : quit"<<std::endl;
            std::cin>>option;

            switch(option)
            {
                case 0:
                    close(clientfd);
                    break;
                case 1:
                    send_ret = send(clientfd, buff, n, 0);
                    std::cout<<send_ret<<std::endl;
                    break;
                case 2:
                    recv_ret = recv(clientfd, buff, 100, 0 );
                    std::cout<<recv_ret<<std::endl;
                    break;
                case 3:
                    quit = 1;
                    break;
            }   
        }
        return 0;
    }
    else
    {
        std::cout<<"accept error "<<std::endl;
        exit(0);
    }
}
