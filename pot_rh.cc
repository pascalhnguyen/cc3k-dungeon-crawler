#include "pot_rh.h"

const int amount = 10;
const std::string sAmount = "10";

std::string Pot_RH::typeDescribe() const
{
 return "Restore " + sAmount + " Health Potion";
}

char Pot_RH::typeTo() const
{
 return 'H';
}

int Pot_RH::typeAmount() const
{
 return amount;
}
