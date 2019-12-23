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
