#include "pot_ba.h"

const int amount = 5;
const std::string sAmount = "5";

std::string Pot_BA::typeDescribe() const
{
 return "Boost " + sAmount + " Attack Potion";
}

char Pot_BA::typeTo() const
{
 return 'A';
}

int Pot_BA::typeAmount() const
{
 return amount;
}
