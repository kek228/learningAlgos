#pragma once

class SuffixArray {
public:
    // очередной суффикс
    // построка начаинающаяся с strPos
    // ее первая половина имеет ранг firstRang, вторая secondRang
    struct Suffix {
        int firstRang; //ранг первой половины подстроки
        int secondRang; //ранг втрой половины
        int strPos; // начало суффикса
        bool operator==(const Suffix &l) {
            return firstRang == l.firstRang && secondRang == l.secondRang;
        }

        bool operator!=(const Suffix &l) {
            return !(*this == l);
        }
    };


    explicit SuffixArray(const string &str) : _original(str), _suffixArray(str.size() + 1) {
        vector<int> classArr;
        for (auto c: str)
            classArr.push_back(c);
        classArr.push_back(0);
        //
        int n = classArr.size();
        vector <Suffix> suffixes(n);
        for (int i = 1; i < n; i *= 2) {
            for (int strPos = 0; strPos < classArr.size(); ++strPos)
                // classArr[strPos] ранг строки с strPos, с предидущего шага
                // classArr[(strPos + i)  % n]  ранг строки с strPos + i
                // ТО ЕСТЬ СОРТИРУЕМ СТРОКИ ДЛИННОЙ 2i
                suffixes[strPos] = {classArr[strPos], classArr[(strPos + i) % n], strPos};
            //
            sort(suffixes.begin(), suffixes.end(), [](const Suffix &l, const Suffix &r) {
                if (l.firstRang != r.firstRang)
                    return l.firstRang < r.firstRang;
                return l.secondRang < r.secondRang;
            });
            // перезапись массива классов
            // класс == позиция в отсортированном массиве, за вычетом равнозначных классв (кейс an an в строке banana)
            int newClass = 0;
            for (int j = 0; j < n; ++j) {
                if (j && suffixes[j] != suffixes[j - 1])
                    ++newClass;
                classArr[suffixes[j].strPos] = newClass;
            }
            //
            for (int i = 0; i < n; i++)
                _suffixArray[classArr[i]] = i;
        }
    }

    string maxStr() {
        int maxBegin = _suffixArray.back();
        return _original.substr(maxBegin);
    }

private:
    const string _original;
    vector<int> _suffixArray;
};


// топ за свои деньги
//string s1 = "abcdefg";
//string s2 = "bcdafgk";

int countConvertOps(const string &s1, const string &s2, const int alphabetSize) {
    unordered_map<char, char> s1Tos2Mapping;
    for (int i = 0; i < s1.size(); ++i) {
        if (s1[i] == s2[i])
            continue;
        auto fchar = s1Tos2Mapping.find(s1[i]);
        if (fchar == s1Tos2Mapping.end())
            s1Tos2Mapping[s1[i]] = s2[i];
        else {
            // a a b case
            // b c d
            if (fchar->second != s2[i])
                return -1;
        }
    }

    // if alphabet is exhausted, we are unable to make a single change
    if (s1Tos2Mapping.size() == alphabetSize)
        return -1;
    // count simple changes and cycle changes
    int res = 0;
    bool swapNeed = false;
    unordered_set<char> cycleFound;
    for (const auto &mapping: s1Tos2Mapping) {
        // simple swap
        auto char2InS1 = s1Tos2Mapping.find(mapping.second);
        if (char2InS1 == s1Tos2Mapping.end()) {
            ++res;
        }
            // check cycle
        else {
            // cycle found
            if (char2InS1->second == mapping.first) {
                if (cycleFound.find(mapping.first) == cycleFound.end()) {
                    res += 3;
                    cycleFound.insert(mapping.first);
                    cycleFound.insert(mapping.second);
                }
            } else
                swapNeed = true;
        }
    }
    return res + s1Tos2Mapping.size() + swapNeed;
}

// https://leetcode.com/problems/string-to-integer-atoi
bool isDigit(const char c) {
    return c >= '0' && c <= '9';
}

int myAtoi(string str) {
    int size = str.size();
    if (size == 0)
        return 0;
    //
    int start = 0;
    int sign = 1;
    for (; start < size; ++start) {
        char c = str[start];
        if (isDigit(c))
            break;
        if (str[start] == '-') {
            sign = -1;
            break;
        }
        if (str[start] == '+')
            break;
        if (c != ' ')
            return 0;
    }
    if (start == size)
        return 0;
    if (!isDigit(str[start])) {// - или +
        ++start;
        if (start == size)
            return 0;
        if (!isDigit(str[start]))
            return 0;
    }
    // тут start строго на первой цифре(может и 0)
    // тут может быть только рядо 0й
    while (start < size && str[start] == '0') {
        ++start;
        if (start < size && !isDigit(str[start]))
            return 0;
    }
    int last = start; // start строго на первую цифру
    for (; last < size; ++last) {
        if (!isDigit(str[last]))
            break;
    }// после цикла last или знак или == size
    --last; // на последнюю цифру
    int degree = 0;
    int res = 0;
    for (int i = last; i >= start; --i) {
        if ((degree == 9 && str[i] > '2') || degree > 9) {
            if (sign > 0)
                return numeric_limits<int>::max();
            else
                return numeric_limits<int>::min();
        }

        int add = (str[i] - '0') * pow(10, degree) * sign;
        if (sign > 0) {
            if (res > numeric_limits<int>::max() - add)
                return numeric_limits<int>::max();
        } else if (sign < 0) {
            if (res < numeric_limits<int>::min() - add)
                return numeric_limits<int>::min();
        }
        res += add;
        ++degree;
    }
    return res;
}
