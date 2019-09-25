//
//  main.cpp
//  lab3
//
//  Created by Spherastree on 04.05.16.
//  Copyright © 2016 икбо-1-14. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;

struct DATA
{
    char key[8] = "";
    int value;
};

class hashtab
{
private:
    int size;
    vector<DATA*> *hashArray;
    bool rm=false;
    DATA *data;
    
public:
    int maxComplexity = 0;
    float averageComplexity = 0;
    hashtab(int n);
    DATA* hashtab_find(char *key);
    bool hashtab_add(DATA *data);
    void hashtab_remove(char *key);
    void hashtab_print();
    
    int hashtab_function(char *key);
    
    void runmenu();
};

hashtab::hashtab(int n)
{
    hashArray= new vector<DATA*>[n];
    for (int i=0; i<n; i++)
    {
        hashArray[i].push_back(NULL);
    }
    size= n;
}
int hashtab::hashtab_function(char *key)
{
   /* unsigned int hash = 0;
    
    for(; *key; key++)
    {
        hash += (unsigned char)(*key);
        hash -= (hash << 13) | (hash >> 19);
    }
    
    return hash;*/
    
    unsigned int hash= 0;
    char *p;
    for (p= key; *p!= '\0'; p++)
        hash =hash*128+(unsigned int)*p; //31
    return hash % 500;
}
DATA* hashtab::hashtab_find(char *key)
{
    unsigned int hkey= hashtab_function(key);
    if (hashArray[hkey].size() == 1)
    {
        return NULL;
    }
    
    for(int i = 0; i < hashArray[hkey].size()-1; i++)
    {
        if ((strcmp(hashArray[hkey][i]->key, key) == 0))
        {
            return hashArray[hkey][i];
        }
    }
    return hashArray[hkey][0];
}
bool hashtab::hashtab_add(DATA *data)
{
    int hkey= hashtab_function(data->key);
    if (hashtab_find(data->key) == NULL)
    {
        hashArray[hkey][hashArray[hkey].size()-1] = data;
        hashArray[hkey].push_back(NULL);
        return true;
    }
    return false;
}
void hashtab::hashtab_print()
{
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < hashArray[i].size()-1; j++)
            {
                usleep(70000);
                cout<<"["<<setw(3)<<i<<"] "<<"value= "<<setw(5)<<hashArray[i][j]->value<<" | "<<"key= "<<setw(7)<<hashArray[i][j]->key<<"\t\n";
                if ((j + 1) > maxComplexity)
                {
                    maxComplexity = j + 1;
                }
                averageComplexity = averageComplexity + (j + 1);
            }
        }
        averageComplexity = averageComplexity / size;
    cout<<"\nMaximum complexity = "<<maxComplexity<<endl;
    cout<<"Average complexity = "<<averageComplexity<<endl;
}
void hashtab::hashtab_remove(char *key)
{
    unsigned int hkey = hashtab_function(key);
    if (hashtab_find(key) == NULL)
    {
        cout<<setw(10)<<"[!]  Ключ "<<setw(7)<<key<<" не найден\t\n";
    }
    else
    {
        for(int i = 0; i < hashArray[hkey].size()-1; i++)
        {
            if (hashtab_find(key) == hashArray[hkey][i])
            {
                cout<<setw(10)<<"[del] "<<"value= "<<setw(4)<<hashtab_find(key)->value<<" | "<<"key= "<<setw(7)<<hashtab_find(key)->key<<"\t\n";
                delete hashtab_find(key);
                hashArray[hkey][hashArray[hkey].size()-2] = NULL;
                hashArray[hkey].pop_back();
            }
        }
    }
}

void hashtab::runmenu()
{
    int command, k;
    char key[10];
    srand((unsigned int)time(0));
    
    cout<<"\n⎧‾‾‾‾‾‾‾‾‾‾‾‾‾  МЕНЮ  ‾‾‾‾‾‾‾‾‾‾‾‾‾⎫\n";
    cout<<  "⎪1. Добавить элемент в хеш-таблицу ⎪\n"
            "⎪2. Удалить элемент из хеш-таблицы ⎪\n"
            "⎪3. Вывести хеш-таблицу            ⎪\n"
            "⎪0. Выйти из программы             ⎪\n";
    cout<<  "⎪                                  ⎪\n"
            "⎪       Выберите пункт меню        ⎪\n";
    cout<<  "⎩__________________________________⎭:→ ";
    cin>> command;
    cout<<"\n";
    switch(command)
    {
        case 1:
            cout<<"Введите количество элементов которые хотите добавить в таблицу: ";
            cin>> k;
            for (int i=0; i<k; i++)
            {
                DATA *data= new DATA;
                data->value = rand()%10000+ 1;
                for(int i = 0, j = 7; i < j; i++)
                {
                    data->key[i] = (char)(rand()%26+65);
                }
                
                if (!hashtab_add(data))
                {
                    usleep(70000);
                    cout<<setw(10)<<"[!] [add] "<<"value= "<<setw(4)<<data->value<<" | "<<"key= "<<setw(7)<<data->key<<"\t\n";
                }
                else
                {
                    usleep(70000);
                    cout<<setw(10)<<"[add] "<<"value= "<<setw(4)<<data->value<<" | "<<"key= "<<setw(7)<<data->key<<"\t\n";
                }
            } runmenu();
            break;
            
        case 2:
            cout<<"Введите ключ элемента, который хотели бы удалить: ";
            cin>>key;
            hashtab_remove(key);
            runmenu();
            break;
        case 3:
            cout<<"\nВаша хеш-таблица: \n";
            hashtab_print();
            runmenu();
            break;
        case 0: exit(EXIT_SUCCESS);
    }
}

int main()
{
    hashtab h(500);
    h.runmenu();
    
    
    
    return 0;
}
