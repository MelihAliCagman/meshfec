#include <cstdio>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int main(){
    int fd = socket(AF_INET,SOCK_DGRAM,0);
    if(fd < 0){
        perror("socket");
        return 1;
    }
    sockaddr_in addr{};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(9000);
    addr.sin_addr.s_addr=INADDR_ANY;
    if(bind(fd,(sockaddr*)&addr,sizeof(addr))<0){
        perror("bind");
        return 1;
    }
    printf("9000 portu dinleniyor\n");

    char buf[1500];
    sockaddr_in from{};

    socklen_t len=sizeof(from);

    ssize_t n = recvfrom(fd, buf, sizeof(buf),0,(sockaddr*)&from,&len);
    
    if(n<0){
        perror("recvfrom");
        return 1 ;
    }

    printf("%zd bayt geldi,gonderen port=%d\n",n,ntohs(from.sin_port));

    close(fd);
    
    return 0;
}