#ifndef TRANSFERFILE_H
#define TRANSFERFILE_H

#include <iostream>
#include <vector>
#include <windows.h>
#include "Markup.h"

#include "Incomes.h"
#include "Expenses.h"
#include "HelpMethods.h"

using namespace std;

class TransferFile
{
    const string INCOMES_FILE_NAME;
    const string EXPENSES_FILE_NAME;
    int lastIncomeId;
    int lastExpenseId;
    CMarkup xml;

public:
    TransferFile(string incomesFileName, string expensesFileName)
        : INCOMES_FILE_NAME(incomesFileName), EXPENSES_FILE_NAME(expensesFileName)
    {
        lastIncomeId  = 0;
        lastExpenseId = 0;
    }
    vector <Incomes>  readLoggedUserIncomesFromFile (int loggedUserId);
    vector <Expenses> readLoggedUserExpensesFromFile(int loggedUserId);
    int  getLastIncomeId();
    int  getLastExpenseId();
    void addIncomeToFile(Incomes income);
    void addExpenseToFile(Expenses expense);
};

#endif
