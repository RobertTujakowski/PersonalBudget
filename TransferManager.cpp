#include "TransferManager.h"

void TransferManager::addIncome()
{
    Incomes income;

    income.setIncomeId( HelpMethods::convertIntToString( transferFile.getLastIncomeId()+1 ) );

    income.setUserId( HelpMethods::convertIntToString( LOGGED_USER_ID) );
    income.setDate( getDateFromUser() );
    income.setItem( getItemFromUser() );
    income.setAmount( getAmountFromUser() );

    transferFile.addIncomeToFile(income);
    incomes.push_back(income);
}

void TransferManager::addExpense()
{
    Expenses expense;

    expense.setExpenseId( HelpMethods::convertIntToString( transferFile.getLastExpenseId()+1 ) );

    expense.setUserId( HelpMethods::convertIntToString( LOGGED_USER_ID) );
    expense.setDate( getDateFromUser() );
    expense.setItem( getItemFromUser() );
    expense.setAmount( getAmountFromUser() );

    transferFile.addExpenseToFile(expense);
    expenses.push_back(expense);
}

string TransferManager::getDateFromUser()
{
    string date = "";

    char choiceDate = dateMenu();

    if (choiceDate == '1')
    {
        date = convertDateIntToString( todaysSystemDateInt() );
        cout << endl << "Today is: " << date << endl;
    }
    else
    {
        while (true)
        {
            cout << endl << "Write a date in format:yyyy-mm-dd; for example: 2017-11-01," << endl;
            cout << "date should be from 2000-01-01 to max end of this month." << endl;
            date = HelpMethods::readLine();

            if ( !checkCorrectnessDate(date) ) cout << "You wrote wrong date" << endl;
            else break;
        }
    }

    return date;
}

char TransferManager::dateMenu()
{
    char choiceDate;
    do
    {
        system("CLS");
        cout << "Choose date:" << endl;
        cout << "1: Today" << endl;
        cout << "2: Write different date" << endl;
        choiceDate = HelpMethods::readChar();

    } while (choiceDate!='1' && choiceDate!='2');

    return choiceDate;
}

bool TransferManager::checkCorrectnessDate(string dateString)
{
    if ( !correctLettersInDate(dateString) ) return false;

    int dateInt = convertDateStringToInt(dateString);

    if ( dateInt<20000101 ) return false;

    if (dateInt > lastDateInChoosenMonth( todaysSystemDateInt() ) ) return false;

    if (dateInt > lastDateInChoosenMonth( dateInt ) ) return false;

    return true;
}

bool TransferManager::correctLettersInDate(string dateString)
{
    if ( dateString.length() != 10 ) return false;

    if ( dateString[4]!='-' || dateString[7]!='-' ) return false;

    int dashNr = 0;
    for (unsigned int pos=0; pos<(dateString.length()); pos++)
    {
        if (( dateString[pos] ) == '-') dashNr++;
        if (dashNr>2) return false;
        if ( dateString[pos]!='-' && !((dateString[pos]>=48) && (dateString[pos]<=57)) ) return false;
    }

    return true;
}

int TransferManager::lastDateInChoosenMonth(int date)
{
    int days = date%100;
    return ( (date-days) + daysInMonthFromDate( date ) );
}

string TransferManager::getItemFromUser()
{
    cout << endl << "Write the transaction name : ";
    return HelpMethods::readLine();
}

string TransferManager::getAmountFromUser()
{
    while (true)
    {
        cout << endl << "Write the amount of transaction : ";
        string transactionTxt = HelpMethods::readLine();

        if ( !checkCorrectnessTransaction(transactionTxt) )
        {
            cout << "You wrote wrong transaction" << endl;
        }
        else
        {
            transactionTxt = changeCommaToDot(transactionTxt);
            return transactionTxt;
        }
    }
}

string TransferManager::convertDateIntToString(int date) // 20230209 -> "2023-02-09"
{
    int year, month, day;
    string yearString, monthString, dayString;

    year  = floor ( date/10000 );
    month = floor ((date%10000) / 100);
    day   = date%100;

    yearString  = HelpMethods::convertIntToString(year);

    if (month<10) monthString = '0' + HelpMethods::convertIntToString(month);
    else          monthString = HelpMethods::convertIntToString(month);

    if (day<10) dayString = '0' + HelpMethods::convertIntToString(day);
    else        dayString = HelpMethods::convertIntToString(day);

    return yearString + '-' + monthString + '-' + dayString;
}

int TransferManager::convertDateStringToInt(string date) // "2023-02-09" -> 20230209
{
    int dateInt, year, month, day;

    year  = HelpMethods::convertStringToInt( date.substr(0,4) );
    month = HelpMethods::convertStringToInt( date.substr(5,2) );
    day   = HelpMethods::convertStringToInt( date.substr(8,2) );

    dateInt = year*10000 + month*100 + day;
    return dateInt;
}

int TransferManager::todaysSystemDateInt()
{
    time_t secondsFrom1970 = time(0);               // time in seconds from year 1970

    tm *timeStruct = localtime(&secondsFrom1970);

    int date, year, month, monthsDay;

    year      = timeStruct -> tm_year+1900;         // https://www.youtube.com/watch?v=M1E3roUNTMY 2:13
    month     = timeStruct -> tm_mon+1;
    monthsDay = timeStruct -> tm_mday;

    date = year*10000 + month*100 + monthsDay;

    return date;
}

int TransferManager::daysInMonthFromDate(int date)
{
    int year, month;
    year  = floor ( date/10000 );
    month = floor ((date%10000) / 100);

    if ( leapYear(year) )
        return DAYS_IN_MONTS_LEAP_YEAR[month-1];
    else
        return DAYS_IN_MONTS_NOT_LEAP_YEAR[month-1];
}

bool TransferManager::leapYear(int year)
{
    if (((year%4 == 0) && (year%100 !=0 )) || (year%400 == 0))
        return true;
    else
        return false;
}

bool TransferManager::checkCorrectnessTransaction(string moneyTxt)
{
    int  dotNr=0;
    int  commaNr=0;
    char letter;

    if ( moneyTxt[0]=='.' || moneyTxt[0]==',' ) return false;                                       // ., na poczatku
    if ( moneyTxt[moneyTxt.length()-1]=='.' || moneyTxt[moneyTxt.length()-1]==',' ) return false;   // ., na koncu

    if ( (moneyTxt.length()==1) && !((moneyTxt[0]>=48) && (moneyTxt[0]<=57)) ) return false;        // tylko, lub.

    for (unsigned int pos=0; pos < moneyTxt.length(); pos++)
    {
        letter = moneyTxt[pos];
        if (letter == '.') dotNr++;
        if (letter == ',') commaNr++;

        if ( (dotNr>1) || (commaNr>1) || ((dotNr+commaNr)>1) ) return false;
        if ( (letter!='.') && (letter!=',') && !((letter>=48) && (letter<=57)) ) return false;
    }

    return true;
}

string TransferManager::changeCommaToDot(string moneyTxt)
{
    for (unsigned int pos=0; pos < moneyTxt.length(); pos++)
    {
        if (moneyTxt[pos]==',')
        {
            moneyTxt[pos] = '.';
        }
    }

    return moneyTxt;
}

double TransferManager::showIncomesSelectedPeriod(int startDate, int endDate)
{
    cout << "--------------------" << endl;
    cout << "Incomes are:" << endl;
    cout << "--------------------" << endl;

    double incomesSumm = 0;

    for (unsigned int pos=0; pos < incomes.size(); pos++)
    {
        int checkedDate = convertDateStringToInt ( incomes[pos].getDate() );
        if ( (checkedDate >= startDate) && (checkedDate <= endDate) )
        {
            cout << "Date   : " << incomes[pos].getDate()   << endl;
            cout << "Item   : " << incomes[pos].getItem()   << endl;
            cout << "Amount : " << incomes[pos].getAmount() << endl;
            cout << "--------------------" << endl;
            incomesSumm += HelpMethods::convertStringToDouble( incomes[pos].getAmount() );
        }
    }

    if ( incomesSumm==0 )
    {
        cout << " No incomes in this period " << endl;
        cout << "--------------------" << endl;
    }

    return incomesSumm;
}

double TransferManager::showExpensesSelectedPeriod(int startDate, int endDate)
{
    cout << "--------------------" << endl;
    cout << "Expenses are:" << endl;
    cout << "--------------------" << endl;

    double expensesSumm = 0;

    for (unsigned int pos=0; pos < expenses.size(); pos++)
    {
        int checkedDate = convertDateStringToInt ( expenses[pos].getDate() );
        if ( (checkedDate >= startDate) && (checkedDate <= endDate) )
        {
            cout << "Date   : " << expenses[pos].getDate()   << endl;
            cout << "Item   : " << expenses[pos].getItem()   << endl;
            cout << "Amount : " << expenses[pos].getAmount() << endl;
            cout << "--------------------" << endl;
            expensesSumm += HelpMethods::convertStringToDouble( expenses[pos].getAmount() );
        }
    }

    if ( expensesSumm==0 )
    {
        cout << " No expenses in this period " << endl;
        cout << "--------------------" << endl;
    }

    return expensesSumm;
}

int TransferManager::currentMonthFirstDay()
{
    return todaysSystemDateInt() - (todaysSystemDateInt() % 100) + 1;
}

int TransferManager::currentMonthEndDay()
{
    return todaysSystemDateInt() - (todaysSystemDateInt() % 100) + daysInMonthFromDate( todaysSystemDateInt() );
}

int TransferManager::previousMonthFirstDay()
{
    int firstDay   = 1;
    int currentMonth = (todaysSystemDateInt() % 10000) / 100;
    int currentYear  = todaysSystemDateInt() / 10000;

    int previousMonth;
    if ( currentMonth == 1 )
        previousMonth = 12;
    else previousMonth = currentMonth - 1;

    int previousMonthYear = currentYear-1;
    if ( currentMonth==1 )
        previousMonthYear = currentYear-1;
    else previousMonthYear = currentYear;

    return previousMonthYear*10000 + previousMonth*100 + firstDay;
}

int TransferManager::previousMonthEndDay()
{
    int currentMonth = (todaysSystemDateInt() % 10000) / 100;
    int currentYear  = todaysSystemDateInt() / 10000;

    int previousMonth;
    if ( currentMonth == 1 )
        previousMonth = 12;
    else previousMonth = currentMonth - 1;

    int previousMonthYear = currentYear-1;
    if ( currentMonth==1 )
        previousMonthYear = currentYear-1;
    else previousMonthYear = currentYear;

    int lastDay = daysInMonthFromDate(previousMonthYear*10000 + previousMonth*100 + 1);

    return previousMonthYear*10000 + previousMonth*100 + lastDay;
}

void TransferManager::showBalanceFromDateToDate(int startDate, int endDate)
{
    sortIncomesAndExpenses();

    double incomesSumm  = showIncomesSelectedPeriod ( startDate, endDate );
    double expensesSumm = showExpensesSelectedPeriod( startDate, endDate );

    cout << "Incomes summ  = " << incomesSumm  << endl;
    cout << "Expenses summ = " << expensesSumm << endl;
    cout << "--------------------" << endl;
    cout << "Balance is : " << incomesSumm-expensesSumm << endl << endl;
}

void TransferManager::balanceCurrentMonth()
{
    int startDate = currentMonthFirstDay();
    int endDate   = currentMonthEndDay();

    system("CLS");
    cout << "Balance from current month:" << endl;
    showBalanceFromDateToDate(startDate, endDate);

    system("pause");
}

void TransferManager::balancePreviousMonth()
{
    int startDate = previousMonthFirstDay();
    int endDate   = previousMonthEndDay();

    system("CLS");
    cout << "Balance from previous month:" << endl;
    showBalanceFromDateToDate(startDate, endDate);

    system("pause");
}

void TransferManager::balanceSelectedPeriod()
{
    system("CLS");
    cout << "Balance from selected period" << endl;
    cout << "---------------------------------" << endl;
    cout << "Type start date of transactions." << endl;

    string startDate, endDate;
    while (true)
    {
        cout << endl << "Write a date in format:yyyy-mm-dd; for example: 2017-11-01," << endl;
        cout << "date should be from 2000-01-01 to max end of this month." << endl;
        startDate = HelpMethods::readLine();

        if ( !checkCorrectnessDate(startDate) ) cout << "You wrote wrong date" << endl;
        else break;
    }

    cout << "---------------------------------" << endl;
    cout << "Type end date of transactions." << endl;
    while (true)
    {
        cout << endl << "Write a date in format:yyyy-mm-dd; for example: 2017-11-01," << endl;
        cout << "date should be from 2000-01-01 to max end of this month." << endl;
        endDate = HelpMethods::readLine();

        if ( !checkCorrectnessDate(endDate) || (convertDateStringToInt(startDate) > convertDateStringToInt(endDate)) )
            cout << "You wrote wrong date" << endl;
        else break;
    }

    cout << "Balance from selected time:" << endl;
    showBalanceFromDateToDate( convertDateStringToInt(startDate), convertDateStringToInt(endDate) );

    system("pause");
}

bool TransferManager::compareIncomes(Incomes income1, Incomes income2)
{
  int dateInt1 = HelpMethods::convertStringToInt( income1.getDate() );
  int dateInt2 = HelpMethods::convertStringToInt( income2.getDate() );
  return dateInt1 > dateInt2;
}

void TransferManager::sortIncomesByDate()
{
    //sort(incomes.begin(), incomes.end(), compareIncomes);
}

bool TransferManager::compareExpenses(Expenses expense1, Expenses expense2)
{
  int dateInt1 = HelpMethods::convertStringToInt( expense1.getDate() );
  int dateInt2 = HelpMethods::convertStringToInt( expense2.getDate() );
  return dateInt1 > dateInt2;
}

void TransferManager::sortExpensesByDate()
{
    //sort(expenses.begin(), expenses.end(), compareExpenses);
}

void TransferManager::sortIncomesAndExpenses()
{
    sortIncomesByDate();
    sortExpensesByDate();
}
