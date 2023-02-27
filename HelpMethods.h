#ifndef HELPMETHODS_H
#define HELPMETHODS_H

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

class HelpMethods
{
public:
    static string convertIntToString(int number);
    static int    convertStringToInt(string number);
    static double convertStringToDouble(string number);
    static string changeFirstLetterToUpperCaseRestToLowerCase(string text);
    static string readLine();
    static char   readChar();
};

#endif
