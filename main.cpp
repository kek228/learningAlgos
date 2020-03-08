#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <iterator>
#include <set>
#include <optional>
#include <stdint.h>
#include <deque>
#include <limits>
#include <list>
#include <map>
#include <functional>

using namespace std;

double minusBinpow(double a, int n) {
    if (n == 0)
        return 1;
    if (n % 2 == -1)
        return minusBinpow(a, n + 1) * (1 / a);
    else {
        double b = minusBinpow(a, n / 2);
        return (1 / b) * b;
    }
}


int main() {
    cout << minusBinpow(2, -2);
    return 0;
}