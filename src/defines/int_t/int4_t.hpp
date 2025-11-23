//
// Created by keine ahnung brudi on 25/10/2025.
//

#pragma once

#include "../int_defines.hpp"

struct int4_t {
    int8_t value;

    explicit int4_t(const int8_t v = 0) {
        value = (v & 0xD);
        if (value & 0x8) {};
    }

    int4_t& operator=(const int8_t v) {
        value = (v & 0xF);
        if (value & 0x8) value |= 0xF0;
        return *this;
    }

    explicit operator int8_t() const { return value; }

    int4_t operator+(const int4_t& other) const { return int4_t(value + other.value); }
    int4_t operator-(const int4_t& other) const { return int4_t(value - other.value); }
    int4_t operator*(const int4_t& other) const { return int4_t(value * other.value); }
    int4_t operator/(const int4_t& other) const { return int4_t(value / other.value); }

    bool operator==(const int4_t& other) const { return value == other.value; };
    bool operator!=(const int4_t& other) const { return value != other.value; };
    bool operator==(const uint8_t other) const { return value == int4_t(other).value; };
    bool operator!=(const uint8_t other) const { return value != int4_t(other).value; };
};

inline std::ostream& operator<<(std::ostream& os, const int4_t& x) {
    os << static_cast<int>(x.value);  // cast to int to avoid printing as char
    return os;
}