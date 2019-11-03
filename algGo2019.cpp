#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <string>
#include <fstream>
#include <streambuf>
#include <sstream>
#include <iterator>
#include <limits>
#include <fstream>

using namespace std;

vector<int> split(const string& str, char delim = ' '){
    vector<int> res;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        res.push_back(stoi(token));
    }
    return res;
}

int counter = 0;
bool ArePair(char opening,char closing)
{
    if(opening == '(' && closing == ')') return true;
    else if(opening == '{' && closing == '}') return true;
    else if(opening == '[' && closing == ']') return true;
    return false;
}
bool AreParanthesesBalanced(vector<char> &exp)
{
    stack<char>  S;
    for(int i =0;i<exp.size();i++)
    {
        if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
            S.push(exp[i]);
        else if(exp[i] == ')' || exp[i] == '}' || exp[i] == ']')
        {
            if(S.empty() || !ArePair(S.top(),exp[i]))
                return false;
            else
                S.pop();
        }
    }
    return S.empty() ? true:false;
}

void validParentheses(vector<char> &parentheses, int n, int b1, int b2){
    if(parentheses.size() == 2*n){
        //if(counter == 8644)
        //{
        if(AreParanthesesBalanced(parentheses)){
            ++counter;
            if(counter == 8233){
                for(auto el: parentheses)
                    cout<<el<<' ';
                cout<<endl;
            }
        }
        //}
        return;
    }
    parentheses.push_back('(');
    validParentheses(parentheses, n, b1 + 1, b2);
    parentheses.pop_back();
    if(b1 != 0){
        parentheses.push_back(')');
        validParentheses(parentheses, n, b1 - 1, b2);
        parentheses.pop_back();
    }
    //
    parentheses.push_back('[');
    validParentheses(parentheses, n, b1, b2 + 1);
    parentheses.pop_back();
    if(b2 != 0){
        parentheses.push_back(']');
        validParentheses(parentheses, n, b1, b2 - 1);
        parentheses.pop_back();
    }


}

int main(){
    vector<char> parentheses;
    validParentheses(parentheses, 7, 0, 0);
    return 0;
}
// 4096
// ( ( ) ( ( ) ( ) ) ) ( ) ( ) ( ) ( ( ) )
// 172 0 3 8 7 ...
// 1 5
// ( [ ] [ ] )
// ( ( [ ] ( ) ) ( [ ] ) ) ( ) 