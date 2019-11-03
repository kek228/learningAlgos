#pragma once
// Неделя была посвященна всяким рекурсивным обходам, бэктрекингу


// подмножества длинной size
// идея проста, мы каждый раз либо добовляем число к подмножеству, либо пропускаем
// i тут это счетчик ПРОСМОТРЕННЫХ, не обязательно добавленных элементов
void genSubsets(vector<int> &subset, int n, int i, int subsetsize){
    if(i == n){
        if(subset.size() == subsetsize){
            for(auto el: subset)
                cout<<el<<' ';
            cout<<endl;
        }
        return;
    }
    subset.push_back(i);
    genSubsets(subset, n, i + 1, n);
    subset.pop_back();
    genSubsets(subset, n, i + 1, n);
}

// Все перестановки с повторениями
void genAllPermutsWithDoubles(vector<int> &permut, int from, int to, int permutsize, int &c){
    if(permut.size() == permutsize){
        for(auto el: permut)
            cout<<el<<' ';
        cout<<endl;
        return;
    }
    for(int j = from; j < to; ++j){
        permut.push_back(j);
        genAllPermutsWithDoubles(permut, from, to, permutsize, c);
        permut.pop_back();
    }
}
// все перестановки чисел от [from, to) размера permutsize БЕЗ ПОВТОРОВ
// идея сходна с подмножествами, но теперь нужно всегда пытаться добавить
// и отмечать добавленные
void genPermuts(vector<int> &permut, vector<bool> &used, int from, int to, int permutsize){
    if(permut.size() == permutsize){
        for(auto el: permut)
            cout<<el<<' ';
        cout<<endl;
        return;
    }
    for(int j = from; j < to; ++j){
        if(used[j])
            continue;
        permut.push_back(j);
        used[j] = true;
        genPermuts(permut, used, from, to, permutsize);
        permut.pop_back();
        used[j] = false;
    }
}

// валидные скобочные последовательности
// отличный пример бэктрэкинга
void validParentheses(vector<char> &parentheses, int n,  int open, int close){
    if(parentheses.size() == 2*n){
        for(auto el: parentheses)
            cout<<el<<' ';
        cout<<endl;
        return;
    }
    if(open < n){
        parentheses.push_back('(');
        validParentheses(parentheses, n, open + 1, close);
        parentheses.pop_back();
    }
    if(close < open){
        parentheses.push_back(')');
        validParentheses(parentheses, n, open, close + 1);
        parentheses.pop_back();
    }
}

// Все разбиения числа на слагаемые
// Важно что все комбинации не убывающие
void allTerms(vector<int> &terms, int n, int sum){
    if(sum == n){
        for(auto t: terms){
            cout<<t<<' ';
        }
        cout<<endl;
        return;
    }
    int t = 1;
    if(!terms.empty())
        t = terms.back();
    for(; t <= n - sum; ++t){
        terms.push_back(t);
        allTerms(terms, n, sum + t);
        terms.pop_back();
    }
}

// расстановка фишек
// вызов: chipPlacing(chips, n, m, -2, 0);
void chipPlacing(vector<char> &chips, int n, int m, int last, int placed){
    if(placed == m){
        for(auto c: chips){
            cout<<c;
        }
        cout<<endl;
        return;
    }
    for(int i = last + 2; i < n; ++i){
        chips[i] = '*';
        chipPlacing(chips, n, m, i, placed + 1);
        chips[i] = '.';
    }
}
