#include "goblin.h"
#include "enemy.h"

const int dHP = 110;
const int dAtk = 15;
const int dDef = 20;

Goblin::Goblin(): Player{dHP, dAtk, dDef} {}

void Goblin::resetStats() { atk = dAtk; def = dDef; }
int Goblin::getMaxHP() const { return dHP; }
int Goblin::getBaseAtk() const { return dAtk; }
int Goblin::getBaseDef() const { return dDef; }

int Goblin::Attacked(std::shared_ptr<Enemy> en)
{
 int success = rand() % 2; //since they have a 50% chance of missing
 if(success) { return 0; }

 int damage = (100 * en->getAtk()) / (100 + this->getDef());
 if(en->getMarker()=='E') damage=(200*en->getAtk())/(100+this->getDef());
 else if(en->getMarker()=='O') damage=(150*en->getAtk())/(100+this->getDef());

 curHP -= damage;
 if(curHP<=0)
 {
  alive = false;
  return -damage;
 }

 return damage;
}

void Goblin::successKill()
{
 this->gainWealth(5);
}
