#include "Expenses.h"

void Expenses::setExpenseId(string newExpenseId)
{
    expenseId = newExpenseId;
}
void Expenses::setUserId(string newUserId)
{
    userId = newUserId;
}
void Expenses::setDate(string newDate)
{
    date = newDate;
}
void Expenses::setItem(string newItem)
{
    item = newItem;
}
void Expenses::setAmount(string newAmount)
{
    amount = newAmount;
}
//--------------------------------------------
string Expenses::getExpenseId()
{
    return expenseId;
}
string Expenses::getUserId()
{
    return userId;
}
string Expenses::getDate()
{
    return date;
}
string Expenses::getItem()
{
    return item;
}
string Expenses::getAmount()
{
    return amount;
}
