#include<iostream>
#include<cstring>
#include<string>
#include<stdlib.h>
#include<map>
#include<unordered_map>
#include<getopt.h>
#include<unistd.h>
using namespace std;
const char* version = "1.0.0";
std::unordered_map<std::string, std::string> wea{
    {"Beijing", "15°C, Sunny,  ☀️"},
    {"Shanghai","18°C, Cloudy, ⛅"},
    {"New York","10°C, Rainy,  🌧️"},
    {"London",  " 7°C, Snowy,  ❄️"} 
};


int tem = 0, con = 0, help = 0, ver = 0;
void Print_help(const char* cmdname)
{
    printf("Usage : %s [OPTIONS]!\n", cmdname);
    printf("Options : \n");
    printf(" -h, --help                       Show this help message\n");
    printf(" -v, --version                    Show the version infomation\n");
    printf(" -c City, --city City             Specify the city of weather query\n");
    printf(" -t, --temp                       Show the temperature of the city\n");
    printf(" -C, --condition                  Show the condition of the city\n");
    printf(" -a, --all                        Show all weather information\n");
}

void Weather(const char* city)
{
    if(city == "all")
    {
        printf("Weather information of all cities : \n");
        for(auto x : wea)
        {
            printf("%-10s : %s\n", x.first.c_str(), x.second.c_str());
        }
        return;
    }
    if(wea.find(city) == wea.end())
    {
        cout << "Wrong City, only Beijing 、Shanghai 、New York and London \n";
        return;
    }

    if(con == tem)
    {
        printf("%-10s : %s\n", city, wea[city].c_str());
    }
    else if(tem || con)
    {
        char* str = (char*)wea[city].c_str();
        char* p =strchr(str, ',');
        if(tem)
        {
            *p = '\0';
            printf("%-10s : %s\n", city, str);
        }
        else
        {
            p += 1;
            printf("%-10s : %s\n", city, p);
        }
    }
    return;
}

void Print_version()
{
    printf("version : %s\n", version);
}
int main(int argc, char* argv[])
{

    if(argc <= 1)
    {
        Print_help(argv[0]);
        return 1;
    }
    int opt = 0;
    char* city;
    char *str = (char*)"hc:tCav";
    while((opt = getopt(argc, argv, str)) != -1)
    {
        switch (opt)
        {
        case 'h':
            help = 1;
            break;
        case 'c':
            city = optarg;
            break;
        case 't':
            tem = 1;
            break;
        case 'C':
            con = 1;
            break;
        case 'a':
            city = (char*)"all";
            tem = 1, con = 1;
            break;
        case 'v':
            ver = 1;
            break;
        default:
            Print_help(argv[0]);
            return 1;
        }
    }

    if(help)
    {
        Print_help(argv[0]);
    }

    Weather(city);

    if (ver)
    {
        Print_version();
    }
    return 0;
}

