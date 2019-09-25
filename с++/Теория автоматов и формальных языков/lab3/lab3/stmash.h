//
//  stmash.h
//  lab3
//
//  Created by Spherastree on 10.04.2018.
//  Copyright © 2018 икбо-5-15. All rights reserved.
//

#ifndef stmash_h
#define stmash_h

#include <stack>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int prior (char s)
{
    int a = 0;
    switch (s) {
        case '*':
            a = 3;
            break;
        case '/':
            a = 3;
            break;
        case '-':
            a = 2;
            break;
        case '+':
            a = 2;
            break;
        case '(':
            a = 1;
            break;
    }
    return a;
}

void st_machine (string text) {
    stack<char> st;
    stack<int> val_stack;
    //string a;
    string tmp = "", numbers = "";
    int count = 0, pp = 0, temp = 0, outputi = 0,
    point = 0, n1=0, n2=0, res,
    p = 0, i = 0;
    /*
     while (p < text.length()){
     tmp = "";
     while (isdigit(text[p]))
     {
     tmp += text[p];
     count++;
     p++;
     }
     if (count > 0)
     {
     
     numbers[numCount] = atoi(tmp.c_str());
     numCount++;
     p += count;
     count = 0;
     p -= 2;
     }
     p++;
     }
     for (i = 0; i < numCount; i++) {
     cout << numbers[i] << " ";
     }
     */
    
    while (p < text.length()){
        tmp = "";
        while (isdigit(text[p]))
        {
            tmp += text[p];
            count++;
            p++;
        }
        if (count > 0)
        {
            numbers += tmp;
            numbers += " ";
            p += count;
            temp = count;
            count = 0;
            p -= temp;
        }
        
        if (text[p] == '+' || text[p] == '-' || text[p] == '/' || text[p] == '*'){
            if (st.empty()){
                st.push(text[p]);
            }
            else {
                if (prior(st.top()) < prior(text[p])){
                    st.push(text[p]);
                }
                else {
                    while (prior(st.top()) >= prior(text[p])){
                        numbers += st.top(); st.pop(); numbers += " ";
                    }
                    st.push(text[p]);
                }
            }
        }
        
        if ( text[p] == '('){
            st.push( text[p]);
        }
        
        if ( text[p] == ')'){
            while (st.top() != '('){
                numbers += st.top(); st.pop(); numbers += " ";
            }
            if (st.top() == '('){
                st.pop();
            }
        }
        p++;
    }
    
    while (st.empty() != true) {
        numbers += st.top(); st.pop(); numbers += " ";
    }
    
    //
    for (i = 0; i<numbers.length(); i++){
        tmp = "";
        pp = i;
        point = 0;
        while (numbers[pp] != ' '){
            tmp += numbers[pp];
            pp++;
            point++;
        }
        switch (point){
            case 2: i+=1; break;
            case 3: i+=2; break;
            case 4: i+=3; break;
        }
        
        if (isdigit(tmp[0])){
            val_stack.push(atoi(tmp.c_str()));
        }
        else if (tmp[0] == '/' || tmp[0] == '+' || tmp[0] == '-' || tmp[0] == '*')
        {
            n2 = val_stack.top(); val_stack.pop();
            n1 = val_stack.top(); val_stack.pop();
            
            switch (numbers[i]){
                case '+': res = n1+n2; break;
                case '-': res = n1-n2; break;
                case '*': res = n1*n2; break;
                case '/': res = n1/n2; break;
            }
            val_stack.push(res);
        }
    }
    outputi = val_stack.top();
    
    cout<< outputi << "\n";
}

#endif /* stmash_h */
