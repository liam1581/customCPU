//
// Created by keine ahnung brudi on 25/10/2025.
//

#pragma once

using namespace std;

class ROM {
public:
    [[nodiscard]]
    uint8_t read(const uint8_t addr) const {
        return data[addr];
    }
    void write(const uint8_t addr, const uint8_t val) {
        data[addr] = val;
    }

    uint8_t& operator[](const uint8_t addr) {
        return data[addr];
    }
    const uint8_t& operator[](const uint8_t addr) const {
        return data[addr];
    }
    ROM& operator<<(const uint8_t& value) {
        data[cursor++] = value;
        return *this;
    }
    ROM& operator<<(const uint4_t& value) {
        data[cursor++] = value.value & 0xF;
        return *this;
    }
    ROM& operator<<(const int4_t& value) {
        data[cursor++] = value.value & 0xF;
        return *this;
    }
    ROM& operator<<(const uint3_t& value) {
        data[cursor++] = value.value & 0x7;
        return *this;
    }

    void reset() { cursor = 0; }
    static constexpr size_t size() { return 256; }



    DEBUGv dump() const {
        for (size_t i = 0; i < size(); ++i) {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<int>(data[i]) << " ";
            if ((i + 1) % 16 == 0) std::cout << "\n";
        }
        std::cout << std::dec << "\n";
    }

private:
    uint8_t data[256] = {};
    uint8_t cursor = 0;
};
inline std::ostream& operator<<(std::ostream& os, const ROM& mem) {
    for (size_t i = 0; i < ROM::size(); ++i) {
        os << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(mem[i]) << " ";
        if ((i + 1) % 16 == 0) os << "\n"; // optional: 16 bytes per line
    }
    os << std::dec; // reset to decimal
    return os;
}

class RAM {
public:
    [[nodiscard]]
    uint8_t read(const uint8_t addr) const {
        return data[addr];
    }
    void write(const uint8_t addr, const uint8_t val) {
        data[addr] = val;
    }

    uint8_t& operator[](const uint8_t addr) {
        return data[addr];
    }
    const uint8_t& operator[](const uint8_t addr) const {
        return data[addr];
    }
    RAM& operator<<(const uint8_t& value) {
        data[cursor++] = value;
        return *this;
    }
    RAM& operator<<(const uint4_t& value) {
        data[cursor++] = value.value & 0xF;
        return *this;
    }
    RAM& operator<<(const int4_t& value) {
        data[cursor++] = value.value & 0xF;
        return *this;
    }
    RAM& operator<<(const uint3_t& value) {
        data[cursor++] = value.value & 0x7;
        return *this;
    }

    void reset() { cursor = 0; }
    static constexpr size_t size() { return 256; }



    DEBUGv dump() const {
        for (size_t i = 0; i < size(); ++i) {
            std::cout << std::hex << std::setw(2) << std::setfill('0')
                      << static_cast<int>(data[i]) << " ";
            if ((i + 1) % 16 == 0) std::cout << "\n";
        }
        std::cout << std::dec << "\n";
    }

private:
    uint8_t data[256] = {};
    uint8_t cursor = 0;
};
inline std::ostream& operator<<(std::ostream& os, const RAM& mem) {
    for (size_t i = 0; i < RAM::size(); ++i) {
        os << std::hex << std::setw(2) << std::setfill('0')
           << static_cast<int>(mem[i]) << " ";
        if ((i + 1) % 16 == 0) os << "\n"; // optional: 16 bytes per line
    }
    os << std::dec; // reset to decimal
    return os;
}