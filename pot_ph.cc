#include "pot_ph.h"

const int amount = -10;
const std::string sAmount = "10";

std::string Pot_PH::typeDescribe() const
{
 return "Poison " + sAmount + " Health Potion";
}

char Pot_PH::typeTo() const
{
 return 'H';
}

int Pot_PH::typeAmount() const
{
 return amount;
}
