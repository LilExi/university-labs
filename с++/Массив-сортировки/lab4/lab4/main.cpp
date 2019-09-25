//
//  main.cpp
//  lab4
//
//  Created by Spherastree on 08.05.16.
//  Copyright © 2016 икбо-1-14. All rights reserved.
//

#include <iostream>
#include <iomanip>

using namespace std;

class lab4
{
private:
    int *arr = new int [10000000];
    int *arrtmp = new int [10000000];
    unsigned int start_time;
    unsigned int end_time;
    float search_time, s1,s2,s3;
public:
    int size = NULL;
    lab4();
    ~lab4();
    bool check_arr(int *arr);
    void bubbleSort();
    void selectSort();
    void quickSortR(int* arr, long size);
    void backup_save();
    void backup_load();
    void menu();
};

lab4::lab4()
{
    for (int i=0; i<size; i++)
    {
        arr[i]=NULL;
    }
}

lab4::~lab4()
{
    delete [] arr;
}

void lab4::selectSort()
{
    start_time=(unsigned int)clock();
    int temp;
    for (int i=0;i<size; i++)
    {
        int pos=i;
        temp=arr[i];
        for(int j = i + 1; j < size; ++j) // цикл выбора наименьшего элемента
        {
            if (arr[j] < temp)
            {
                pos = j;
                temp = arr[j];
            }
        }
        arr[pos] = arr[i];
        arr[i] = temp; // меняем местами наименьший с a[i]
    }
    end_time=(unsigned int)clock();
    s1=end_time-start_time;
}

void lab4::bubbleSort()
{
    start_time=(unsigned int)clock();
    int temp;
    for(int i = 0; i < size - 1; ++i) // i - номер прохода
    {
        for(int j = 0; j < size - 1; ++j) // внутренний цикл прохода
        {
            if (arr[j + 1] < arr[j])
            {
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    end_time=(unsigned int)clock();
    s2=end_time-start_time;
}

void lab4::quickSortR(int *arr, long size)
{
    
    long i = 0, j = size;      // поставить указатели на исходные места
    int temp, p;
    
    p = arr[ size>>1 ];      // центральный элемент
    
    // процедура разделения
    do {
        while ( arr[i] < p ) i++;
        while ( arr[j] > p ) j--;
        
        if (i <= j) {
            temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            i++; j--;
        }
    } while ( i<=j );
    
    // рекурсивные вызовы, если есть, что сортировать
    if ( j > 0 ) quickSortR(arr, j);
    if ( size > i ) quickSortR(arr+i, size-i);
    
}

void lab4::backup_save()
{
    for (int i=0; i<size; i++)
    {
        arrtmp[i]=arr[i];
    }
}

void lab4::backup_load()
{
    for (int i=0; i<size; i++)
    {
        arr[i]=arrtmp[i];
    }
}

bool lab4::check_arr(int *arr)
{
    for (int i=0; i<size; i++)
    {
        if (arr[i]<arr[i+1])
        {
            return true;
        }
    }
    return false;
}

void lab4::menu()
{
    int command, command_inp;
    srand((int)time(0));
    
    cout<<"\n⎧‾‾‾‾‾‾‾‾‾‾  МЕНЮ  ‾‾‾‾‾‾‾‾‾‾⎫\n";
    cout<<  "⎪1. Добавить элемент в массив⎪\n"
            "⎪2. Вывести массив           ⎪\n"
            "⎪3. Сортировка выбором       ⎪\n"
            "⎪4. Сортировка пузырьком     ⎪\n"
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
                {
                    cout<<"Введите размер массива: ";
                    cin>>size;
                    for (int i=0; i<size; i++)
                    {
                        cout<<"["<<setw(4)<<i<<"]"<<":→";
                        cin>>arr[i];
                    }
                } break;
                    
                case 2:
                {
                    cout<<"Введите размер массива: ";
                    cin>>size;
                    for (int i=0;i<size;i++)
                    {
                        //usleep(70000);
                        arr[i]=rand()%2000000+1;
                        if (size<20)
                        {
                        cout<<"[add]"<<setw(4)<<arr[i]<<endl;
                        }
                        else if (i==size-1)
                        {
                            cout<<"("<<setw(5)<<i<<") добавленно в массив\n";
                        }
                    }
                    
                } break;
                    
            }
        } menu(); break;
            
        case 2:
        {
            cout<<endl;
            if (size<100)
            {
            for (int i=0; i<size; i++)
            {
                usleep(70000);
                cout<<"["<<setw(4)<<i<<"] "<<arr[i]<<endl;
            }
            }
            else
            {
                for (int i=0;i<3;i++)
                {
                cout<<"["<<setw(4)<<i<<"] "<<arr[i]<<endl;
                }
                cout<<  "\t●\n"
                        "\t●\n"
                        "\t●\n";
                cout<<"["<<setw(4)<<size<<"] "<<arr[size-1]<<endl;
                
            }
        } menu(); break;
            
        case 3:
        {
            backup_save();
            selectSort();
            if (check_arr(arr)==true)
            {
                if (size<20)
                {
                    cout<<"[completed] Сортировка выбором\n";
                    for (int i=0; i<size; i++)
                    {
                        usleep(70000);
                        cout<<"["<<setw(4)<<i<<"] "<<arr[i]<<endl;
                    }
                }
                else
                {
                    cout<<"[completed] Сортировка выбором\n";
                    for (int i=0; i<size; i++)
                    {
                        usleep(7000);
                        cout<<"["<<setw(4)<<i<<"] "<<arr[i]<<endl;
                    }
                }
            }
            else
            {
                cout<<"[incomplete] Сортировка выбором\n";
            }
            cout<<"\n time: "<<s1/1000<<" ms"<<endl;
            backup_load();
        } menu(); break;
            
        case 4:
        {
            backup_save();
            bubbleSort();
            if (check_arr(arr)== true)
            {
                if (size<20)
                {
                    cout<<"[completed] Сортировка пузырьком\n";
                        for (int i=0; i<size; i++)
                        {
                            usleep(70000);
                            cout<<"["<<setw(4)<<i<<"] "<<arr[i]<<endl;
                        }
                }
                else
                {
                cout<<"[completed] Сортировка пузырьком\n";
                    for (int i=0; i<size; i++)
                    {
                        usleep(7000);
                        cout<<"["<<setw(4)<<i<<"] "<<arr[i]<<endl;
                    }
                }
            }
            cout<<"\n time: "<<s2/1000<<" ms"<<endl;
            backup_load();
        } menu(); break;
            
        case 5:
        {
            backup_save();
            start_time=(unsigned int)clock();
            quickSortR(arr,size);
            end_time=(unsigned int)clock();
            s3=end_time-start_time;
            if (size<20)
            {
                cout<<"[completed] Сортировка пузырьком\n";
                for (int i=0; i<size+1; i++)
                {
                    usleep(70000);
                    cout<<"["<<setw(4)<<i<<"] "<<arr[i]<<endl;
                }
            }
            else
            {
                cout<<"[completed] Быстрая сортировка\n";
                for (int i=0; i<size+1; i++)
                {
                    usleep(7000);
                    cout<<"["<<setw(4)<<i<<"] "<<arr[i]<<endl;
                }
            }
            cout<<"\n time: "<<s3/1000<<" ms"<<endl;
            backup_load();
        } menu(); break;
    }

}

int main()
{
    lab4 run;
    run.menu();
    cout<<clock()/1000;
    return 0;
}
