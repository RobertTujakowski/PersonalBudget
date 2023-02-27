#include "HelpMethods.h"

string HelpMethods::convertIntToString(int number)
{
    ostringstream txt;
    txt << number;
    string str = txt.str();
    return str;
}

int HelpMethods::convertStringToInt(string number)
{
    int numberInt;
    istringstream iss(number);
    iss >> numberInt;

    return numberInt;
}

double HelpMethods::convertStringToDouble(string number)
{
    double numberDouble;
    istringstream iss(number);
    iss >> numberDouble;

    return numberDouble;
}

string HelpMethods::changeFirstLetterToUpperCaseRestToLowerCase(string text)
{
    if (!text.empty())
    {
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        text[0] = toupper(text[0]);
    }
    return text;
}

string HelpMethods::readLine()
{
    string input = "";
    cin.sync();
    getline(cin, input);
    return input;
}


char HelpMethods::readChar()
{
    string input = "";
    char sign = {0};

    while (true)
    {
        cin.sync();
        getline(cin, input);
        if (input.length() == 1)
        {
            sign = input[0];
            break;
        }
        cout << "It is not a single sign. Write again." << endl;
    }
    return sign;
}
