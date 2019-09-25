//
//  lab1.h
//  lab1_v1
//
//  Created by Spherastree on 19.04.16.
//  Copyright © 2016 икбо-1-14. All rights reserved.
//

#ifndef lab1_h
#define lab1_h

#include <cassert>
#include <time.h>
using namespace std;

struct number {
    int x;
    number *next;
};

class queuq
{
public:
    void enqq();
    void outqq();
    number *top, *first=NULL, *p;
    number *top1, *first1=NULL, *p1;
    number *mystack_top, *mystack_first=NULL, *mystack_p;
    int meh=NULL;
private:
    int n=0;
};

void queuq::enqq()
{
    srand(time(0));
    if (first==NULL)
    {
    top= new number;
    top->next=NULL;
    top->x=rand() %9 +1;
    first=top;
    }
    else
    {
        p=new number;
        p->next=NULL;
        p->x=rand() %9 +1;
        top->next=p;
        top=p;
    }
}
void queuq::outqq()
{
    p=first;
    cout<<endl;
    cout<<  "⎧‾‾‾‾‾‾‾‾‾⎫\n"
            "⎪ Очередь ⎪\n"
            "⎩_________⎭:→ ";
    if (first==NULL)
    {
        cout<<"пуста =С\n";
    }
    else
    {
        while (first!=0)
        {
            cout<< first->x <<" ";
            first=first->next;
        }
    }
    cout<<endl;
    first=p;
    
}
/*void queuq::outsss()
{
    while (first!=NULL)
    {
        while (first->next!=NULL)
        {
            if (first1==NULL)
            {
                top1= new number;
                top1->next=NULL;
                top1->x=first->x;
                first1=top1;
            }
            else
            {
                p1= new number;
                p1->next=NULL;
                p1->x=first->x;
                top1->next=p1;
                top1=p1;
            }
            first=first->next;
        }
        meh=first->x;
        first=first1;
        first1=NULL;
        
        if (mystack_first==NULL)
        {
            mystack_top= new number;
            mystack_top->next=NULL;
            mystack_top->x=meh;
            mystack_first=mystack_top;
        }
        else
        {
            mystack_p= new number;
            mystack_p->next=NULL;
            mystack_p->x=meh;
            mystack_top->next=mystack_p;
            mystack_top=mystack_p;
        }
    }
    cout<<"MYSTACK: ";
    while (mystack_first!=NULL)
    {
        cout<< mystack_first->x << " ";
        mystack_first=mystack_first->next;
    }
}*/



class stack
{
private:
    queuq q;
public:
    void enss(number *first, number *top, number *p, number *first1, number *top1, number *p1, number *mystack_top, number *mystack_first, number *mystack_p, int &meh);
    bool f=false, myout=false;
    int k=NULL;
    //void outss(number *mystack_first);
};

void stack::enss(number *first, number *top, number *p, number *first1, number *top1, number *p1, number *mystack_top, number *mystack_first, number *mystack_p, int &meh)
{
    while (first!=NULL)
    {
        while (first->next!=NULL)
        {
            if (first1==NULL)
            {
                top1= new number;
                top1->next=NULL;
                top1->x=first->x;
                first1=top1;
            }
            else
            {
                p1= new number;
                p1->next=NULL;
                p1->x=first->x;
                top1->next=p1;
                top1=p1;
            }
            first=first->next;
        }
        meh=first->x;
        first=first1;
        first1=NULL;
        /*MEEEH*/
        if (mystack_first==NULL)
        {
            mystack_top= new number;
            mystack_top->next=NULL;
            mystack_top->x=meh;
            mystack_first=mystack_top;
        }
        else
        {
            mystack_p= new number;
            mystack_p->next=NULL;
            mystack_p->x=meh;
            mystack_top->next=mystack_p;
            mystack_top=mystack_p;
        }
    }
    cout<<  "⎧‾‾‾‾‾‾‾‾‾⎫\n"
            "⎪  Стек   ⎪\n"
            "⎩_________⎭:→ ";
    if (mystack_first==NULL)
    {
        cout<<"пуст =C\n";
    }
    else
    {
        if ((myout==true) && (f==false))
        {
        while (mystack_first!=NULL)
        {
            cout<< mystack_first->x << " ";
            mystack_first=mystack_first->next;
        }
        }
        else if (myout==true && f==true)
        {
            cout<<"| ";
            while (mystack_first!=NULL)
            {
                cout<< mystack_first->x << " ";
                mystack_first=mystack_first->next;
            }
        }
       else if (myout==false && f==true)
        {
            for (int i=0;i<k;i++)
            {
                cout<< mystack_first->x << " ";
                mystack_first=mystack_first->next;
            }
            cout<<"|→ ";
            while (mystack_first!=NULL)
            {
                cout<< mystack_first->x << " ";
                mystack_first=mystack_first->next;
            }
        }
    }
    cout<<endl;
}
/*void stack::outss(number *mystack_first)
{
    cout<<"Стек: ";
    if (mystack_first==NULL)
    {
        cout<<"пуст :C\n";
    }
    else
    {
    while (mystack_first!=NULL)
    {
        cout<< mystack_first->x << " ";
        mystack_first=mystack_first->next;
    }
    }
    cout<<endl;
}*/


/* MENU*/
class menu
{
public:
    void outmenu();
    void addqq();
    void amount_el();
    void loading();
private:
    int menu_num;
    queuq q;
    stack s;
    int n=0;
    int ch;
};
void menu::outmenu()
{
        cout<<"\n⎧‾‾‾‾‾‾‾‾‾‾ МЕНЮ ‾‾‾‾‾‾‾‾‾‾⎫\n";
        cout<<  "⎪1. Добавить элемент в стек⎪\n"
                "⎪2. Вывести стек           ⎪\n"
                "⎪0. Завершить программу    ⎪\n";
        cout<<  "⎪                          ⎪\n"
                "⎪   Выберите пункт меню    ⎪\n";
        cout<<  "⎩__________________________⎭:→ ";
        cin>> menu_num;
        cout<<"\n";
        switch(menu_num)
        {
            case 1: s.myout=false; amount_el(); q.outqq(); outmenu(); break;
            case 2: s.myout=true; s.k=0; s.enss(q.first,q.top,q.p,q.first1,q.top1,q.p1,q.mystack_top,q.mystack_first,q.mystack_p,q.meh); outmenu();  break;
            case 0: s.f=true; q.outqq(); s.enss(q.first,q.top,q.p,q.first1,q.top1,q.p1,q.mystack_top,q.mystack_first,q.mystack_p,q.meh); break; exit(EXIT_SUCCESS);
            default:cout<<"It is not this variant... please repeat\n";
        }
}

void menu::amount_el()
{
    cout<<"Введите кол-во элементов, которые хотите положить в стек: ";
    cin>>n;
    while (n!=0)
    {
        if (s.myout==false)
        {
            s.k++;
        }
        sleep(1);
        q.enqq();
        n--;
    }
}


#endif /* lab1_h */
