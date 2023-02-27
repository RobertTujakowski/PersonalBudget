#include "Incomes.h"

void Incomes::setIncomeId(string newIncomeId)
{
    incomeId = newIncomeId;
}
void Incomes::setUserId(string newUserId)
{
    userId = newUserId;
}
void Incomes::setDate(string newDate)
{
    date = newDate;
}
void Incomes::setItem(string newItem)
{
    item = newItem;
}
void Incomes::setAmount(string newAmount)
{
    amount = newAmount;
}
//--------------------------------------------
string Incomes::getIncomeId()
{
    return incomeId;
}
string Incomes::getUserId()
{
    return userId;
}
string Incomes::getDate()
{
    return date;
}
string Incomes::getItem()
{
    return item;
}
string Incomes::getAmount()
{
    return amount;
}
