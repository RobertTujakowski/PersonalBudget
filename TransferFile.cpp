#include "TransferFile.h"
#include "Markup.h"

vector <Incomes> TransferFile::readLoggedUserIncomesFromFile (int loggedUserId)
{
    Incomes income;
    vector <Incomes> incomes;

    CMarkup xml;

    bool fileExists = xml.Load(INCOMES_FILE_NAME);

    if (!fileExists)
    {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("INCOMES");
        xml.Save(INCOMES_FILE_NAME);
    }
    else
    {
        xml.FindElem("INCOMES");
        xml.IntoElem();

        while ( xml.FindElem("income") )
        {
            xml.IntoElem();

            lastIncomeId++;
            xml.FindElem("incomeId");
            income.setIncomeId( HelpMethods::convertIntToString( lastIncomeId ) );

            xml.FindElem("userId");
            if ( HelpMethods::convertIntToString( loggedUserId ) == MCD_2PCSZ(xml.GetData()) )
            {
                income.setUserId( HelpMethods::convertIntToString( loggedUserId ) );

                xml.FindElem("date");
                income.setDate( MCD_2PCSZ(xml.GetData()) );

                xml.FindElem("item");
                income.setItem( MCD_2PCSZ(xml.GetData()) );

                xml.FindElem("amount");
                income.setAmount( MCD_2PCSZ(xml.GetData()) );

                incomes.push_back(income);
            }

            xml.OutOfElem();
        }
    }

    return incomes;
}

vector <Expenses> TransferFile::readLoggedUserExpensesFromFile(int loggedUserId)
{
    Expenses expense;
    vector <Expenses> expenses;

    CMarkup xml;

    bool fileExists = xml.Load(EXPENSES_FILE_NAME);

    if (!fileExists)
    {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("EXPENSES");           // tworzy element glowny (ang. root element)
    }
    else
    {
        xml.FindElem("EXPENSES");
        xml.IntoElem();

        while ( xml.FindElem("expense") )
        {
            xml.IntoElem();

            lastExpenseId++;
            xml.FindElem("expenseId");
            expense.setExpenseId( HelpMethods::convertIntToString( lastExpenseId ) );

            xml.FindElem("userId");
            if ( HelpMethods::convertIntToString( loggedUserId ) == MCD_2PCSZ(xml.GetData()) )
            {
                expense.setUserId( HelpMethods::convertIntToString( loggedUserId ) );

                xml.FindElem("date");
                expense.setDate( MCD_2PCSZ(xml.GetData()) );

                xml.FindElem("item");
                expense.setItem( MCD_2PCSZ(xml.GetData()) );

                xml.FindElem("amount");
                expense.setAmount( MCD_2PCSZ(xml.GetData()) );

                expenses.push_back(expense);
            }

            xml.OutOfElem();
        }

    }
    xml.Save(EXPENSES_FILE_NAME);
    return expenses;
}

int TransferFile::getLastIncomeId()
{
    return lastIncomeId;
}

int  TransferFile::getLastExpenseId()
{
    return lastExpenseId;
}

void TransferFile::addIncomeToFile(Incomes income)
{
    lastIncomeId++;
    CMarkup xml;
    bool fileExists = xml.Load(INCOMES_FILE_NAME);

    xml.FindElem("INCOMES");
    xml.IntoElem();

    xml.AddElem("income");
    xml.IntoElem();
    xml.AddElem( "incomeId",income.getIncomeId() );
    xml.AddElem( "userId"  ,income.getUserId() );
    xml.AddElem( "date"    ,income.getDate() );
    xml.AddElem( "item"    ,income.getItem() );
    xml.AddElem( "amount"  ,income.getAmount() );
    xml.OutOfElem();

    xml.Save(INCOMES_FILE_NAME);
}

void TransferFile::addExpenseToFile(Expenses expense)
{
    lastExpenseId++;
    CMarkup xml;
    bool fileExists = xml.Load(EXPENSES_FILE_NAME);

    xml.FindElem("EXPENSES");
    xml.IntoElem();

    xml.AddElem("expense");
    xml.IntoElem();
    xml.AddElem( "expenseId",expense.getExpenseId() );
    xml.AddElem( "userId"   ,expense.getUserId() );
    xml.AddElem( "date"     ,expense.getDate() );
    xml.AddElem( "item"     ,expense.getItem() );
    xml.AddElem( "amount"   ,expense.getAmount() );
    xml.OutOfElem();

    xml.Save(EXPENSES_FILE_NAME);
}
