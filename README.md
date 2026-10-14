# meshfec

Taktik mesh ağlar için **kayba dayanıklı veri/video iletimi**: UDP üzerinde ileri hata düzeltme
(FEC, Reed-Solomon), kayıplı kanal simülasyonu ve ileride ad-hoc yönlendirme. C++17, harici
bağımlılık yok.

> **Durum: geliştirme sürüyor.** Proje, adım adım ve öğrenilerek yazılıyor. Her adım kendi testiyle
> birlikte ilerliyor. Güncel durum aşağıdaki tabloda ve [`YOL_HARITASI.md`](YOL_HARITASI.md) dosyasında.

## Problem

Taktik mesh ağlarda düğümler birbirine doğrudan bağlanır ve bağlantılar kayıplıdır. Canlı video gibi
zamanlı veride TCP uygun değildir: kayıp pakette yeniden gönderim yapar ve sırayı korumak için
sonraki paketleri bekletir, gecikme artar. UDP hızlıdır ama paketin ulaşmasını garanti etmez.

Bir video karesi çoğu zaman onlarca pakete bölünür ve **ancak tüm paketleri ulaşırsa** çözülebilir.
Bu yüzden küçük paket kayıpları bile kareleri büyük oranda öldürür:

| Paket kaybı | 25 paketlik karenin ulaşma oranı (formül) | Simülasyon (10000 kare) |
|-------------|-------------------------------------------|-------------------------|
| %1          | 0.99^25 = %77.8                           | %78.4                   |
| %5          | 0.95^25 = %27.7                           | %27.8                   |
| %10         | 0.90^25 = %7.2                            | %7.2                    |

Çözüm yaklaşımı: UDP'nin üstüne **yedek paketler** (FEC) ekleyip kaybolan paketleri yeniden
istemeden, gecikme olmadan geri kurmak.

## Mevcut durum

| Adım | Konu | Durum |
|------|------|-------|
| 1 | UDP soketi: `receiver` ve `sender` programları | Tamam |
| 2 | Kayıplı kanal simülasyonu, FEC'siz kare teslim ölçümü | Tamam |
| 3 | XOR paritesi (tek kaybı kurtarır) ve testi | Tamam |
| 4 | Galois alanı GF(256) | Sırada |
| 5 | Reed-Solomon (birden çok kaybı kurtarır) | Planlandı |
| 6 | Paket formatı ve CRC | Planlandı |
| 7 | Kare kodlayıcı ve birleştirici | Planlandı |
| 8 | Burst kayıp kanalı (Gilbert-Elliott), deney ve grafikler | Planlandı |
| 9+ | Çok düğümlü ağ ve yönlendirme (AODV) | Planlandı |

### Şu ana kadar yapılanlar

- **`apps/receiver.cpp`, `apps/sender.cpp`:** Linux soketleriyle UDP üzerinden haberleşen alıcı ve
  gönderici. Alıcı 9000 portuna `bind` eder, gelen paketin boyutunu ve gönderen portunu yazar.
- **`include/meshfec/channel.hpp`:** `LossChannel`, her paketi belirli bir olasılıkla düşüren,
  `seed` sayesinde tekrarlanabilir kayıp kanalı.
- **`apps/loss_demo.cpp`:** 25 paketlik karelerin FEC olmadan kayıp altında ne kadarının ulaştığını
  ölçer (yukarıdaki tablo).
- **`include/meshfec/xor_parity.hpp`:** XOR parite paketi üretimi (`xor_parity`) ve kaybolan bir
  paketin geri kurulması (`xor_recover`). Boş girdi ve farklı boyutlu paketler hata fırlatarak
  reddedilir.
- **`tests/test_xor_parity.cpp`:** Geri kurmayı ve hatalı girdilerin reddedilmesini doğrular.

## Planlanan mimari

```
kare -> [paketlere böl] -> k veri paketi -> [FEC kodla] -> k+m paket
     -> [kayıplı kanal / UDP] -> alıcı -> [FEC çöz] -> kare
```

`k` veri paketine `m` yedek paket eklenir. Reed-Solomon ile alınan `k+m` paketin **herhangi** `k`
tanesi kareyi geri kurmak için yeterlidir.

## Derleme ve çalıştırma (Ubuntu)

```bash
sudo apt install build-essential cmake git
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
```

Programlar `build/` içinde oluşur. Her `apps/*.cpp` ve `tests/test_*.cpp` dosyası ayrı bir program
olur, boş dosyalar atlanır.

```bash
# Alıcı ve gönderici (iki ayrı terminal)
./build/receiver          # 9000 portunda bir paket bekler
./build/sender            # 127.0.0.1:9000 adresine "merhaba" yollar

# Kayıp simülasyonu
./build/loss_demo
```

## Proje yapısı

```
apps/               çalıştırılabilir programlar (receiver, sender, loss_demo, ...)
include/meshfec/    header-only kütüphane (channel, xor_parity, ...)
tests/              testler (CTest ile çalışır)
YOL_HARITASI.md     adım adım yol haritası ve ilerleme
```

## Notlar

Bu proje bir öğrenme projesidir: kod, her adımda kavram öğrenilerek elle yazılmaktadır. Hedef,
ağ programlama, hata düzeltme kodları ve sistem yazılımı konularını gerçek bir uygulama üzerinde
pekiştirmektir.
