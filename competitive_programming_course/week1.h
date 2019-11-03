#pragma once
// Неделя была посвященна всяким рекурсивным обходам, бэктрекингу
// подмножества длинной size
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

// все перестановки числе от [from, to) размера permutsize
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
