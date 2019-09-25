//
//  main.cpp
//  lab1
//
//  Created by Spherastree on 27.03.2018.
//  Copyright © 2018 икбо-5-15. All rights reserved.
//

#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;

struct Table_Entry
{
    unsigned int  current_state_id;
    unsigned char transition_letter;
    unsigned int  next_state_id;
};

Table_Entry const *    table_begin(void);
Table_Entry const *    table_end(void);

static const Table_Entry    my_table[] =
{
    //  Current   Transition     Next
    //  State ID    Letter     State ID
    {0, '0', 1}, {0, '1', 1}, {0, '2', 1}, {0, '3', 1},                 //переходы из 0 состояния в 1 (число от 0 до 3)

    {1, '0', 2}, {1, '1', 2}, {1, '2', 2}, {1, '3', 2}, {1, '4', 2},    // переходы из 1 состояния в 2
    {1, '5', 2}, {1, '6', 2}, {1, '7', 2}, {1, '8', 2}, {1, '9', 2},    // (число от 0 до 9)
    
    {2, '.', 3},                                                        // переход из 2 состояния в 3 (переход по '.')
    
    {3, '0', 4},                                                        // переход из 3 состояния в 4 (число 0)
    {3, '1', 5},                                                        // переход из 3 состояния в 5 (число 1)
    
    {4, '0', 5},
    {    4,     '1',    5},
    {    4,     '2',    5},
    {    4,     '3',    5},
    {    4,     '4',    5},
    {    4,     '5',    5},
    {    4,     '6',    5},
    {    4,     '7',    5},
    
    
    
    {    3,     '3',    2},
    {    0,     '3',    1}, // From 0 goto 3 if letter is 'C'.
    {    1,     'A',    1}, // From 1 goto 1 if letter is 'A'.
    {    1,     'B',    3}, // From 1 goto 3 if letter is 'B'.
    {    1,     'C',    0}, // From 1 goto 0 if letter is 'C'.
};

static const unsigned int  TABLE_SIZE = sizeof(my_table) / sizeof(my_table[0]);

Table_Entry const * table_begin(void)
{
    return &my_table[0];
}

Table_Entry const * table_end(void)
{
    return &my_table[TABLE_SIZE];
}

void Execute_State_Machine(void)
{
    char text[11] = "31.01.1995";
    unsigned int current_state = 0;
    while (1)
    {
        char transition_letter;
        cout << "Current state: " << current_state << "\n";
        
        for (int i = 0; i<=11; i++) {
            transition_letter = text[i];
        
        cout << "Enter transition letter: " << transition_letter << "\n";
//cin >> transition_letter;
//cin.ignore(1000, '\n'); /* Eat up the '\n' still in the input stream */
        Table_Entry const *  p_entry = table_begin();
        Table_Entry const * const  p_table_end =  table_end();
        bool state_found = false;
        while ((!state_found) && (p_entry != p_table_end))
        {
            if (p_entry->current_state_id == current_state)
            {
                if (p_entry->transition_letter == transition_letter)
                {
                    cout << "State found, transitioning" << " from state " << current_state << ", to state " << p_entry->next_state_id<< "\n";
                    current_state = p_entry->next_state_id;
                    state_found = true;
                    break;
                }
            }
            ++p_entry;
        }
            
        if (!state_found)
        {
            cerr << "Transition letter not found, current state not changed.\n";
        }
        }
    }
}

int main(int argc, const char * argv[]) {
    Execute_State_Machine();
    return 0;
}
