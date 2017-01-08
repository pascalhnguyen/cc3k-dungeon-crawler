#include "pot_bd.h"

const int amount = 5;
const std::string sAmount = "5";

std::string Pot_BD::typeDescribe() const
{
 return "Boost " + sAmount + " Defense";
}

char Pot_BD::typeTo() const
{
 return 'D';
}

int Pot_BD::typeAmount() const
{
 return amount;
}
