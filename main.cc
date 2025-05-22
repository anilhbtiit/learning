#include <stdio.h>
#include <stdlib.h>				  // For qsort
#include <string.h>				  // For strcmp
#include <iostream>

extern int auto_();
extern int cpp20();
//extern void a00();
//extern void template_();

using namespace std;

int main() {    
    int number;

    cout << "Enter an integer: ";
    cin >> number;

    cout << "You entered " << number << std::endl;    
    auto_();
    cpp20();
    //a00();
    //template_();
    return 0;
}
