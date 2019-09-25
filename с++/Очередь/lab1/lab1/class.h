//
//  class.h
//  lab1
//
//  Created by Spherastree on 15.04.16.
//  Copyright © 2016 икбо-1-14. All rights reserved.
//

#ifndef class_h
#define class_h

#include <queue>
#include <stack>
using namespace std;

class lab1
{
private:
    queue<int> myque;
    int myque2[26];
    stack<int> mystack;
    
    int n,
        st,
        menu_num,
        element;
    
    void add_stacki();
    void add_new();
    void scer();
    void backup();

    void output();
    
public:
    
    void menu();
    
};

void lab1::menu()
{
    cout<<"\n********* МЕНЮ *********\n";
    cout<<  "1. Создать случайный стек\n"
            "2. Добавить новый элемент\n"
            "3. Вывести результат\n"
            "4. Вывести определенный элемент\n";
    cout<<"Выберите пункт меню: ";
    cin>> menu_num;
    cout<<endl;
    switch(menu_num)
    {
        case 1: add_stacki(); menu(); break;
        case 2: add_new();  menu(); break;
        case 3: output(); menu(); break;
        case 4: scer();break;
        default:cout<<"It is not this variant... please repeat\n";
    }
}
void lab1::scer()
{
    bool flag = false;
    cout<<"Введите элемент который хотите вывести: ";
    cin>>element;
    for(int count=1, i=0;i<n;i++,count++)
    {
        if (element==myque2[i])
        {
            cout<<"myque2 ["<<count<<"] "<<myque2[i]<<"\n";
            flag=true;

        }
        else if (element!=myque2[i] && flag == false && i == n-1)
        {
            cout<<"Такого элемента не существует\n";
        }
    }
    
}

void lab1::add_stacki()
{
    n=rand()%15+4;
    for(int i=0;i<n;i++)
    {
        st=rand()% 25+1;
        mystack.push(st);
        myque.push(st);
       
    }
};
void lab1::add_new()
{
    if (mystack.empty() && myque.empty())
    {
        cout<<"Невозможно добавить элемент в пустой контейнер\n";
    }
        else
        {
    
    n++;
    cout<<"Введите новый элемент: ";
    cin>>st;
        mystack.push(st);
        myque.push(st);
        }
}

void lab1::backup()
{
    for(int i=0;i<n;i++)
    {
        mystack.push(myque2[i]);
        myque.push(myque2[i]);
    }
}

void lab1::output()
{
    cout<<"**** Стек **** \t\t **** Очередь ****\n";
    while (!mystack.empty() || !myque.empty())
    {
        for(int count=1, count2=n, i=0;i<n;i++,count++, count2--)
        {
            cout<<"["<<count2<<"] "<<mystack.top();
            cout<<"\t\t\t\t["<<count<<"] "<<myque.front()<<endl;
            myque2[i]=myque.front();
            mystack.pop();
            myque.pop();
        }
    }
    backup();
}

#endif /* class_h */
