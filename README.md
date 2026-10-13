# meshfec

Taktik mesh ağlar için kayba dayanıklı veri/video iletimi: ad-hoc yönlendirme + Reed-Solomon FEC +
kayıplı kanal simülasyonu. C++17, harici bağımlılık yok.

Bu proje adım adım, öğrenilerek yazılıyor. İlerleme için `YOL_HARITASI.md`'ye bakın.

## Derleme (Ubuntu)

```bash
sudo apt install build-essential cmake git
cmake -S . -B build
cmake --build build -j
ctest --test-dir build --output-on-failure
```

Programlar `build/` içinde oluşur (örn. `./build/receiver`).
