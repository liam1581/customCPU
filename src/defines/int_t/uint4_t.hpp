//
// Created by keine ahnung brudi on 25/10/2025.
//

#pragma once

#include "../int_defines.hpp"

struct uint4_t {
    uint8_t value;

    explicit uint4_t(const uint8_t v = 0) : value(v & 0xF) {} // only keep 4 bits

    uint4_t& operator=(const uint8_t v) {
        value = v & 0xF;
        return *this;
    }

    explicit operator uint8_t() const { return value; }

    // Arithmetic with wrapping at 4 bits
    uint4_t operator+(const uint4_t& other) const { return uint4_t((value + other.value) & 0xF); }
    uint4_t operator-(const uint4_t& other) const { return uint4_t((value - other.value) & 0xF); }
    uint4_t operator*(const uint4_t& other) const { return uint4_t((value * other.value) & 0xF); }
    uint4_t operator/(const uint4_t& other) const { return uint4_t((value / other.value) & 0xF); }

    bool operator==(const uint4_t& other) const { return value == other.value; }
    bool operator!=(const uint4_t& other) const { return value != other.value; }
    bool operator==(const uint8_t other) const { return value == (other & 0xF); };
    bool operator!=(const uint8_t other) const { return value != (other & 0xF); };
};

inline std::ostream& operator<<(std::ostream& os, const uint4_t& x) {
    os << static_cast<int>(x.value);  // cast to int to avoid printing as char
    return os;
}

inline bool operator==(const uint8_t& x, const uint4_t& y) { return (x & 0xFF) == (y.value & 0xF); }
inline bool operator!=(const uint8_t& x, const uint4_t& y) { return !(x == y); }
inline bool operator==(const uint4_t& x, const uint8_t& y) { return (x.value == y); }
inline bool operator!=(const uint4_t& x, const uint8_t& y) { return (x.value != y); }
