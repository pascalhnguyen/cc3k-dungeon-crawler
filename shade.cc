#include "shade.h"

const int dHP = 125;
const int dAtk = 25;
const int dDef = 25;

Shade::Shade(): Player{dHP, dAtk, dDef} {}

void Shade::resetStats() { atk = dAtk; def = dDef; }
int Shade::getMaxHP() const { return dHP; }
int Shade::getBaseAtk() const { return dAtk; }
int Shade::getBaseDef() const { return dDef; }

int Shade::getScore() const { return this->getWealth() * 1.5; }

