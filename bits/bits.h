#pragma once

int leastSignifisantBit(unsigned int n) {
    return (n & (~n + 1))
}

// кол-во единичных бит
int hammingWeight(uint32_t n) {
    int res = 0;
    while (n > 0) {
        if ((n & 1) != 0)
            ++res;
        n >>= 1;
    }
    return res;
}