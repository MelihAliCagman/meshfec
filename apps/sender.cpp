#include <arpa/inet.h>
#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

int main(){
    int fd = socket(AF_INET,SOCK_DGRAM,0);
    if(fd < 0){
        perror("socket");
        return 1;
    }
    sockaddr_in dest{};
    dest.sin_family = AF_INET;
    dest.sin_port=htons(9000);
    inet_pton(AF_INET,"127.0.0.1",&dest.sin_addr);

    const char* msg = "merhaba";
    ssize_t n = sendto(fd,msg,strlen(msg),0,
        (sockaddr*)&dest,sizeof(dest));

    if(n<0){
        perror("sendto");
        return 1;
    }
    printf("%zd bayt gonderildi \n",n);
    close(fd);
    return 0;    

}