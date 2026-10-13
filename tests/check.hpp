#pragma once
// Minimal test yardımcıları (Adım 3'ten itibaren kullanacağız).
// assert() yerine bunu kullanıyoruz: Release modunda (NDEBUG) devre dışı kalmaz.

#include <cstdio>
#include <cstdlib>

#define CHECK(cond)                                                                           \
    do {                                                                                      \
        if (!(cond)) {                                                                        \
            std::fprintf(stderr, "CHECK basarisiz: %s (%s:%d)\n", #cond, __FILE__, __LINE__); \
            std::exit(1);                                                                     \
        }                                                                                     \
    } while (0)

#define CHECK_THROWS(expr, ex)          \
    do {                                \
        bool thrown_ = false;           \
        try {                           \
            (void)(expr);               \
        } catch (const ex&) {           \
            thrown_ = true;             \
        }                               \
        CHECK(thrown_);                 \
    } while (0)
