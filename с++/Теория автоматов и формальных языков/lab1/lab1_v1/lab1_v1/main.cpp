//
//  automat.cpp
//  lab1
//
//  Created by Spherastree on 28.03.2018.
//  Copyright © 2018 икбо-5-15. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

class automat {
private:
    int start_state;
    list<int> final_state;
    map<int,map<char,int>> map_state;
    
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
        cout << state << " ";
        char curr = str.at(p);
        int next_state = get_next(state, curr);
        if (next_state == 0) break;
        state = next_state;
        p++;
        cout << curr << " " << next_state << endl;
    }
    bool found = (find(final_state.begin(), final_state.end(), state) != final_state.end());
    if (found && p == str.length()){
        return true;
    }
    else {
        cout<<" << [err] " << "\n";
        return false;
    }
};

int main(){
    //char text[11] = "31.01.1995";
    int S0 = 0;
    int S1 = 1;
    int S2 = 2;
    int S3 = 3;
    int S4 = 4;
    int S5 = 5;
    int S6 = 6;
    int S7 = 7;
    int S8 = 8;
    int S9 = 9;
    int S10 = 10;
    int S11 = 11;
    int S12 = 12;
    
    list<char> zero_to_nine;
    list<char> one_to_nine;
    list<char> one_and_zero;
    list<char> zero_to_two;
    list<char> three;
    list<char> symbol;
    
    char ztn[] = {'0','1','2','3','4','5','6','7','8','9'};
    for (int i = 0; i<10;i++){
        zero_to_nine.push_back(ztn[i]);
    }
    char otn[] = {'1','2','3','4','5','6','7','8','9'};
    for (int i = 0; i<9; i++){
        one_to_nine.push_back(otn[i]);
    }
    
    one_and_zero.push_back('0');
    one_and_zero.push_back('1');
    
    char ztt[] = {'0','1','2'};
    for (int i = 0; i<3; i++){
        zero_to_two.push_back(ztt[i]);
    }
    
    three.push_back('3');
    symbol.push_back('.');
    
    list<int> final_state;
    final_state.push_back(S12);
    
    automat a(S0, final_state);
    
    a.add_step(S0, zero_to_two, S1);
    a.add_step(S0, three, S2);
    a.add_step(S1, one_to_nine, S3);
    a.add_step(S2, one_and_zero, S3);
    
    a.add_step(S3, symbol, S4);
    
    a.add_step(S4, '0', S5);
    a.add_step(S4, '1', S6);
    a.add_step(S5, zero_to_nine, S7);
    a.add_step(S6, zero_to_two, S7);
    
    a.add_step(S7, symbol, S8);
    
    a.add_step(S8, zero_to_nine, S9);
    a.add_step(S9, zero_to_nine, S10);
    a.add_step(S10, zero_to_nine, S11);
    a.add_step(S11, zero_to_nine, S12);
    
    string str;
    str = "01.09.2007";
    //cin >> str;
    if (a.does_match(str) == true) {
        cout << "[Correct expression]\n";
    }
}

