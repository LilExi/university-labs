//
//  main.cpp
//  lab2
//
//  Created by Spherastree on 03.04.2018.
//  Copyright © 2018 икбо-5-15. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include "stackmachine.h"
using namespace std;

class automat
{
private:
    int start_state;
    list<int> final_state;
    map<int,map<char,int>> map_state;
    int br = 0;
    
public:
    automat (int start_state, list<int> final_states);
    void add_step(int from_state, char ch, int to_state);
    void add_step(int from_state, list<char> characters, int to_state);
    int get_next(int from_state, char ch);
    bool does_match(string str);
    void set_startstate(int start_state);
};

automat::automat (int Start_state, list<int> Final_state) {
    start_state = Start_state;
    final_state = Final_state;
};

void automat::add_step(int from_state, char ch, int to_state){
    map<char,int> tmp;
    if (map_state.find(from_state) != map_state.end()){
        //tmp.insert(pair<char,int>(ch,to_state));
        tmp[ch] = to_state;
        //map_state[from_state] = tmp;
        map_state[from_state].insert(pair <char,int>(ch, to_state));
    }
    else {
        tmp = map_state[from_state];
        //tmp.insert(pair<char, int>(ch,to_state));
        tmp[ch] = to_state;
        //map_state[from_state] = tmp;
        map_state[from_state].insert(pair <char,int>(ch,to_state));
    }
};

void automat::add_step(int from_state, list<char> characters, int to_state){
    for (char ch : characters){
        add_step(from_state, ch, to_state);
    }
};

int automat::get_next(int from_state, char ch){
    map<char,int> state_tras;
    state_tras = map_state[from_state];
    return state_tras[ch];//[ch];
};

bool automat::does_match(string str){
    int state = start_state;
    int p = 0;
    while (p < str.length()) {
        //cout << state << " ";
        char curr = str.at(p);
        if (curr == '(') {
            br++;}
        else if (curr == ')') {
            br--;
        }
        int next_state = get_next(state, curr);
        if (next_state == 0) break;
        state = next_state;
        p++;
        //cout << curr << " " << next_state << endl;
    }
    bool found = (find(final_state.begin(), final_state.end(), state) != final_state.end());
    if (found && p == str.length() && br == 0){
        return true;
    }
    else {
        cout<<" << [err]" << "\n";
        return false;
    }
};

int main(int argc, const char * argv[]) {
    int s0 = 0;
    //int s1 = 1;
    int s2 = 2;
    int s3 = 3;
    int s4 = 4;
    
    list<char>zero_to_nine;
    list<char>oper;
    list<char>close_br;
    list<char>open_br;
    list<int>final_state;
    
    char ztn[] = {'0','1','2','3','4','5','6','7','8','9'};
    for (int i = 0; i<10;i++){
        zero_to_nine.push_back(ztn[i]);
    }
    
    char ops[] = {'-','+','*','/'};
    for (int i = 0; i<4;i++){
        oper.push_back(ops[i]);
    }
    
    close_br.push_back(')');
    open_br.push_back('(');
    
    final_state.push_back(s4);
    
    automat a(s0, final_state);
    
    a.add_step(s0, zero_to_nine, s4);
    a.add_step(s0, open_br, s3);
    a.add_step(s4, zero_to_nine, s4);
    a.add_step(s4, oper, s2);
    a.add_step(s4, close_br, s4);
    a.add_step(s3, open_br, s3);
    a.add_step(s3, zero_to_nine, s4);
    a.add_step(s2, zero_to_nine, s4);
    a.add_step(s2, open_br, s3);
    a.add_step(s0, '-', s2);
    
    string f = "(8+(6/2+10)*(3+1))/2";
    //string f = "300+(52-2)*4";
    if (a.does_match(f) == true) {
        cout << "[Correct expression] " << f << " = ";
        st_machine(f);
    }
    else{
        cout << "[Uncorrect expression] " << f;
    }
    return 0;
}
