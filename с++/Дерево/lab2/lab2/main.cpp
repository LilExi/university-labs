//
//  main.cpp
//  lab2
//
//  Created by Spherastree on 25.04.16.
//  Copyright © 2016 икбо-1-14. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <time.h>
#include <cmath>
using namespace std;

struct Node
{
    int value;
    Node *left, *right, *papa;
};

class Tree
{
public:
    Tree();
    ~Tree();
    bool insert(int value);
    bool remove(int value);
    bool balance();
    void menu();
private:
    Node* root;
    Node* min(Node *node);
    Node* leftRotate(Node* node);
    Node* rightRotate(Node* node);
    Node* Leftmost(Node * node);
    Node* Rightmost(Node * node);
    
    bool insert(int value, Node* node);
    bool remove(int value, Node *node);
    void lkp_print();
    void lkp_print(Node* root);
    void destroyer(Node *node);
    void rotate(Node*node);
    void makebalance(Node*node);
    bool check_balance();
    bool check_balance(Node* root);
    int getHight (Node* root);
    double countSum(Node* node);
    
    bool bbalance;
    bool balance_flag=false;
    
    void del(Node* node);
};

Tree::Tree()
{
    root=NULL;
}
Tree::~Tree()
{
    destroyer(root);
    root=NULL;
}

/*======= Добавление в дерево =========*/
bool Tree::insert(int value,Node *node)// Рекурсивная функция добавления в LorR
{
    if (value < node->value && value!=node->value)
    {
        if (node->left == NULL)
        {
            node->left = new Node;
            (node->left)->value = value;
            (node->left)->right = NULL;
            (node->left)->left = NULL;
            (node->left)->papa = node;
            return true;
        }
        else
        {
            return insert(value, node->left);
        }
    }
    
    else if (value > node->value && value!=node->value)
    {
        if (node->right == NULL)
        {
            node->right = new Node;
            (node->right)->value = value;
            (node->right)->right = NULL;
            (node->right)->left = NULL;
            (node->right)->papa = node;
            return true;
        }
        else
        {
            return insert(value, node->right);
        }
    }
    
    
    return false;
}
bool Tree::insert(int value)           // Функция добавления элемента в корень и определения дальнейшего положения (LorR)
{
    if (root == NULL){
        root = new Node;
        root->value = value;
        root->left=root->right = NULL;
        root->papa=NULL;
        return true;
    }
    
    if (value > root->value && value!=root->value)
        {
            if (root->right==NULL)
            {
                root->right=new Node;
                (root->right)->value = value;
                (root->right)->right=(root->right)->left= NULL;
                (root->right)->papa = root;
                return true;
            }
            else
            {
            return insert(value, root->right);
            }
        }
        else if (value < root->value && value!=root->value)
        {
            if(root->left==NULL)
            {
                root->left=new Node;
                (root->left)->value = value;
                (root->left)->right=(root->left)->left= NULL;
                (root->left)->papa = root;
                return true;
            }
            else
            {
            return insert(value, root->left);
            }
        }
    return false;
}
/*======================================*/


/*============== Удаление ==============*/
Node *Tree::min(Node *node)             // Функция поиска минимального элемента дерева
{
    if (node->left==NULL)
    {
        return node;
    }
    return min(node->left);
}
Node* Tree::Leftmost(Node * node) {
    if (node == NULL)
        return NULL;
    if (node->left != NULL) {
        return Leftmost(node->left);
    }
    return node;
}
Node* Tree::Rightmost(Node * node) {
    if (node == NULL)
        return NULL;
    if (node->right != NULL) {
        return Rightmost(node->right);
    }
    return node;
}
bool Tree::remove(int value)            // 1-ая функция удаления
{
    if (root==NULL)
    {
    return false;
    }
    
    if (root->value==value)
    {
        if (root->left==NULL && root->right==NULL)
        {
            root=NULL;
            return true;
        }
        else if (root->left==NULL || root->right==NULL)
        {
            if (root->right==NULL)
            {
                root=root->left;
                root->left=NULL;
                root->papa=NULL;
                return true;
            }
            else
            {
                root=root->right;
                root->right=NULL;
                root->papa=NULL;
                return true;
            }
        }
        else if (root->left!=NULL && root->right!=NULL)
        {
            root->value=min(root->right)->value;
            root->right=NULL;
            return true;
        }
    }
    else if (value<root->value && root->left!=NULL)
    {
       return remove(value, root->left);
    }
    else
    {
        return remove(value, root->right);
    }
    
    return false;
}
bool Tree::remove(int value, Node *node)// 2-ая функция удаления
{
    if (value==node->value)
    {
        if (node->left==NULL && node->right==NULL)
            {
                if (node->papa != NULL)
                {
                    if ((node->papa)->left == node)
                    {
                        (node->papa)->left = NULL;
                        node=NULL;
                    }
                    else
                    {
                        (node->papa)->right = NULL;
                        node=NULL;
                    }
                }
                //node->papa = NULL;
                node = NULL;
                return true;
            }
        else if (node->left==NULL || node->right==NULL)
        {
            /*if (node->right==NULL)
            {
                if (node->papa!=NULL)
                {
                    if (node->papa->left==node && node->papa->left->left!=NULL)
                    {
                        node->papa->left=node->papa->left->left;
                        node->papa->left->left=NULL;
                        node->papa->left->papa =node->papa;
                        node=node->left;
                        node->left=NULL;
                    }
                    else if (node->papa->right==node && node->papa->left) //node->papa->left->rigt!=0
                    {
                        node->papa->left=node->papa->left->right;
                        node->papa->left->right=NULL;
                        node->papa->left->papa =node->papa;
                        node->left->right=NULL;
                    }
                    
                }
                return true;
        }
            else
            {
                if (node->papa!=NULL)
                {
                    if (node->papa->left==node && node->papa->left->left!=NULL)
                    {
                        node->papa->left=node->papa->left->left;
                        node->papa->left->left=NULL;
                        node->papa->left->papa =NULL;
                        node=node->left;
                        node->left->left=NULL;
                    }
                    else //node->papa->left->rigt!=0
                    {
                        node->papa->left=node->papa->left->right;
                        node->papa->left->right=NULL;
                        node->papa->left->papa =NULL;
                        node=node->right;
                        node->right=NULL;
                    }
                    
                }
                return true;
            }*/
            if (node->left==NULL)
            {
                node->papa->left=node->right;
                node->right->papa=node->papa;
                node=NULL;
                return true;
            }
            else if (node->right==NULL)
            {
                node->papa->left=node->left;
                node->left->papa=node->papa;
                node=NULL;
                return true;
            }
        }
        else if (node->left!=NULL && node->right!=NULL)
        {
            /*node->value=min(node->right)->value;
            /Node*tmp =NULL;
            if(node->left != NULL) {
                tmp = Rightmost(node->left);
            } else
                tmp = Leftmost(node->right);
            
            if (node->papa->left == node)
                node->papa->left = tmp;
            else
                node->papa->right = tmp;
            
            tmp->papa = node->papa;
            tmp->right = node->right;
            //tmp->left = node->left;
            node=NULL;
            delete node;
            return true;*/
            Node* left_max_node = Rightmost(node->left);
            (*node).value = (*left_max_node).value;
            
            del(left_max_node);
            return true;
        }
    }
    
    /*Reeeeeeeeeeee*/
    else if ((value < node->value)&&(node->left != NULL))
    {
        return remove(value, node->left);
    }
    else
    {
        return remove(value, node->right);
    }
    
    
    return false;
}
void Tree::del(Node* node)
{
    node->left = NULL;
    node->right = NULL;
    if (node->papa != NULL){
        if ((node->papa)->left == node){
            (node->papa)->left = NULL;
        }
        if ((node->papa)->right == node){
            (node->papa)->right = NULL;
        }
    }
    node->papa = NULL;
    node = NULL;
    delete node;
}
/*=====================================*/

/*============ Балансировка ===========*/
Node* Tree::leftRotate(Node *node)
{
    if (node->papa != NULL)
    {
        if ((node->papa)->left == node)
        {
            (node->papa)->left = node->right;
        }
        if ((node->papa)->right == node)
        {
            (node->papa)->right = node->right;
        }
    }
    Node* tmp = node->right;
    node->right = (node->right)->left;
    if (node->right != NULL)
    {
        (node->right)->papa = node;
    }
    node->papa = tmp;
    (node->papa)->left = node;
    (node->papa)->papa = NULL;
    
    return node->papa;
}
Node* Tree::rightRotate(Node *node)
{
    if (node->papa != NULL)
    {
        if ((node->papa)->left == node)
        {
            (node->papa)->left = node->left;
        }
        if ((node->papa)->right == node)
        {
            (node->papa)->right = node->left;
        }
    }
    Node* tmp = node->left;
    node->left = (node->left)->right;
    if (node->left != NULL)
    {
        (node->left)->papa = node;
    }
    node->papa = tmp;
    (node->papa)->right = node;
    (node->papa)->papa = NULL;
    
    return node->papa;
}
double Tree::countSum(Node* node)
{
    if (node == NULL)
    {
        return 0;
    }
    return countSum(node->left) + countSum(node->right) + 1;
}
void Tree::rotate(Node *node)
{
    while (node->right != NULL){
        if (node->papa == NULL)
        {
            root = leftRotate(root);
            node = root;
        } else
        {
            Node* t = node->papa;
            if ((node->papa)->left == node)
            {
                node = leftRotate(node);
                node->papa = t;
            }
            if ((node->papa)->right == node)
            {
                node = leftRotate(node);
                node->papa = t;
            }
        }
    }
    if (node->left != NULL)
    {
        rotate(node->left);
    }
}
void Tree::makebalance(Node *node)
{
    while(node->left != NULL)
    {
        node = node->left;
    }
    int i = 2;
    while(!check_balance())
    {
        node = node->papa;
        while(node->papa != NULL)
        {
            for(int j = 0; j < i-1; j++)
            {
                node = node->papa;
            }
            
            if (node == root)
            {
                root = rightRotate(root);
                node = root;
            }else
            {
                Node* t = node->papa;
                node = rightRotate(node);
                node->papa = t;
                node = node->papa;
            }
        }
        i++;
        while(node->left != NULL)
        {
            node = node->left;
        }
    }
}
bool Tree::check_balance()
{
    return check_balance(this->root);
}
bool Tree::check_balance(Node* root)
{
    if (root == NULL)
        return true;
    if (!check_balance(root->left))
        return false;
    if (!check_balance(root->right))
        return false;
    int left = getHight (root->left);
    int right = getHight (root->right);
    if (abs(left - right) > 1)
        return false;
    return true;
}
int Tree::getHight (Node* root)
{
    if (root == NULL)
        return 0;
    int left = getHight(root->left);
    int right = getHight(root->right);
    return max(left, right) + 1;
}
bool Tree::balance()
{
    double n = log2((countSum(root)+1));
    int x = n;
    if ((root == NULL)||(n != x))
    {
        return false;
    }
    else
    {
        rotate(root);
        makebalance(root);
        return true;
    }
    return false;
}
/*=====================================*/


/*=============== Вывод ===============*/
void Tree::lkp_print()                 // Вспомогательная функция вывода
{
    
    cout<<  "\n⎧‾‾‾‾‾‾‾‾‾‾⎫\n"
            "⎪  Дерево  ⎪\n"
            "⎩__________⎭:→ ";
    
    if (root==NULL)
    {
        cout<<"Тут пока пусто, но ты можешь это изменить!\n";
    }
    else if (root!=NULL && balance_flag==false)
    {
        cout<<"[ ";
        lkp_print(this->root);
        cout<<"] - <(￣︶￣)>\n";
    }
    else if (bbalance==false && balance_flag==true)
    {
        cout<<"[ ";
        lkp_print(this->root);
        cout<<" ] - является сбалансированным\n";
    }
    else if (bbalance==true && balance_flag==true)
    {
        cout<<"[ ";
        lkp_print(this->root);
        cout<<" ] - дерево сбалансированно\n";
    }
}
void Tree::lkp_print(Node* root)       // Рекурсивная функция вывода дерева
{
    if (root == NULL)
        return;
    lkp_print(root->left);
    cout<< root->value << " " ;
    lkp_print(root->right);
    
    /*
     while (root!=NULL)
     {
      lkp_print(root->right)
     }
     */
}
/*=====================================*/

void Tree::destroyer(Node* node)
{
    if (node != NULL)
    {
        destroyer(node->left);
        destroyer(node->right);
        node=NULL;
    }
}
void Tree::menu()
{

    int command, command_inp, value=0, n;
    srand(time(0));
    
    cout<<"\n⎧‾‾‾‾‾‾‾‾‾‾  МЕНЮ  ‾‾‾‾‾‾‾‾‾‾⎫\n";
    cout<<  "⎪1. Добавить элемент в дерево⎪\n"
            "⎪2. Удалить элемент из дерева⎪\n"
            "⎪3. Сбалансировать дерево    ⎪\n"
            "⎪4. Вывести дерево           ⎪\n"
            "⎪0. Выйти из программы       ⎪\n";
    cout<<  "⎪                            ⎪\n"
            "⎪    Выберите пункт меню     ⎪\n";
    cout<<  "⎩____________________________⎭:→ ";
    cin>> command;
    cout<<"\n";
    switch(command)
    {
        case 1:
        {
            cout<<  "1. Ввести в ручную.\n"
                    "2. Ввести рандомные числа.\n:→";
            cin>>command_inp;
            switch (command_inp)
            {
                case 1:
                    cout<<"Введите элемент, который хотите добавить в дерево: ";
                    cin>>value;
                    if (!insert(value))
                    {
                        usleep(150000);
                        cout<<"Элемете [ "<<setw(2)<<value<<" ] уже существует.\n";
                    }
                    else
                    {
                        usleep(150000);
                        cout<<"Элемете [ "<<setw(2)<<value<<" ] "<<"добавлен в дерево.\n";
                    }
                    break;
                case 2:
                    cout<<"Введите количество элементов дерева: ";
                    cin>>n;
                    if (n==0)
                    {
                        cout<<"Ну ты и ретард (ಠ_ಠ)\n";
                    }
                    while (n!=0)
                    {
                        value=rand()%50+1;
                        if (!insert(value))
                        {
                            usleep(150000);
                            cout<<"Элемете [ "<<setw(2)<<value<<" ] уже существует.\n";
                        }
                        else
                        {
                            usleep(150000);
                            cout<<"Элемете [ "<<setw(2)<<value<<" ] "<<"добавлен в дерево.\n";
                        }
                        
                        n--;
                    }
                    break;
                
                default:
                    menu();
            }
            menu();
            break;
            
            
         /*cout<<"Введите количество элементов дерева: ";
            cin>>n;
            if (n==0)
            {
                cout<<"Ну ты и ретард (ಠ_ಠ)\n";
            }
            while (n!=0)
            {
                value=rand()%50+1;
                if (!insert(value))
                {
                    usleep(150000);
                    cout<<"Элемете [ "<<setw(2)<<value<<" ] уже существует.\n";
                }
                else
                {
                    usleep(150000);
                    cout<<"Элемете [ "<<setw(2)<<value<<" ] "<<"добавлен в дерево.\n";
                }

                n--;
            }
            //myTree.lkp_print();
            menu();
            break;*/
        }
        case 2:
        {
            cout<<"Введите элемент, который хотите удалить: ";
            cin>>value;
            if (!remove(value))
            {
                cout<<"Элемета [ "<<setw(2)<<value<<"  ] не существует.\n";
            }
            else
            {
                cout<<"Элемете [ "<<setw(2)<<value<<"  ] удален.\n";
            }
            cout<<endl;
            menu();

            break;
        }
        case 3:
        {
            balance_flag=true;
            if (!balance())
            {
                bbalance=false;
            }
            else
            {
                bbalance=true;
            }
            
                lkp_print();
                cout<<endl;
            menu();
            break;
        }
            case 4:
        {
            lkp_print(); menu(); break;
            
        }
        case 0: ;
        default:cout<<"It is not this variant... please repeat\n";
    }
    
}
int main()
{
    Tree run;
    run.menu();
    
}
