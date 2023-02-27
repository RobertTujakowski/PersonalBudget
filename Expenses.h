#ifndef EXPENSES_H
#define EXPENSES_H

#include <iostream>

using namespace std;

class Expenses
{
    string expenseId;
    string userId;
    string date;
    string item;
    string amount;

public:
    Expenses(string expenseId="", string userId="", string date="", string item="", string amount="")
    {
        this -> expenseId = expenseId;
        this -> userId = userId;
        this -> date = date;
        this -> item = item;
        this -> amount = amount;
    }

    void setExpenseId(string newExpenseId);
    void setUserId(string newUserId);
    void setDate(string newDate);
    void setItem(string newItem);
    void setAmount(string newAmount);

    string getExpenseId();
    string getUserId();
    string getDate();
    string getItem();
    string getAmount();
};

#endif
