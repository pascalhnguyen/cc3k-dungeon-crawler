#include "vampire.h"

const int suc = 5;

const int dHP = 50;
const int dAtk = 25;
const int dDef = 25;

Vampire::Vampire(): Player{dHP, dAtk, dDef} {}

void Vampire::resetStats() { atk = dAtk; def = dDef; }
int Vampire::getMaxHP() const { return 0; }
int Vampire::getBaseAtk() const { return dAtk; }
int Vampire::getBaseDef() const { return dDef; }

void Vampire::gainHP(int amnt)
{
 curHP += amnt;
}

void Vampire::successAttack(char marker)
{
 if(marker == 'W')
 {
  curHP -=suc;
  if(curHP<=0) { alive = false; }
 }
 else
 {
  curHP += suc;
 }
}
