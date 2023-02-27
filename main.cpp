#include <iostream>
#include "PersonalBudget.h"

using namespace std;

int main()
{
    PersonalBudget personalBudget("users.xml", "incomes.xml", "expenses.xml");

    char choice;
    while (true)
    {
        if ( !personalBudget.isUserLogged() )
        {
            choice = personalBudget.chooseOptionFromLoginMenu();

            switch (choice)
            {
                case '1':
                    personalBudget.userRegistration();
                    break;
                case '2':
                    personalBudget.userLogin();
                    break;
                case '9':
                    exit(0);
                    break;
                default:
                    cout << endl << "There is no such option in the menu." << endl << endl;
                    system("pause");
                    break;
            }
        }
        else
        {
            choice = personalBudget.chooseOptionFromLoggedUserMenu();
            switch (choice)
            {
            case '1':
                personalBudget.addIncome();
                break;
            case '2':
                personalBudget.addExpense();
                break;
            case '3':
                personalBudget.balanceCurrentMonth();
                break;
            case '4':
                personalBudget.balancePreviousMonth();
                break;
            case '5':
                personalBudget.balanceSelectedPeriod();
                break;
            case '6':
                personalBudget.changePassword();
                break;
            case '7':
                personalBudget.logout();
                break;
            }
        }
    }

    return 0;
}
