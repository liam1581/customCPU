//
// Created by keine ahnung brudi on 25/10/2025.
//

#pragma once

#include "./../int_defines.hpp"

struct uint3_t {
    uint8_t value;

    explicit uint3_t(const uint8_t v = 0) : value(v & 0x7) {} // only keep 3 bits

    uint3_t& operator=(const uint8_t v) {
        value = v & 0x7;
        return *this;
    }

    explicit operator uint8_t() const { return value; }

    // Arithmetic with wrapping at 4 bits
    uint3_t operator+(const uint3_t& other) const { return uint3_t((value + other.value) & 0x7); }
    uint3_t operator-(const uint3_t& other) const { return uint3_t((value - other.value) & 0x7); }
    uint3_t operator*(const uint3_t& other) const { return uint3_t((value * other.value) & 0x7); }
    uint3_t operator/(const uint3_t& other) const { return uint3_t((value / other.value) & 0x7); }

    bool operator==(const uint3_t& other) const { return value == other.value; }
    bool operator!=(const uint3_t& other) const { return value != other.value; }
    bool operator==(const uint8_t other) const { return value == (other & 0x7); }
    bool operator!=(const uint8_t other) const { return value != (other & 0x7); }
};

inline std::ostream& operator<<(std::ostream& os, const uint3_t& x) {
    os << static_cast<int>(x.value);  // cast to int to avoid printing as char
    return os;
}

inline bool operator==(const uint8_t& x, const uint3_t& y) { return (x & 0xFF) == (y.value & 0x7); }
inline bool operator!=(const uint8_t& x, const uint3_t& y) { return !(x == y); }
inline bool operator==(const uint3_t& x, const uint8_t& y) { return (x.value == y); }
inline bool operator!=(const uint3_t& x, const uint8_t& y) { return (x.value != y); }