#include "check.hpp"
#include "meshfec/xor_parity.hpp"

int main(){
    std::vector<Bytes> paketler = {{1,2,3},{4,5,6},{7,8,9,}};
    Bytes parite =xor_parity(paketler);

    Bytes geri = xor_recover({paketler[0],paketler[2]},parite);
    CHECK(geri == paketler[1]);

    CHECK_THROWS(xor_parity({}),std::invalid_argument);
    CHECK_THROWS(xor_parity({{1,2,3},{4,5}}), std::invalid_argument);

    std::puts("test_xor_parity: tamam");
}