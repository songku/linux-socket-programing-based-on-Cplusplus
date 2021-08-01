/*
 * @Description: 
 * @Author: dive668
 * @Date: 2021-08-01 18:27:18
 * @LastEditTime: 2021-08-01 19:40:14
 */
#include <iostream>
#include <string.h>
#include <sstream>
using namespace std;

int main()
{
    char buf[100];
    int var_temp=100;

    while(1)
    {
        std::stringstream out;
        var_temp--;
        out<<var_temp;
        out>>buf;
        printf("%s\n",buf);
    }
//    strcpy(buf,out.str());

    // strcpy(buf,"get current var_temp"); 
    // if(strcmp(buf,"get current var_temp")==0)//equal
    //     printf("YES!");
    // else // not equal
    //     printf("error!\n");
    //incompatible types in assignment of 'const char [7]' to 
    //'char [100]'
//    buf[0]="error!";
    //error: invalid conversion from 'const char*' to 'char' 
    //[-fpermissive]
//    cout<<buf;
//    cout<<buf<<endl;
    printf("%s",buf);
}
