#include <cstdio>
#include "meshfec/channel.hpp"

int main(){
    const int kare_sayisi=10000;
    const int paket_sayisi = 25;
    LossChannel kanal(0.05,42);
    int ulasan = 0;

    for(int k=0;k<kare_sayisi;k++){

        bool tamam = true;

        for(int p=0;p<paket_sayisi;p++)

            if (!kanal.deliver()) 
            tamam=false;
            {}

        if(tamam){
            ulasan++;
        }
                  
    }
    printf("%d kareden %d tanesi ulasti(%%%.1f)\n",
        kare_sayisi,ulasan,100.0*ulasan/kare_sayisi); 
}