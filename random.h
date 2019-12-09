#pragma once

void sieve() {
    memset(prime, true, sizeof(prime));
    prime[1] = false, prime[0] = false;
    for (int i = 4; i <= 9000; i += 2)
        prime[i] = false;
    for (int p = 3; p * p <= 9000; p += 2) {
        if (prime[p] == true) {
            for (int i = p * p; i <= 9000; i += 2 * p)
                prime[i] = false;
        }
    }
}