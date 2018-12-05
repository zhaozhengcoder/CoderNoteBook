#include <stdio.h>
#include <iostream>
#include <sys/types.h>  
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <signal.h>
 
#define MAX_MSG_SIZE 256
#define SERVER_PORT  9999
 
void handle(int arg)
{
    printf("sigpipe !!! \n");
}
 
int main()
{ 
    signal(SIGPIPE, handle);//SIGPIPE信号的处理
    
    int cli_sockfd;
    int addrlen;  
    char seraddr[] = "127.0.0.1";  
    struct sockaddr_in ser_addr,cli_addr;
    char msg[MAX_MSG_SIZE];

    cli_sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(cli_sockfd<0)
    {
        fprintf(stderr,"socker Error:%s\n",strerror(errno));  
        exit(1);  
    }  
    
    /* 初始化客户端地址*/  
    addrlen=sizeof(struct sockaddr_in);  
    bzero(&ser_addr,addrlen);  
    cli_addr.sin_family=AF_INET;  
    cli_addr.sin_addr.s_addr=htonl(INADDR_ANY);  
    cli_addr.sin_port=0;  
    if(bind(cli_sockfd,(struct sockaddr*)&cli_addr,addrlen)<0)
    {  
        fprintf(stderr,"Bind Error:%s\n",strerror(errno));  
        exit(1);  
    }  
    addrlen=sizeof(struct sockaddr_in);  
    bzero(&ser_addr,addrlen);  
    ser_addr.sin_family=AF_INET;  
    ser_addr.sin_addr.s_addr=inet_addr(seraddr);  
    ser_addr.sin_port=htons(SERVER_PORT);  

    if(connect(cli_sockfd,(struct sockaddr*)&ser_addr, addrlen)!=0)
    {  
        /*连接失败 */  
        fprintf(stderr,"Connect Error:%s\n",strerror(errno));  
        close(cli_sockfd);  
        exit(1);  
    }  

    std::cout<<"press any number begin send and recv a msg"<<std::endl;
    int num;
    std::cin>>num;

    strcpy(msg,"hi,I am client");  
    send(cli_sockfd, msg, strlen(msg),0);/*发送数据*/  
    std::cout<<"send len : "<<strlen(msg)<<std::endl;
    recv(cli_sockfd, msg, MAX_MSG_SIZE,0); /* 接受数据*/  
	printf("%s\n",msg);
	

    
    
    int option;
    int quit = 0;
    while(quit == 0)
    {
        std::cout<<std::endl;
        std::cout<<"0 : quit"<<std::endl;
        std::cout<<"1 : send"<<std::endl;
        std::cout<<"2 : recv"<<std::endl;
        std::cout<<"3 : test sigpipe "<<std::endl;
        std::cin>>option;
        switch(option)
        {
            case 0:
                quit = 1;
                break;
            case 1:
                send(cli_sockfd, msg, strlen(msg),0);/*发送数据*/  
                std::cout<<"send len : "<<strlen(msg)<<std::endl;
                break;
            case 2:		
                num = recv(cli_sockfd, msg, MAX_MSG_SIZE,0); /* 接受数据*/  
                std::cout<<"recv num : "<<num<<std::endl;
                break;
            case 3:
                // 当服务器close之后，client 连续向fd写入两次数据，会产生sigpipe信号 
                // sigpipe的信号 默认处理时退出 
                send(cli_sockfd, msg, strlen(msg),0);/*发送数据*/  
                send(cli_sockfd, msg, strlen(msg),0);/*发送数据*/  
                break;

        }
    }

   
    close(cli_sockfd);
    return 0;  
}  

