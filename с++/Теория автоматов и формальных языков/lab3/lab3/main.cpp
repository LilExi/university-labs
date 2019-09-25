//
//  main.cpp
//  lab3
//
//  Created by Spherastree on 10.04.2018.
//  Copyright © 2018 икбо-5-15. All rights reserved.
//
/*
 A -> E
 E -> T + E | T - E | T
 T -> F * T | F / T | F
 F -> P ^ F | P
 P ->  L | U | UL | (A)
 U -> + | -
 L -> D | DL
 D -> 0 | 1 | ... | 8 | 9
 */

#include <iostream>
#include <list>
#include "stmash.h"

using namespace std;
    //int i = 0;

class bnf_class {
private:
    string text;
    int i;
public:
    bnf_class(string t);
    bool expression_a(); // A -> I = E | E
    bool expression_e(); // E -> T + E | T - E | T
    bool expression_t(); // T -> F * T | F / T | F
    bool expression_f();
    bool expression_p(); // P -> L | U | UL | (A)
    bool expression_l(); // L -> D | DL
};
bnf_class::bnf_class(string t){
    text = t;
    i = 0;
};

bool bnf_class::expression_a(){
    return expression_e();
};

bool bnf_class::expression_e(){
    if (expression_t())
    {
        if (text.at(i) == '+' || text.at(i) == '-')
        {
            if(i < text.length()) ++i;
            return expression_e();
        }
        return true;
    }
    return false;
};

bool bnf_class::expression_t()
{
    if (expression_f())
    {
        if(text.at(i) == '*' || text.at(i) == '/')
        {
            if(i < text.length()) ++i;
            if (text.at(i) == '(') return expression_p();
            else return expression_l();
        }
        return true;
    }
    return false;
};

bool bnf_class::expression_f(){
    if(expression_p())
    {
        if(text.at(i) == '^')
        {
            if(i < text.length()) ++i;
            return expression_f();
        }
        return true;
    }
    return false;
}

bool bnf_class::expression_p(){
    if(expression_l()) return true;
    else if (text.at(i) == '+' || text.at(i) == '-') expression_l();
    else if (text.at(i) == '(')
    {
        if(i < text.length()) ++i;
        if(expression_a())
        {
            if(text.at(i) == ')') {
                if(i < text.length()) ++i;
                return true;
            }
            else
                return false;
        }
    }
    return false;
};

bool bnf_class::expression_l(){
    if (text.at(i) >= '0' && text.at(i) <= '9')
    {
        if(i < text.length()) ++i;
        /*if (!L() && line.charAt(i) != '+'&& line.charAt(i) != '-'&& line.charAt(i) != '*' && line.charAt(i) != '/' && line.charAt(i) != ' ')
         return false;
         else return true;*/ //Просто хотел попробовать, ничего не вышло
        expression_l();
        
        return true;
    }
    //else return false;
    
    return false;
}



int main(int argc, const char * argv[]) {
    bool flag = true;
    bool tmp_flag = false;
    //string text = "(((15+5)*4)/(100/25))*2";
    //string text = "(8+7)*(5+3)";
    string text = "(8+(6/2+10)*(3+1))/2";
    list<char> m_chars;
    text += " ";
    bnf_class b(text);
    char chr[] = {'1','2','3','4','5','6','7','8','9','0','+','-','/','*','(',')',' '};
    for (int k = 0; k<strlen(chr); k++){
        m_chars.push_back(chr[k]);
    }
    
    for(int j = 0; j < text.length(); j++)
    {
        tmp_flag = false;
        for(char ch : chr)
            if(ch == text.at(j))
                tmp_flag = true;
        if (!tmp_flag)
        {
            flag = false;
            break;
        }
    }
    
    //cout << b.expression_a();
    if(b.expression_a() == true && flag)
    {
        cout << "[Correct expression] " << text << "= ";
        st_machine(text);
        cout << "\n";
    }
    else {
        cout << "[Uncorrect expression] " << text << "\n";
    }
    
    return 0;
}
