#include "pot_wa.h"

const int amount = -5;
const std::string sAmount = "5";

std::string Pot_WA::typeDescribe() const
{
 return "Wound " + sAmount + " Attack Potion";
}

char Pot_WA::typeTo() const
{
 return 'A';
}

int Pot_WA::typeAmount() const
{
 return amount;
}
