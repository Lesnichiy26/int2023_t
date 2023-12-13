#include "number.h"

bool IsNegative(const int2023_t &num) {
    if (num.number[0] > 127) {
        return true;
    }
    return false;
}

int2023_t BinDivision(const int2023_t &a) {
    int2023_t num = a;
    bool flag = IsNegative(num);
    if (flag) {
        num.number[0] -= SIGN;
    }
    int start = 0;
    while (num.number[start] == 0) {
        start++;
    }
    int buf = 0;
    int2023_t result;
    for (int i = start; i < ARRAY_SIZE; i++) {
        buf += num.number[i];
        result.number[i] += buf / 2;
        buf = buf % 2 * BASE;
    }
    if (flag && !IsNegative(result)) {
        result.number[0] += SIGN;
    }
    return result;
}

int2023_t from_int(int32_t i) {
    int2023_t a(i);
    return a;
}

int2023_t from_string(const char *buff) {
    int2023_t result;
    int start = 0;
    bool flag = false;
    int2023_t ten(10);
    if (buff[0] == '-') {
        start++;
        flag = true;
    }
    int len = strlen(buff);
    for (int i = start; i < len; i++) {
        result = result * ten;
        int cur = buff[i] - '0';
        int2023_t temp(cur);
        result = result + temp;
    }
    if (flag) {
        result.number[0] += SIGN;
    }
    return result;
}

int2023_t absolute(const int2023_t &n) { // to get absolute value
    int2023_t a = n;
    if (a.number[0] >= SIGN) {
        a.number[0] -= SIGN;
    }
    return a;
}

bool operator>(const int2023_t &lhs, const int2023_t &rhs) {
    if (IsNegative(lhs) && !IsNegative(rhs)) {
        return false;

    } else if (!IsNegative(lhs) && IsNegative(rhs)) {
        return true;

    } else if (!IsNegative(lhs) && !IsNegative(rhs)) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if (lhs.number[i] > rhs.number[i]) {
                return true;

            } else if (lhs.number[i] < rhs.number[i]) {
                return false;
            }
        }

    } else if (IsNegative(lhs) && IsNegative(rhs)) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            int lhs1 = lhs.number[i];
            int rhs1 = rhs.number[i];
            if (i == 0) {
                lhs1 -= SIGN;
                rhs1 -= SIGN;
            }
            if (lhs1 > rhs1) {
                return false;

            } else if (lhs1 < rhs1) {
                return true;
            }
        }
    }
    return false;
}

bool operator<(const int2023_t &lhs, const int2023_t &rhs) {
    if (IsNegative(lhs) && !IsNegative(rhs)) {
        return true;

    } else if (!IsNegative(lhs) && IsNegative(rhs)) {
        return false;

    } else if (!IsNegative(lhs) && !IsNegative(rhs)) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if (lhs.number[i] > rhs.number[i]) {
                return false;

            } else if (lhs.number[i] < rhs.number[i]) {
                return true;
            }
        }

    } else if (IsNegative(lhs) && IsNegative(rhs)) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            int lhs1 = lhs.number[i];
            int rhs1 = rhs.number[i];
            if (i == 0) {
                lhs1 -= SIGN;
                rhs1 -= SIGN;
            }
            if (lhs1 > rhs1) {
                return true;

            } else if (lhs1 < rhs1) {
                return false;
            }
        }
    }
    return false;
}

int2023_t operator+(const int2023_t &lhs, const int2023_t &rhs) {
    int2023_t result(0);
    if (!IsNegative(lhs) && !IsNegative(rhs)) { // lhs > 0 && rhs > 0
        for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
            int cur = lhs.number[i] + rhs.number[i] + result.number[i];
            if (cur >= BASE) {
                result.number[i] = cur - BASE;
                if (i - 1 < 0) {
                    break;
                }
                result.number[i - 1]++;
            } else {
                result.number[i] = cur;
            }
        }
        if (result.number[0] >= SIGN) {
            result.number[0] -= SIGN;
        }

    } else if (IsNegative(lhs) && IsNegative(rhs)) { // lhs < 0 && rhs < 0
        for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
            int cur = lhs.number[i] + rhs.number[i] + result.number[i];
            if (cur >= BASE) {
                result.number[i] = cur - BASE;
                if (i - 1 < 0) {
                    break;
                }
                result.number[i - 1]++;
            } else {
                result.number[i] = cur;
            }
        }
        if (result.number[0] < SIGN) {
            result.number[0] += SIGN;
        }

    } else if (IsNegative(lhs) && !IsNegative(rhs)) { // lhs < 0 && rhs > 0
        bool flag = false; // if true the result is negative
        int2023_t abs_lhs = absolute(lhs);
        if (abs_lhs == rhs) {
            return result;
        } else if (abs_lhs > rhs) {
            flag = true;
        }
        int help = 0;
        if (flag) {
            int2023_t n1 = abs_lhs;
            int2023_t n2 = rhs;
            for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
                int cur = n1.number[i] - n2.number[i] + help;
                if (cur < 0) {
                    result.number[i] += cur + BASE;
                    help = -1;
                } else {
                    result.number[i] = cur;
                    help = 0;
                }
            }
            if (result.number[0] < SIGN) {
                result.number[0] += SIGN;
            }

        } else {
            int2023_t n1 = rhs;
            int2023_t n2 = abs_lhs;
            for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
                int cur = n1.number[i] - n2.number[i] + help;
                if (cur < 0) {
                    result.number[i] += cur + BASE;
                    help = -1;
                } else {
                    result.number[i] = cur;
                    help = 0;
                }
            }
            if (result.number[0] >= SIGN) {
                result.number[0] -= SIGN;
            }
        }
    } else if (!IsNegative(lhs) && IsNegative(rhs)) { // lhs > 0 && rhs < 0
        bool flag = false; // if true the result is negative
        int2023_t abs_rhs = absolute(rhs);
        if (abs_rhs == lhs) {
            return result;
        } else if (abs_rhs > lhs) {
            flag = true;
        }
        int help = 0;
        if (flag) {
            int2023_t n1 = abs_rhs;
            int2023_t n2 = lhs;
            for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
                int cur = n1.number[i] - n2.number[i] + help;
                if (cur < 0) {
                    result.number[i] += cur + BASE;
                    help = -1;
                } else {
                    result.number[i] = cur;
                    help = 0;
                }
            }
            if (result.number[0] < SIGN) {
                result.number[0] += SIGN;
            }

        } else {
            int2023_t n1 = lhs;
            int2023_t n2 = abs_rhs;
            for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
                int cur = n1.number[i] - n2.number[i] + help;
                if (cur < 0) {
                    result.number[i] += cur + BASE;
                    help = -1;
                } else {
                    result.number[i] = cur;
                    help = 0;
                }
            }
            if (result.number[0] >= SIGN) {
                result.number[0] -= SIGN;
            }
        }
    }

    return result;
}

int2023_t operator-(const int2023_t &lhs, const int2023_t &rhs) {
    int2023_t new_rhs = rhs;
    if (!IsNegative(new_rhs)) {
        new_rhs.number[0] += SIGN;
    } else {
        new_rhs.number[0] -= SIGN;
    }
    return lhs + new_rhs;
}

int2023_t operator*(const int2023_t &lhs, const int2023_t &rhs) {
    bool flag = false; // if true the result is negative
    int2023_t result;
    if ((IsNegative(lhs) && !IsNegative(rhs)) || (!IsNegative(lhs) && IsNegative(rhs))) {
        flag = true;
    }
    int2023_t nul;
    if (lhs == nul || rhs == nul) {
        return result;
    }

    int2023_t n1;
    int2023_t n2;

    if (IsNegative(lhs)) {
        n1 = absolute(lhs);
    } else {
        n1 = lhs;
    }

    if (IsNegative(rhs)) {
        n2 = absolute(rhs);
    } else {
        n2 = rhs;
    }
    int border = ARRAY_SIZE - 1;
    int id;
    for (int i = ARRAY_SIZE - 1; i >= 0; i--) {
        int mult = n2.number[i];
        int2023_t buf;
        id = border;
        for (int j = ARRAY_SIZE - 1; j >= 0; j--) {
            int cur = mult * n1.number[j] + buf.number[id];
            if (cur >= BASE) {
                buf.number[id] = cur % BASE;
                if (id - 1 < 0) {
                    break;
                }
                buf.number[id - 1] = cur / BASE;
            } else {
                buf.number[id] = cur;
            }
            id--;
            if (id < 0) {
                break;
            }
        }
        result = result + buf;
        border--;
        if (border < 0) {
            break;
        }
    }

    if (flag && result.number[0] < SIGN) {
        result.number[0] += SIGN;
    }

    return result;
}

int2023_t operator/(const int2023_t &lhs, const int2023_t &rhs) {
    bool flag = false; // if true the result is negative
    int2023_t result;
    int2023_t nul;
    if ((IsNegative(lhs) && !IsNegative(rhs)) || (!IsNegative(lhs) && IsNegative(rhs))) {
        flag = true;
    }
    if (rhs == int2023_t(1)) {
        result = lhs;
        return result;
    }
    int2023_t low = nul;
    int2023_t high = absolute(lhs);
    int2023_t x = absolute(lhs);
    int2023_t y = absolute(rhs);
    if (y == nul) {
        std::cerr << "Division by zero";
        exit(EXIT_FAILURE);
    }
    if (x < y) {
        return result;
    }
    while (true) {
        int2023_t mid = low + (BinDivision(high - low));

        if (x - mid * y > y) {
            low = mid;

        } else if (y * mid - x < nul || y * mid - x == nul) {
            result = mid;
            break;
        }

        if (y * mid < x) {
            low = mid;
        } else if (y * mid > x) {
            high = mid;
        }
    }
    if (flag && !IsNegative(result) && result != nul) {
        result.number[0] += SIGN;
    }
    return result;
}

bool operator==(const int2023_t &lhs, const int2023_t &rhs) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (lhs.number[i] != rhs.number[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const int2023_t &lhs, const int2023_t &rhs) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (lhs.number[i] != rhs.number[i]) {
            return true;
        }
    }
    return false;
}

std::ostream &operator<<(std::ostream &stream, const int2023_t &value) {
    uint32_t byte_with_sign = value.number[0];
    if (value.number[0] >= SIGN) {
        stream << '-';
        byte_with_sign -= SIGN;
    }
    uint32_t first = byte_with_sign;
    stream << first << ' ';
    for (int i = 1; i < ARRAY_SIZE; i++) {
        int num = value.number[i];
        stream << num << ' ';
    }
    stream << '\n';

    return stream;
}
