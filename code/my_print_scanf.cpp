#include<iostream>
#include<stdlib.h>
#include<memory>
#include<string>
#include<stdarg.h>
#include<unistd.h>
using namespace std;

#define BUFFERSIZE 1024
int my_print(const char* format, ...)
{
    char buffer[BUFFERSIZE];
    va_list varg;
    va_start(varg, format);
    ssize_t len = vsprintf(buffer, format, varg);
    va_end(varg);
    write(1, buffer, len);
    return len;
}

int my_scanf(const char* format, ...)
{
    char buffer[BUFFERSIZE];
    va_list varg;
    va_start(varg, format);
    read(0, buffer, BUFFERSIZE);
    va_end(varg);
    ssize_t len = vsscanf(buffer, format, varg);
    return len;
}


int main()
{
    int num;
    char* name;
    my_print("please input a num : \n");
    my_scanf("%d", &num);
    my_print("the input num = %d\n", num);

    my_print("please input a name : \n");
    my_scanf("%s", name);
    my_print("name = %s\n", name);
    return 0;
}