#pragma once

#include <cinttypes>
#include <iostream>
#include <cstring>


const int ARRAY_SIZE = 253;
const int SIGN = 128;
const int BASE = 256;

struct int2023_t {
    uint8_t number[ARRAY_SIZE]{0};

    int2023_t() = default;

    explicit int2023_t(int32_t i) {
        int start = ARRAY_SIZE - 1;
        if (i >= 0) {
            while (i > 0) {
                number[start] = i % BASE;
                i /= BASE;
                start--;
            }
        } else {
            i = -i;
            while (i > 0) {
                number[start] = i % BASE;
                i /= BASE;
                start--;
            }
            number[0] = SIGN; // if number is negative we should use 1 bit for the sign
        }
    }
};

static_assert(sizeof(int2023_t) <= 253, "Size of int2023_t must be no higher than 253 bytes");

bool IsNegative(const int2023_t &num);

int2023_t BinDivision(const int2023_t &a);

int2023_t from_int(int32_t i); // DONE

int2023_t from_string(const char *buff); // DONE

int2023_t operator+(const int2023_t &lhs, const int2023_t &rhs); // DONE

int2023_t operator-(const int2023_t &lhs, const int2023_t &rhs); // DONE

int2023_t operator*(const int2023_t &lhs, const int2023_t &rhs); // DONE

int2023_t operator/(const int2023_t &lhs, const int2023_t &rhs); // DONE

bool operator==(const int2023_t &lhs, const int2023_t &rhs); // DONE

bool operator!=(const int2023_t &lhs, const int2023_t &rhs); // DONE

std::ostream &operator<<(std::ostream &stream, const int2023_t &value); // DONE
