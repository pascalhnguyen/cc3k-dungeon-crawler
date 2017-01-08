#include "troll.h"

const int dHP = 120;
const int dAtk = 25;
const int dDef = 15;

Troll::Troll(): Player{dHP, dAtk, dDef} {}

void Troll::resetStats() { atk = dAtk; def = dDef; }
int Troll::getMaxHP() const { return dHP; }
int Troll::getBaseAtk() const { return dAtk; }
int Troll::getBaseDef() const { return dDef; }

void Troll::newTurn()
{
 this->gainHP(5);
}
