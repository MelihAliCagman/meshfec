# Yol haritası

| Adım | Konu | Dosyalar | Bitti |
|------|------|----------|-------|
| 1 | UDP soketi: iki program konuşuyor | `apps/receiver.cpp`, `apps/sender.cpp` | [x] |
| 2 | Paket kaybı: kaybı simüle et, FEC'siz kare teslimini ölç | `include/meshfec/channel.hpp`, `apps/loss_demo.cpp` | [x] |
| 3 | En basit FEC: XOR paritesi (1 kaybı kurtar) | `include/meshfec/xor_parity.hpp`, `tests/test_xor_parity.cpp` | [x] |
| 4 | Galois alanı GF(256) | `include/meshfec/gf256.hpp`, `tests/test_gf256.cpp` | [ ] |
| 5 | Reed-Solomon: birden çok kaybı kurtar | `include/meshfec/rs_erasure.hpp`, `tests/test_rs.cpp` | [ ] |
| 6 | Paket formatı ve CRC | `include/meshfec/crc32.hpp`, `include/meshfec/packet.hpp`, `tests/test_packet.cpp` | [ ] |
| 7 | Kare kodlayıcı ve birleştirici | `include/meshfec/frame_codec.hpp`, `tests/test_codec.cpp` | [ ] |
| 8 | Burst kayıp kanalı, deney, grafik | `channel.hpp` (genişlet), `tests/test_channel.cpp`, `apps/sim_link.cpp` | [ ] |
| 9+ | Çok düğümlü ağ ve yönlendirme (AODV) | (sonra eklenecek) | [ ] |
