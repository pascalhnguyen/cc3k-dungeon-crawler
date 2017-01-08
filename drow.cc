#include "drow.h"
#include "enemy.h"
#include "potion.h"

const int dHP = 150;
const int dAtk = 25;
const int dDef = 15;

Drow::Drow(): Player{dHP, dAtk, dDef} {}

void Drow::resetStats() { atk = dAtk; def = dDef; }
int Drow::getMaxHP() const { return dHP; }
int Drow::getBaseAtk() const { return dAtk; }
int Drow::getBaseDef() const { return dDef; }

void Drow::usePotion(const std::shared_ptr<Potion> pt)
{
 int amnt = pt->effectAmount() * 1.5;
 this->usePotionAmount(pt, amnt);
}

int Drow::Attacked(std::shared_ptr<Enemy> en)
{ // override the two attacks by elves
 int success = rand() % 2; //since they have a 50% chance of missing

 if(success) { return 0; }

 int damage = (100 * en->getAtk()) / (100 + this->getDef());
 curHP -= damage;
 if(curHP<=0)
 {
  alive = false;
  return -damage; }

 return damage;
}
