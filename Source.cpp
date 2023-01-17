#include <iostream>
#include "HugeReal.h"
#include<conio.h>
using namespace std;
int main()
{
    HugeReal H;
    {
        HugeReal** I = nullptr;
        int _nos;
        ifstream fin("Text.txt");
        fin >> _nos;
        I = new HugeReal * [_nos];
        for (int i = 0; i < _nos; i++)
        {
            I[i] = new HugeReal(fin);
        }
        /*for (int i = 0; i < _nos; i++)
        {
            cout << *I[i] << endl;
        }
        if (*I[0] > *I[1])
        {
            cout << "true";
        }
        else
        {
            cout << "false";
        }*/
        cout << endl;
        HugeReal temp;
        //temp = *I[0] / *I[1];//use any operator
        H = *I[1] / *I[0];
       // cout << temp;
        cout << *I[1];
        cout << endl;
        cout << *I[0];
        cout << endl;
        cout << H;
    }
    
    return 0;
}
int main1()
{
    HugeReal x;
    HugeReal y;
    while (true)
    {
        cout << "input numbers:\n";
        cin >> x >> y;
        if (x > y)
        {
            cout << "1 is greater\n";
        }
        if (x >= y)
        {
            cout << "1 is greater or equal\n";
        }
        if (x < y)
        {
            cout << "2 is greater\n";
        }
        if (x <= y)
        {
            cout << "2 is greater or equal\n";
        }
        if (x == y)
        {
            cout << "both are equal\n";
        }
        _getch();
        system("cls");

    }
    return 0;
}

