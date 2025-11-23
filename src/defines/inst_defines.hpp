//
// Created by keine ahnung brudi on 25/10/2025.
//

#pragma once

const auto WORD = static_cast<uint4_t>(0b0000);
const auto LD = static_cast<uint4_t>(0b0001);
const auto ST = static_cast<uint4_t>(0b0010);
const auto NO = static_cast<uint4_t>(0b0011);
const auto HL = static_cast<uint4_t>(0b0100);
const auto ADD = static_cast<uint4_t>(0b0101);
const auto SUB = static_cast<uint4_t>(0b0110);
const auto MUL = static_cast<uint4_t>(0b0111);
const auto JMP = static_cast<uint4_t>(0b1000);

const auto REG_n = static_cast<uint3_t>(0b00);
const auto REG_A = static_cast<uint3_t>(0b01);
const auto REG_B = static_cast<uint3_t>(0b10);
const auto REG_C = static_cast<uint3_t>(0b11);