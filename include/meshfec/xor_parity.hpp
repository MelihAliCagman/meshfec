#pragma once
#include <cstdint>
#include <vector>
#include <cstddef>
#include <stdexcept>

using Bytes = std::vector<uint8_t>;

inline Bytes xor_parity(const std::vector<Bytes>&paketler){
    
    if (paketler.empty())
        throw std::invalid_argument("paket listesi bos");
    for (const Bytes& p : paketler)
        if (p.size() != paketler[0].size())
            throw std::invalid_argument("paket boyutlari farkli");


    Bytes parite(paketler[0].size(),0);
    for (const Bytes& p : paketler)
        for(size_t i=0;i < p.size();i++)
        parite[i] ^= p[i];
    return parite;    
    
}
inline Bytes xor_recover(const std::vector<Bytes>& kalanlar,const Bytes& parite){
    std::vector<Bytes> hepsi = kalanlar;
    hepsi.push_back(parite);
    return xor_parity(hepsi);
}