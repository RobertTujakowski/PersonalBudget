#ifndef INCOMES_H
#define INCOMES_H

#include <iostream>

using namespace std;

class Incomes
{
    string incomeId;
    string userId;
    string date;
    string item;
    string amount;

public:
    Incomes(string incomeId="", string userId="", string date="", string item="", string amount="")
    {
        this -> incomeId = incomeId;
        this -> userId = userId;
        this -> date = date;
        this -> item = item;
        this -> amount = amount;
    }

    void setIncomeId(string newIncomeId);
    void setUserId(string newUserId);
    void setDate(string newDate);
    void setItem(string newItem);
    void setAmount(string newAmount);

    string getIncomeId();
    string getUserId();
    string getDate();
    string getItem();
    string getAmount();
};

#endif
