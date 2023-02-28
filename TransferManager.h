#ifndef TRANSFERMANAGER_H
#define TRANSFERMANAGER_H

#include <iostream>
#include <vector>
#include <windows.h>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <math.h>
#include <algorithm>

#include "Incomes.h"
#include "Expenses.h"
#include "TransferFile.h"
#include "HelpMethods.h"

using namespace std;

class TransferManager
{
    const int LOGGED_USER_ID;
    const int DAYS_IN_MONTS_NOT_LEAP_YEAR [12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    const int DAYS_IN_MONTS_LEAP_YEAR     [12] = {31,29,31,30,31,30,31,31,30,31,30,31};

    vector <Incomes>  incomes;
    vector <Expenses> expenses;
    TransferFile transferFile;
    int loggedUserId;

    string convertDateIntToString(int date);
    string changeCommaToDot(string incomeTxt);

    string getDateFromUser();
    string getItemFromUser();
    string getAmountFromUser();

    char dateMenu();
    int  convertDateStringToInt(string date);
    int  todaysSystemDateInt();
    int  daysInMonthFromDate(int date);
    int  lastDateInChoosenMonth(int choosenDate);
    bool correctLettersInDate(string dateString);
    bool leapYear(int year);
    int  currentMonthFirstDay();
    int  currentMonthEndDay();
    int  previousMonthFirstDay();
    int  previousMonthEndDay();
    bool checkCorrectnessDate(string date);

    void   readIcomesFromUser();
    bool   checkCorrectnessTransaction(string moneyTxt);
    double showIncomesSelectedPeriod(int startDate, int endDate);
    double showExpensesSelectedPeriod(int startDate, int endDate);
    void   showBalanceFromDateToDate(int startDate, int endDate);

    void sortIncomesAndExpenses();
    void sortIncomesByDate();
    void sortExpensesByDate();

public:
    TransferManager (string incomesFileName, string expensesFileName, int loggedUserId)
        : LOGGED_USER_ID(loggedUserId), transferFile(incomesFileName, expensesFileName)
    {
        incomes  = transferFile.readLoggedUserIncomesFromFile (LOGGED_USER_ID);
        expenses = transferFile.readLoggedUserExpensesFromFile(LOGGED_USER_ID);
    };

    void addIncome();
    void addExpense();
    void balanceCurrentMonth();
    void balancePreviousMonth();
    void balanceSelectedPeriod();
};

#endif
