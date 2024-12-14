#include<iostream>
#include<string>
#include<stdlib.h>
#include <unistd.h>
using namespace std;

char* name = nullptr;
int age = 18;
char* gender = "man";

int main(int argc, char* argv[])
{
    int opt = 0;
    while((opt = getopt(argc, argv, "n:a:g:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            name = optarg;
            break;
        case 'a':
            age = atoi(optarg);
            break;
        case 'g':
            gender = optarg;
            break;
        default:
            cout << "Usage : ./a.out -n name -a 18 -g nan\n";
            return 1;
        }
    }

    cout << "name = " << name << endl;
    cout << "age = " << age << endl;
    cout << "gender = " << gender << endl;
    return 0;
}