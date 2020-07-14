函数详情

atoi 将字符串转化为int
int atoi (const char * str)
atol 将字符串转化为long
long int atol ( const char * str )

扩展实例

Server_epoll.cc
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

//#include <memory.h>  //menset
#include <sys/epoll.h>
#include <fcntl.h>

#define SOCKET_PORT 9999
#define EPOLL_SIZE 10

int main(int argc, char *argv[])
{
    int server_fd;
    int client_fd;
    int epfd;
    
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    
    if (argc == 2){
        addr.sin_addr.s_addr = inet_addr(argv[1]);
        addr.sin_port = htons(SOCKET_PORT);
    }else if(argc==3){
        addr.sin_addr.s_addr = inet_addr(argv[1]);
        addr.sin_port = htons(atoi(argv[2]));
    }else{
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(SOCKET_PORT); 
    }
    
    server_fd = socket(PF_INET,SOCK_STREAM,0);
    if (server_fd < 0){
        std::cout<<"Create Socket Errors, "<<server_fd<<std::endl;
        exit(server_fd);
    }
    
    if (bind(server_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr)) < 0) 
    {
        perror("bind error");
        return -1;
    }
    
    if (listen(server_fd, 10)<0)
    {
        perror("listen error");
        return -1;
    }else{
        printf("Stared the Socket: %s:%d\n",
               inet_ntoa(addr.sin_addr),
               ntohs(addr.sin_port));
    }
    
    epfd = epoll_create(EPOLL_SIZE);
    if (epfd < 0)
    {
        perror("Epoll Create");
        exit(-1);
    }
    
    struct epoll_event ev;
    struct epoll_event events[EPOLL_SIZE];
    ev.data.fd = server_fd;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &ev);
    fcntl(server_fd, F_SETFL, fcntl(server_fd, F_GETFD, 0)| O_NONBLOCK);
    
    while (1)
    {
        int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
        if (epoll_events_count < 0)
        {
            perror("epoll failed");
            break;
        }
        printf("epoll_events_count = %d\n", epoll_events_count);
        for (int i=0;i < epoll_events_count;i++)
        {
            if (events[i].data.fd==server_fd&&(events[i].events & EPOLLIN))
            {
                struct sockaddr_in remote_addr;
                
                socklen_t socklen = sizeof(struct sockaddr_in);
                client_fd = accept(server_fd, (struct sockaddr *)&remote_addr, &socklen);
                if (client_fd < 0)
                {
                    perror("accept error");
                }
                printf("client connection from: %s : % d(IP : port), "
                       "clientfd = %d \n",
                       inet_ntoa(remote_addr.sin_addr),
                       ntohs(remote_addr.sin_port),
                       client_fd);
                
                ev.data.fd = client_fd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev);
                
                fcntl(client_fd, F_SETFL,
                      fcntl(client_fd, F_GETFD, 0)| O_NONBLOCK);
                send(client_fd,"Welcome to My server",21,0);
            }else{ 
                char buffer[1024];
                int len;
                if ((len=recv(events[i].data.fd,buffer,sizeof(buffer), 0))>0)
                {
                    send(events[i].data.fd,"Welcome to My server\n",21,0);
                    printf("%s fd %d \n",buffer,events[i].data.fd);
                    
                    //close(client_fd);
                }else{
                    printf("client offline with: "
                           "clientfd = %d \n",
                           events[i].data.fd);
                }
            }
        }
    }
    close(server_fd);
    close(epfd);
    return 0;                                                                   
}
Client_epoll.cc

#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

//#include <memory.h>  //menset
#include <sys/epoll.h>
#include <fcntl.h>

#define EPOLL_SIZE 10

int main(int argc, char *argv[])
{
    int size;
    int client_fd;
    
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    
    if (argc == 3){
        addr.sin_addr.s_addr = inet_addr(argv[1]);
        addr.sin_port = htons(atoi(argv[2]));
    }else{
        printf("The host ip and port is falied.\n");
        exit(-1);
    }
    
    client_fd = socket(PF_INET,SOCK_STREAM,0);
    
    if (client_fd < 0){
        std::cout<<"Create Socket Errors, "<<client_fd<<std::endl;
        exit(client_fd);
    }
    
    size = connect(client_fd, (struct sockaddr *)&addr,
                   sizeof(struct sockaddr));
    if (size < 0)
    {
        perror("connect error");
    }
    printf("Connect client: %s:%d \n",inet_ntoa(addr.sin_addr),
           ntohs(addr.sin_port));
    
    int epfd;
    epfd = epoll_create(EPOLL_SIZE);
    struct epoll_event ev;
    
    ev.data.fd = client_fd;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd, &ev);
    fcntl(client_fd, F_SETFL, fcntl(client_fd, F_GETFD, 0)| O_NONBLOCK);
    
    char buffer[1024];
    struct epoll_event events[EPOLL_SIZE];
    
    int len;
    while (1)
    {
        int epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
        if (epoll_events_count<0)
        {
            perror("Epoll wait");
            exit(-1);
        }
        
        for (int i=0;i<epoll_events_count;i++)
        {
            printf("client fd %d, event fd %d \n",client_fd,
                   events[i].data.fd);
            len = recv(client_fd, buffer, sizeof(buffer), 0);
            if (len > 0)
            {
                printf("%s",buffer);
            }
            sleep(3);
            send(client_fd,"Welcome to My client",21,0);
        }
    }
    return 0;
}

作者：_艾_斯_
链接：https://www.jianshu.com/p/b319c5cadba2
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。