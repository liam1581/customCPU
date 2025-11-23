//
// Created by keine ahnung brudi on 25/10/2025.
//

#pragma once
#include "../inst_defines.hpp"

class CPU {
public:
    CPU() = default;

    void compile(const uint4_t inst, const uint8_t data, const uint3_t RS, ROM& rom) const {
        if (inst == LD) {
            rom << LD << data << RS;
        } else if (inst == ST) {
            rom << ST << data << RS;
        } else if (inst == NO) {
            rom << NO << data << RS;
        } else if (inst == HL) {
            rom << HL << data << RS;
        } else if (inst == ADD) {
            rom << ADD << data << RS;
        } else if (inst == SUB) {
            rom << SUB << data << RS;
        } else if (inst == MUL) {
            rom << MUL << data << RS;
        } else if (inst == JMP) {
            rom << JMP << data << RS;
        } else if (inst == WORD) {
            if (RS == REG_A) {
                rom[data] = A;
            } else if (RS == REG_B) {
                rom[data] = B;
            } else if (RS == REG_C) {
                rom[data] = C;
            }
        }

        else {
            cout << "COMPILE::invalid instruction (" << inst << ")" << endl;
        }
    }

    static void parse(const string& line, uint8_t out[3]) {
        stringstream ss(line);
        string word;
        vector<string> words;

        while (ss >> word) {
            words.push_back(word);
        }

        const string inst = words[0];
        string data;
        string RS;
        if (!inst.starts_with("NOP") && !inst.starts_with("HL") && !inst.starts_with("JMP")) {
            data = words[1];
            RS = words[2];
        } else if (inst.starts_with("JMP")) {
            data = words[1];
            RS = "n";
        } else if (inst.starts_with("NOP") || inst.starts_with("HL")) {
            data = "$00";
            RS = "n";
        }
        if (inst.starts_with(';') || inst.starts_with('#') || inst.starts_with("//")) {}

        if (inst == "LD") inst_to_out(LD, data, RS, out);
        else if (inst == "ST") inst_to_out(ST, data, RS, out);
        else if (inst == "NO") inst_to_out(NO, data, RS, out);
        else if (inst == "HL") inst_to_out(HL, data, RS, out);
        else if (inst == "ADD") inst_to_out(ADD, data, RS, out);
        else if (inst == "SUB") inst_to_out(SUB, data, RS, out);
        else if (inst == "MUL") inst_to_out(MUL, data, RS, out);
        else if (inst == "JMP") inst_to_out(JMP, data, RS, out);
        else if (inst == ".byte") inst_to_out(WORD, data, RS, out);

    }

    void run(const ROM &rom, RAM& ram) {
        A = 0x00;
        B = 0x00;
        C = 0x00;

        while (ROM_addr < ROM::size()) {
            const uint8_t inst = rom.read(ROM_addr);
            ROM_addr++;
            const uint8_t data = rom.read(ROM_addr);
            ROM_addr++;
            const uint8_t RS = rom.read(ROM_addr);
            ROM_addr++;

            if (inst == LD) {
                if (RS == REG_A) {
                    A = data;
                } else if (RS == REG_B) {
                    B = data;
                } else if (RS == REG_C) {
                    C = data;
                }
            } else if (inst == ST) {
                if (RS == REG_A) {
                    ram.write(data, A);
                } else if (RS == REG_B) {
                    ram.write(data, B);
                } else if (RS == REG_C) {
                    ram.write(data, C);
                }
            } else if (inst == NO) {
            } else if (inst == HL) {
                cout << "HALTING CPU" << endl;
                break;
            }
            else if (inst == ADD) {
                if (RS == REG_A) {
                    A = data + A;
                } else if (RS == REG_B) {
                    B = data + B;
                } else if (RS == REG_C) {
                    B = data + B;
                }
            } else if (inst == SUB) {
                if (RS == REG_A) {
                    A = data - A;
                } else if (RS == REG_B) {
                    B = data - B;
                } else if (RS == REG_C) {
                    B = data - B;
                }
            } else if (inst == MUL) {
                if (RS == REG_A) {
                    A = data * A;
                } else if (RS == REG_B) {
                    B = data * B;
                } else if (RS == REG_C) {
                    B = data * B;
                }
            } else if (inst == JMP) {
                ROM_addr = data;
            }

            /*
            if (RS == static_cast<uint8_t>(REG_A)) {

                } else if (RS == static_cast<uint8_t>(REG_B)) {

                } else if (RS == static_cast<uint8_t>(REG_C)) {

                }
             */

            else if (inst == 0x00) {
                break;
            } else {
                cerr << "RUN::Unknown inst: " << static_cast<int>(inst) << endl;
                exit(1);
            }
        }
    }
private:
    uint8_t ROM_addr = 0;

    uint8_t A;
    uint8_t B;
    uint8_t C;


    static uint8_t parse_uint8(const std::string& input) {
        if (input.empty())
            throw std::invalid_argument("Empty input");

        const char prefix = input[0];
        const std::string number = input.substr(1); // everything after the prefix

        int base;
        switch (prefix) {
            case '#': base = 10; break; // decimal
            case '$': base = 16; break; // hexadecimal
            case '%': base = 2;  break; // binary
            default:
                throw std::invalid_argument("Invalid prefix (must be #, $, or %)");
        }

        // Convert string to integer with base
        const unsigned long value = std::stoul(number, nullptr, base);

        // Enforce 8-bit limit
        if (value > 255)
            throw std::out_of_range("Value exceeds uint8_t range");

        return static_cast<uint8_t>(value);
    }
    static void inst_to_out(const uint4_t inst, const string& data, const string& RS, uint8_t out[3]) {
        out[0] = static_cast<uint8_t>(inst);
        out[1] = parse_uint8(data);
        if (RS == "A") {
            out[2] = static_cast<uint8_t>(REG_A);
        } else if (RS == "B") {
            out[2] = static_cast<uint8_t>(REG_B);
        } else if (RS == "C") {
            out[2] = static_cast<uint8_t>(REG_C);
        } else if (RS == "n") {
            out[2] = static_cast<uint8_t>(REG_n);
        }
    }
};
