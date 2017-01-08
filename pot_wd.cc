#include "pot_wd.h"

const int amount = -5;
const std::string sAmount = "5";

std::string Pot_WD::typeDescribe() const
{
 return "Wound " + sAmount + " Defense";
}

char Pot_WD::typeTo() const
{
 return 'D';
}

int Pot_WD::typeAmount() const
{
 return amount;
}
